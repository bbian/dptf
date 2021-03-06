/******************************************************************************
** Copyright (c) 2013 Intel Corporation All Rights Reserved
**
** Licensed under the Apache License, Version 2.0 (the "License"); you may not
** use this file except in compliance with the License.
**
** You may obtain a copy of the License at
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
** WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**
** See the License for the specific language governing permissions and
** limitations under the License.
**
******************************************************************************/
#include "Ver.h"
#include "esif.h"
#include "esif_uf_app_iface.h"
#include "esif_uf_iface.h"
#include "esif_uf_esif_iface.h"
#include "esif_uf_app_event_type.h"
#include "esif_data_misc.h"
#include "Dptf.h"
#include "DptfManager.h"
#include "PolicyManager.h"
#include "ParticipantManager.h"
#include "WorkItemQueueManager.h"
#include "WIAll.h"
#include "IndexContainer.h"
#include "EsifDataString.h"
#include "EsifServices.h"
#include "EsifDataGuid.h"
#include "EsifDataUInt32.h"

static const Guid DptfAppGuid(0x8f, 0x0d, 0x8c, 0x59, 0xad, 0x8d, 0x4d, 0x82, 0xaa, 0x25, 0x46, 0xd3, 0xc0, 0x83, 0x30, 0x5b);

UInt32 getUInt32FromEsifDataGuidEvent(const esif::EsifDataPtr esifDataPtr)
{
    if ((esifDataPtr == nullptr) ||
        (esifDataPtr->type != ESIF_DATA_STRUCTURE) ||
        (esifDataPtr->buf_ptr == nullptr) ||
        (esifDataPtr->buf_len < sizeof(esif_data_guid_event)) ||
        (esifDataPtr->data_len < sizeof(esif_data_guid_event)))
    {
        throw dptf_exception("Error while trying to extract UInt32 parameter.");
    }

    esif_data_guid_event* esifDataGuidEvent = (esif_data_guid_event*)(esifDataPtr->buf_ptr);
    UInt32 value = *((UInt32*)(esifDataGuidEvent->event_context));
    return value;
}

//
// Implement the required interface
//

