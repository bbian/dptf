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
#include "DomainCoreControl_001.h"
#include "XmlNode.h"

DomainCoreControl_001::DomainCoreControl_001(ParticipantServicesInterface* participantServicesInterface) :
    m_participantServicesInterface(participantServicesInterface)
{
    initializeDataStructures();
}

CoreControlStaticCaps DomainCoreControl_001::getCoreControlStaticCaps(UIntN participantIndex, UIntN domainIndex)
{
    checkAndCreateControlStructures(domainIndex);

    return *m_coreControlStaticCaps;
}

CoreControlDynamicCaps DomainCoreControl_001::getCoreControlDynamicCaps(UIntN participantIndex, UIntN domainIndex)
{
    checkAndCreateControlStructures(domainIndex);

    return *m_coreControlDynamicCaps;
}

CoreControlLpoPreference DomainCoreControl_001::getCoreControlLpoPreference(UIntN participantIndex, UIntN domainIndex)
{
    checkAndCreateControlStructures(domainIndex);

    return *m_coreControlLpoPreference;
}

CoreControlStatus DomainCoreControl_001::getCoreControlStatus(UIntN participantIndex, UIntN domainIndex)
{
    if (m_numActiveLogicalProcessors == Constants::Invalid)
    {
        throw dptf_exception("No core control has been set.  No status available.");
    }

    return *m_coreControlStatus;
}

void DomainCoreControl_001::setActiveCoreControl(UIntN participantIndex, UIntN domainIndex, const CoreControlStatus& coreControlStatus)
{
    verifyCoreControlStatus(coreControlStatus);

    m_participantServicesInterface->primitiveExecuteSetAsUInt32(
        esif_primitive_type::SET_ACTIVE_CORE_LIMIT,
        coreControlStatus.getNumActiveLogicalProcessors(),
        domainIndex);

    // Refresh the status
    m_numActiveLogicalProcessors = coreControlStatus.getNumActiveLogicalProcessors();
    delete m_coreControlStatus;
    m_coreControlStatus = new CoreControlStatus(m_numActiveLogicalProcessors);
}

void DomainCoreControl_001::initializeDataStructures(void)
{
    m_coreControlStaticCaps = nullptr;
    m_coreControlDynamicCaps = nullptr;
    m_coreControlLpoPreference = nullptr;
    m_coreControlStatus = nullptr;

    m_numActiveLogicalProcessors = Constants::Invalid;
    m_coreControlStatus = new CoreControlStatus(m_numActiveLogicalProcessors);
}

void DomainCoreControl_001::clearCachedData(void)
{
    delete m_coreControlStaticCaps;
    delete m_coreControlDynamicCaps;
    delete m_coreControlLpoPreference;
    delete m_coreControlStatus;

    initializeDataStructures();
}

XmlNode* DomainCoreControl_001::getXml(UIntN domainIndex)
{
    checkAndCreateControlStructures(domainIndex);

    XmlNode* root = XmlNode::createWrapperElement("core_control");

    root->addChild(m_coreControlStatus->getXml());
    root->addChild(m_coreControlStaticCaps->getXml());
    root->addChild(m_coreControlDynamicCaps->getXml());
    root->addChild(m_coreControlLpoPreference->getXml());
    root->addChild(XmlNode::createDataElement("control_knob_version", "001"));

    return root;
}

void DomainCoreControl_001::createCoreControlDynamicCaps(UIntN domainIndex)
{
    UInt32 minActiveCoreLimit = 1;

    UInt32 maxActiveCoreLimit = m_coreControlStaticCaps->getTotalLogicalProcessors();

    m_coreControlDynamicCaps = new CoreControlDynamicCaps(minActiveCoreLimit, maxActiveCoreLimit);
}

void DomainCoreControl_001::createCoreControlStaticCaps(UIntN domainIndex)
{
    UInt32 logicalCoreCount =
        m_participantServicesInterface->primitiveExecuteGetAsUInt32(
            esif_primitive_type::GET_PROC_LOGICAL_PROCESSOR_COUNT,
            domainIndex);

    m_coreControlStaticCaps = new CoreControlStaticCaps(logicalCoreCount);
}

void DomainCoreControl_001::verifyCoreControlStatus(const CoreControlStatus& coreControlStatus)
{
    if (coreControlStatus.getNumActiveLogicalProcessors() > m_coreControlDynamicCaps->getMaxActiveCores() ||
        coreControlStatus.getNumActiveLogicalProcessors() < m_coreControlDynamicCaps->getMinActiveCores())
    {
        throw dptf_exception("Desired number of cores outside dynamic caps range.");
    }
}

void DomainCoreControl_001::createCoreControlLpoPreference(UIntN domainIndex)
{
    UInt32 dataLength = 0;
    DptfMemory binaryData(Constants::DefaultBufferSize);

    //Build CLPO table
    try
    {
        m_participantServicesInterface->primitiveExecuteGet(
            esif_primitive_type::GET_PROC_CURRENT_LOGICAL_PROCESSOR_OFFLINING,
            ESIF_DATA_BINARY,
            binaryData,
            binaryData.getSize(),
            &dataLength,
            domainIndex);

        m_coreControlLpoPreference = BinaryParse::processorClpoObject(dataLength, binaryData);
    }
    catch (...)
    {
        // CLPO was not found, provide default values
        delete m_coreControlLpoPreference;

        m_participantServicesInterface->writeMessageWarning(
            ParticipantMessage(FLF, "CLPO not found, using defaults."));

        m_coreControlLpoPreference = new CoreControlLpoPreference(true, 0, Percentage(50),
            CoreControlOffliningMode::Smt, CoreControlOffliningMode::Core);
    }

    binaryData.deallocate();
}

void DomainCoreControl_001::checkAndCreateControlStructures(UIntN domainIndex)
{
    if (m_coreControlStaticCaps == nullptr)
    {
        createCoreControlStaticCaps(domainIndex);
    }

    if (m_coreControlDynamicCaps == nullptr)
    {
        createCoreControlDynamicCaps(domainIndex);
    }

    if (m_coreControlLpoPreference == nullptr)
    {
        createCoreControlLpoPreference(domainIndex);
    }
}