extern "C"
{
    static eEsifError GetDptfAbout(esif::EsifDataPtr dataPtr)
    {
        return FillDataPtrWithString(dataPtr, "About DPTF");
    }

    static eEsifError GetDptfDescription(esif::EsifDataPtr dataPtr)
    {
        return FillDataPtrWithString(dataPtr, "DPTF application description");
    }

    static eEsifError GetDptfGuid(esif::EsifDataPtr appGuidPtr)
    {
        if (appGuidPtr->buf_len >= ESIF_GUID_LEN)
        {
            appGuidPtr->type = ESIF_DATA_GUID;
            esif_ccb_memcpy(appGuidPtr->buf_ptr, DptfAppGuid, ESIF_GUID_LEN);
            appGuidPtr->data_len = ESIF_GUID_LEN;
            return ESIF_OK;
        }
        else
        {
            return ESIF_E_NEED_LARGER_BUFFER;
        }
    }

    static eEsifError GetDptfName(esif::EsifDataPtr dataPtr)
    {
        return FillDataPtrWithString(dataPtr, "DPTF");
    }

    static eEsifError GetDptfVersion(esif::EsifDataPtr dataPtr)
    {
        return FillDataPtrWithString(dataPtr, VERSION_STR);
    }

    static eEsifError DptfAllocateHandle(void** appHandleLocation)
    {
        DptfManager* dptfManager = nullptr;

        try
        {
            dptfManager = new DptfManager();
            *appHandleLocation = static_cast<void*>(dptfManager);
        }
        catch (...)
        {
            dptfManager = nullptr;
            *appHandleLocation = nullptr;
        }

        return (dptfManager != nullptr) ? ESIF_OK : ESIF_E_UNSPECIFIED;
    }

    static eEsifError DptfCreate(EsifInterfacePtr esifInterfacePtr, const void* esifHandle, const void* appHandle,
        const AppDataPtr appData, const eAppState appInitialState)
    {
        eEsifError rc = ESIF_OK;

        // Make sure we received what we are expecting from EISF.  We can't start the application if we don't have
        // the ESIF interface pointers.  In this case we will check everything manually here instead of in a constructor.
        // If this fails we can't throw an exception or log a message since the infrastructure isn't up.  All we can do
        // is return an error.
        if (esifInterfacePtr == nullptr ||
            esifInterfacePtr->fIfaceType != eIfaceTypeEsifService ||
            esifInterfacePtr->fIfaceVersion != ESIF_INTERFACE_VERSION ||
            esifInterfacePtr->fIfaceSize != (UInt16)sizeof(EsifInterface) ||
            esifInterfacePtr->fGetConfigFuncPtr == nullptr ||
            esifInterfacePtr->fSetConfigFuncPtr == nullptr ||
            esifInterfacePtr->fPrimitiveFuncPtr == nullptr ||
            esifInterfacePtr->fWriteLogFuncPtr == nullptr ||
            esifInterfacePtr->fRegisterEventFuncPtr == nullptr ||
            esifInterfacePtr->fUnregisterEventFuncPtr == nullptr ||
            appHandle == nullptr ||
            appData == nullptr)
        {
            rc = ESIF_E_UNSPECIFIED;
        }
        else
        {
            try
            {
                esifInterfacePtr->fWriteLogFuncPtr(esifHandle, appHandle, nullptr, nullptr,
                    EsifDataString("DptfCreate:  Initialization starting."), eLogType::eLogTypeDebug);

                // Creating the DptfManager will start the framework.  When this call returns the work item
                // manager is up and running and the polices have been created.  All future work will execute in the
                // context of a work item and will only take place on the work item thread.
                Bool enabled = (appInitialState == eAppState::eAppStateEnabled);
                std::string dptfHomeDirectoryPath = EsifDataString(appData->fPathHome);
                DptfManager* dptfManager = (DptfManager*)appHandle;
                dptfManager->createDptfManager(esifHandle, esifInterfacePtr, dptfHomeDirectoryPath, enabled);

                esifInterfacePtr->fWriteLogFuncPtr(esifHandle, appHandle, nullptr, nullptr,
                    EsifDataString("DptfCreate: Initialization completed."), eLogType::eLogTypeDebug);
            }
            catch (...)
            {
                esifInterfacePtr->fWriteLogFuncPtr(esifHandle, appHandle, nullptr, nullptr,
                    EsifDataString("DptfCreate: Initialization failed."), eLogType::eLogTypeFatal);
                rc = ESIF_E_UNSPECIFIED;
            }
        }

        return rc;
    }

    static eEsifError DptfDestroy(void* appHandle)
    {
        eEsifError rc = ESIF_OK;

        try
        {
            DptfManager* dptfManager = (DptfManager*)appHandle;
            delete dptfManager;
        }
        catch (...)
        {
            rc = ESIF_E_UNSPECIFIED;
        }

        return rc;
    }

    static eEsifError GetDptfBanner(const void* appHandle, esif::EsifDataPtr dataPtr)
    {
        return FillDataPtrWithString(dataPtr, "DPTF application banner");
    }

    static eEsifError GetDptfPrompt(const void* appHandle, esif::EsifDataPtr dataPtr)
    {
        return FillDataPtrWithString(dataPtr, "DPTF application prompt [not supported]");
    }

    static eEsifError DptfCommand(const void* appHandle, const esif::EsifDataPtr request,
        const esif::EsifDataPtr response, esif_string appParseContext)
    {
        return ESIF_E_NOT_SUPPORTED;
    }

    static eEsifError SetDptfState(const void* appHandle, const eAppState appState)
    {
        // FIXME after alpha
        // throw not_implemented()

        //DptfManager* dptfManager = (DptfManager*)appHandle;
        //if (dptfManager->isDptfShuttingDown() == true)
        //{
        //    return ESIF_E_UNSPECIFIED;
        //}

        return ESIF_OK;
    }

    static eEsifError GetDptfStatus(const void* appHandle, const eAppStatusCommand command,
        const UInt32 appStatusIn, esif::EsifDataPtr appStatusOut)
    {
        DptfManager* dptfManager = (DptfManager*)appHandle;
        if ((dptfManager == nullptr) || (dptfManager->isAvailable() == false))
        {
            return ESIF_E_UNSPECIFIED;
        }

        eEsifError rc = ESIF_E_UNSPECIFIED;

        try
        {
            WorkItem* workItem = new WIDptfGetStatus(dptfManager, command, appStatusIn, appStatusOut, &rc);
            dptfManager->getWorkItemQueueManager()->enqueueImmediateWorkItemAndWait(workItem);
        }
        catch (...)
        {
        }

        return rc;
    }

    static eEsifError ParticipantAllocateHandle(const void* appHandle, void** participantHandleLocation)
    {
        DptfManager* dptfManager = (DptfManager*)appHandle;
        if ((dptfManager == nullptr) || (dptfManager->isAvailable() == false))
        {
            return ESIF_E_UNSPECIFIED;
        }

        eEsifError rc = ESIF_E_UNSPECIFIED;
        UIntN newParticipantIndex = Constants::Esif::NoParticipant;

        try
        {
            WorkItem* workItem = new WIParticipantAllocate(dptfManager, &newParticipantIndex);
            dptfManager->getWorkItemQueueManager()->enqueueImmediateWorkItemAndWait(workItem);
        }
        catch (...)
        {
            newParticipantIndex = Constants::Esif::NoParticipant;
        }

        if (newParticipantIndex != Constants::Esif::NoParticipant)
        {
            try
            {
                *participantHandleLocation = (void*)(dptfManager->getIndexContainer()->getIndexPtr(newParticipantIndex));
                rc = ESIF_OK;
            }
            catch (...)
            {
            }
        }

        return rc;
    }

    static eEsifError ParticipantCreate(const void* appHandle, const void* participantHandle,
        const AppParticipantDataPtr participantDataPtr, const eParticipantState particiapntInitialState)
    {
        DptfManager* dptfManager = (DptfManager*)appHandle;
        if ((dptfManager == nullptr) || (dptfManager->isAvailable() == false))
        {
            return ESIF_E_UNSPECIFIED;
        }

        Bool participantCreated = false;

        try
        {
            Bool participantEnabled = (particiapntInitialState == eParticipantState::eParticipantStateEnabled);

            WorkItem* workItem = new WIParticipantCreate(dptfManager,
                dptfManager->getIndexContainer()->getIndex((IndexStructPtr)participantHandle),
                participantDataPtr, participantEnabled, &participantCreated);
            dptfManager->getWorkItemQueueManager()->enqueueImmediateWorkItemAndWait(workItem);
        }
        catch (...)
        {
            participantCreated = false;
        }

        return (participantCreated == true) ? ESIF_OK : ESIF_E_UNSPECIFIED;
    }

    eEsifError ParticipantDestroy(const void* appHandle, const void* participantHandle)
    {
        DptfManager* dptfManager = (DptfManager*)appHandle;
        if ((dptfManager == nullptr) || (dptfManager->isAvailable() == false))
        {
            return ESIF_E_UNSPECIFIED;
        }

        eEsifError rc = ESIF_OK;

        try
        {
            WorkItem* workItem = new WIParticipantDestroy(dptfManager,
                dptfManager->getIndexContainer()->getIndex((IndexStructPtr)participantHandle));
            dptfManager->getWorkItemQueueManager()->enqueueImmediateWorkItemAndWait(workItem);
        }
        catch (...)
        {
            rc = ESIF_E_UNSPECIFIED;
        }

        return rc;
    }

    static eEsifError ParticipantSetState(const void* appHandle, const void* participantHandle,
        eParticipantState participantState )
    {
        // FIXME after alpha
        // throw not_implemented()

        DptfManager* dptfManager = (DptfManager*)appHandle;
        if ((dptfManager == nullptr) || (dptfManager->isAvailable() == false))
        {
            return ESIF_E_UNSPECIFIED;
        }

        return ESIF_OK;
    }

    static eEsifError DomainAllocateHandle(const void* appHandle, const void* participantHandle,
        void** domainHandleLocation)
    {
        DptfManager* dptfManager = (DptfManager*)appHandle;
        if ((dptfManager == nullptr) || (dptfManager->isAvailable() == false))
        {
            return ESIF_E_UNSPECIFIED;
        }

        eEsifError rc = ESIF_E_UNSPECIFIED;
        UIntN newDomainIndex = Constants::Esif::NoDomain;

        try
        {
            WorkItem* workItem = new WIDomainAllocate(dptfManager,
                dptfManager->getIndexContainer()->getIndex((IndexStructPtr)participantHandle),
                &newDomainIndex);
            dptfManager->getWorkItemQueueManager()->enqueueImmediateWorkItemAndWait(workItem);
        }
        catch (...)
        {
            newDomainIndex = Constants::Esif::NoDomain;
        }

        if (newDomainIndex != Constants::Esif::NoDomain)
        {
            try
            {
                *domainHandleLocation = (void*)(dptfManager->getIndexContainer()->getIndexPtr(newDomainIndex));
                rc = ESIF_OK;
            }
            catch (...)
            {
            }
        }

        return rc;
    }

    static eEsifError DomainCreate(const void* appHandle, const void* participantHandle, const void* domainHandle,
        const AppDomainDataPtr domainDataPtr, const eDomainState domainInitialState)
    {
        DptfManager* dptfManager = (DptfManager*)appHandle;
        if ((dptfManager == nullptr) || (dptfManager->isAvailable() == false))
        {
            return ESIF_E_UNSPECIFIED;
        }

        Bool domainCreated = false;

        try
        {
            Bool domainEnabled = (domainInitialState == eDomainState::eDomainStateEnabled);

            WorkItem* workItem = new WIDomainCreate(dptfManager,
                dptfManager->getIndexContainer()->getIndex((IndexStructPtr)participantHandle),
                dptfManager->getIndexContainer()->getIndex((IndexStructPtr)domainHandle),
                domainDataPtr, domainEnabled, &domainCreated);
            dptfManager->getWorkItemQueueManager()->enqueueImmediateWorkItemAndWait(workItem);
        }
        catch (...)
        {
            domainCreated = false;
        }

        return (domainCreated == true) ? ESIF_OK : ESIF_E_UNSPECIFIED;
    }

    static eEsifError DomainDestroy(const void* appHandle, const void* participantHandle, const void* domainHandle)
    {
        DptfManager* dptfManager = (DptfManager*)appHandle;
        if ((dptfManager == nullptr) || (dptfManager->isAvailable() == false))
        {
            return ESIF_E_UNSPECIFIED;
        }

        eEsifError rc = ESIF_OK;

        try
        {
            WorkItem* workItem = new WIDomainDestroy(dptfManager,
                dptfManager->getIndexContainer()->getIndex((IndexStructPtr)participantHandle),
                dptfManager->getIndexContainer()->getIndex((IndexStructPtr)domainHandle));
            dptfManager->getWorkItemQueueManager()->enqueueImmediateWorkItemAndWait(workItem);
        }
        catch (...)
        {
            rc = ESIF_E_UNSPECIFIED;
        }

        return rc;
    }

    static eEsifError DomainSetState(const void* appHandle, const void* participantHandle, const void* domainHandle,
        const eDomainState domainState)
    {
        // FIXME after alpha release
        // throw implement_me()

        DptfManager* dptfManager = (DptfManager*)appHandle;
        if ((dptfManager == nullptr) || (dptfManager->isAvailable() == false))
        {
            return ESIF_E_UNSPECIFIED;
        }

        return ESIF_OK;
    }

    static eEsifError DptfEvent(const void* appHandle, const void* participantHandle, const void* domainHandle,
        const esif::EsifDataPtr esifEventDataPtr, const esif::EsifDataPtr eventGuid)
    {
        DptfManager* dptfManager = (DptfManager*)appHandle;
        if ((dptfManager == nullptr) || (dptfManager->isAvailable() == false))
        {
            return ESIF_E_UNSPECIFIED;
        }

        Guid guid;
        FrameworkEvent::Type frameworkEvent = FrameworkEvent::Max;

        try
        {
            guid = EsifDataGuid(*eventGuid);
            frameworkEvent = FrameworkEventInfo::instance()->getFrameworkEventType(guid);
        }
        catch (...)
        {
            ManagerMessage message = ManagerMessage(dptfManager, FLF,
                "Error while trying to convert event guid to DPTF framework event.");
            if (guid.isValid())
            {
                message.setEsifEventGuid(guid);
            }
            dptfManager->getEsifServices()->writeMessageError(message);
            return ESIF_E_UNSPECIFIED;
        }

        IndexContainer* idx = dptfManager->getIndexContainer();
        UIntN participantIndex = idx->getIndex((IndexStructPtr)participantHandle);
        UIntN domainIndex = idx->getIndex((IndexStructPtr)domainHandle);

#ifdef ONLY_LOG_TEMPERATURE_THRESHOLDS
        // Added to help debug issue with missing temperature threshold events
        if (frameworkEvent == DomainTemperatureThresholdCrossed)
        {
            ManagerMessage temperatureMessage = ManagerMessage(dptfManager, FLF, "Received temperature threshold crossed event");
            temperatureMessage.setParticipantAndDomainIndex(participantIndex, domainIndex);
            temperatureMessage.setFrameworkEvent(frameworkEvent);
            dptfManager->getEsifServices()->writeMessageWarning(temperatureMessage, MessageCategory::TemperatureThresholds);
        }
#endif

        ManagerMessage startMessage = ManagerMessage(dptfManager, FLF, "Starting function execution");
        startMessage.setParticipantAndDomainIndex(participantIndex, domainIndex);
        startMessage.setFrameworkEvent(frameworkEvent);
        dptfManager->getEsifServices()->writeMessageDebug(startMessage);

        eEsifError rc = ESIF_OK;

        try
        {
            WorkItem* wi = nullptr;
            UInt32 uint32param = Constants::Invalid;

            switch (frameworkEvent)
            {
                case FrameworkEvent::DptfConnectedStandbyEntry:
                    wi = new WIDptfConnectedStandbyEntry(dptfManager);
                    break;
                case FrameworkEvent::DptfConnectedStandbyExit:
                    wi = new WIDptfConnectedStandbyExit(dptfManager);
                    break;
                case FrameworkEvent::ParticipantSpecificInfoChanged:
                    wi = new WIParticipantSpecificInfoChanged(dptfManager, participantIndex);
                    break;
                case FrameworkEvent::DomainConfigTdpCapabilityChanged:
                    wi = new WIDomainConfigTdpCapabilityChanged(dptfManager, participantIndex, domainIndex);
                    break;
                case FrameworkEvent::DomainCoreControlCapabilityChanged:
                    wi = new WIDomainCoreControlCapabilityChanged(dptfManager, participantIndex, domainIndex);
                    break;
                case FrameworkEvent::DomainDisplayControlCapabilityChanged:
                    wi = new WIDomainDisplayControlCapabilityChanged(dptfManager, participantIndex, domainIndex);
                    break;
                case FrameworkEvent::DomainDisplayStatusChanged:
                    wi = new WIDomainDisplayStatusChanged(dptfManager, participantIndex, domainIndex);
                    break;
                case FrameworkEvent::DomainPerformanceControlCapabilityChanged:
                    wi = new WIDomainPerformanceControlCapabilityChanged(dptfManager, participantIndex, domainIndex);
                    break;
                case FrameworkEvent::DomainPerformanceControlsChanged:
                    wi = new WIDomainPerformanceControlsChanged(dptfManager, participantIndex, domainIndex);
                    break;
                case FrameworkEvent::DomainPowerControlCapabilityChanged:
                    wi = new WIDomainPowerControlCapabilityChanged(dptfManager, participantIndex, domainIndex);
                    break;
                case FrameworkEvent::DomainPriorityChanged:
                    wi = new WIDomainPriorityChanged(dptfManager, participantIndex, domainIndex);
                    break;
                case FrameworkEvent::DomainTemperatureThresholdCrossed:
                    wi = new WIDomainTemperatureThresholdCrossed(dptfManager, participantIndex, domainIndex);
                    break;
                case FrameworkEvent::PolicyActiveRelationshipTableChanged:
                    wi = new WIPolicyActiveRelationshipTableChanged(dptfManager);
                    break;
                case FrameworkEvent::PolicyThermalRelationshipTableChanged:
                    wi = new WIPolicyThermalRelationshipTableChanged(dptfManager);
                    break;
                case FrameworkEvent::PolicyForegroundApplicationChanged:
                    wi = new WIPolicyForegroundApplicationChanged(dptfManager, EsifDataString(*esifEventDataPtr));
                    break;
                case FrameworkEvent::PolicyOperatingSystemLpmModeChanged:
                    uint32param = getUInt32FromEsifDataGuidEvent(esifEventDataPtr);
                    wi = new WIPolicyOperatingSystemLpmModeChanged(dptfManager, uint32param);
                    break;
                case FrameworkEvent::PolicyPlatformLpmModeChanged:
                    wi = new WIPolicyPlatformLpmModeChanged(dptfManager);
                    break;
                case FrameworkEvent::PolicyOperatingSystemConfigTdpLevelChanged:
                    uint32param = getUInt32FromEsifDataGuidEvent(esifEventDataPtr);
                    wi = new WIPolicyOperatingSystemConfigTdpLevelChanged(dptfManager, uint32param);
                    break;
                case FrameworkEvent::PolicyCoolingModePowerLimitChanged:
                    uint32param = getUInt32FromEsifDataGuidEvent(esifEventDataPtr);
                    wi = new WIPolicyCoolingModePowerLimitChanged(dptfManager, (CoolingModePowerLimit::Type)uint32param);
                    break;
                case FrameworkEvent::PolicyCoolingModeAcousticLimitChanged:
                    uint32param = getUInt32FromEsifDataGuidEvent(esifEventDataPtr);
                    wi = new WIPolicyCoolingModeAcousticLimitChanged(dptfManager, (CoolingModeAcousticLimit::Type)uint32param);
                    break;
                case FrameworkEvent::PolicyCoolingModePolicyChanged:
                    uint32param = getUInt32FromEsifDataGuidEvent(esifEventDataPtr);
                    wi = new WIPolicyCoolingModePolicyChanged(dptfManager, (CoolingMode::Type)uint32param);
                    break;
                case FrameworkEvent::PolicyPassiveTableChanged:
                    wi = new WIPolicyPassiveTableChanged(dptfManager);
                    break;
                case FrameworkEvent::PolicySensorOrientationChanged:
                    uint32param = getUInt32FromEsifDataGuidEvent(esifEventDataPtr);
                    wi = new WIPolicySensorOrientationChanged(dptfManager, (SensorOrientation::Type)uint32param);
                    break;
                case FrameworkEvent::PolicySensorSpatialOrientationChanged:
                    uint32param = getUInt32FromEsifDataGuidEvent(esifEventDataPtr);
                    wi = new WIPolicySensorSpatialOrientationChanged(dptfManager, (SensorSpatialOrientation::Type)uint32param);
                    break;
                case FrameworkEvent::PolicySensorProximityChanged:
                    uint32param = getUInt32FromEsifDataGuidEvent(esifEventDataPtr);
                    wi = new WIPolicySensorProximityChanged(dptfManager, (SensorProximity::Type)uint32param);
                    break;
                default:
                {
                    ManagerMessage message = ManagerMessage(dptfManager, FLF, "Received unexpected event");
                    message.setParticipantAndDomainIndex(participantIndex, domainIndex);
                    message.setFrameworkEvent(frameworkEvent);
                    dptfManager->getEsifServices()->writeMessageError(message);
                    rc = ESIF_E_NOT_SUPPORTED;
                    break;
                }
            }

            if (wi != nullptr)
            {
                dptfManager->getWorkItemQueueManager()->enqueueImmediateWorkItemAndReturn(wi);
            }
        }
        catch (duplicate_work_item ex)
        {
            ManagerMessage message = ManagerMessage(dptfManager, FLF, "Discarding duplicate event.  Already in immediate queue.");
            message.setParticipantAndDomainIndex(participantIndex, domainIndex);
            message.setFrameworkEvent(frameworkEvent);
            message.setExceptionCaught("WorkItemQueueManager::enqueueImmediateWorkItemAndReturn", ex.what());
            dptfManager->getEsifServices()->writeMessageDebug(message);
            rc = ESIF_OK;
        }
        catch (std::exception ex)
        {
            ManagerMessage message = ManagerMessage(dptfManager, FLF, "Error while trying to create work item for event received from ESIF.");
            message.setParticipantAndDomainIndex(participantIndex, domainIndex);
            message.setFrameworkEvent(frameworkEvent);
            message.setExceptionCaught("DptfEvent", ex.what());
            dptfManager->getEsifServices()->writeMessageError(message);
            rc = ESIF_E_UNSPECIFIED;
        }

        return rc;
    }

    dptf_export eEsifError GetApplicationInterface(AppInterfacePtr appInterfacePtr)
    {
        // header
        appInterfacePtr->fIfaceType = eIfaceTypeApplication;
        appInterfacePtr->fIfaceSize = (UInt16)sizeof(AppInterface);
        appInterfacePtr->fIfaceVersion = ESIF_INTERFACE_VERSION;

        /* Application */
        appInterfacePtr->fAppAllocateHandleFuncPtr = DptfAllocateHandle;
        appInterfacePtr->fAppCreateFuncPtr = DptfCreate;
        appInterfacePtr->fAppDestroyFuncPtr = DptfDestroy;

        appInterfacePtr->fAppCommandFuncPtr = DptfCommand;
        appInterfacePtr->fAppGetAboutFuncPtr = GetDptfAbout;
        appInterfacePtr->fAppGetBannerFuncPtr = GetDptfBanner;
        appInterfacePtr->fAppGetDescriptionFuncPtr = GetDptfDescription;
        appInterfacePtr->fAppGetGuidFuncPtr = GetDptfGuid;
        appInterfacePtr->fAppGetNameFuncPtr = GetDptfName;
        appInterfacePtr->fAppGetPromptFuncPtr = GetDptfPrompt;
        appInterfacePtr->fAppGetStatusFuncPtr = GetDptfStatus;
        appInterfacePtr->fAppGetVersionFuncPtr = GetDptfVersion;
        appInterfacePtr->fAppSetStateFuncPtr = SetDptfState;

        /* Participant */
        appInterfacePtr->fParticipantAllocateHandleFuncPtr = ParticipantAllocateHandle;
        appInterfacePtr->fParticipantCreateFuncPtr = ParticipantCreate;
        appInterfacePtr->fParticipantDestroyFuncPtr = ParticipantDestroy;
        appInterfacePtr->fParticipantSetStateFuncPtr = ParticipantSetState;

        /* Domain */
        appInterfacePtr->fDomainAllocateHandleFuncPtr = DomainAllocateHandle;
        appInterfacePtr->fDomainCreateFuncPtr = DomainCreate;
        appInterfacePtr->fDomainDestroyFuncPtr = DomainDestroy;
        appInterfacePtr->fDomainSetStateFuncPtr = DomainSetState;

        /* Event */
        appInterfacePtr->fAppEventFuncPtr = DptfEvent;

        return ESIF_OK;
    }
} // extern "C"