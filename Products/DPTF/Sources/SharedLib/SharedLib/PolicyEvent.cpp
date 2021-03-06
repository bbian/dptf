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
#include "PolicyEvent.h"
#include "Dptf.h"

//
// FIXME: the code in this file may be called enough that we should change it to an index based lookup.  Need
// to run a profiler and see.
//

#define CASE(eventType) \
    case eventType: return FrameworkEvent::eventType;

namespace PolicyEvent
{
    // FIXME:  update to use hash table

    FrameworkEvent::Type ToFrameworkEvent(PolicyEvent::Type policyEventType)
    {
        switch (policyEventType)
        {
            CASE(DptfConnectedStandbyEntry)
            CASE(DptfConnectedStandbyExit)
            CASE(DomainConfigTdpCapabilityChanged)
            CASE(DomainCoreControlCapabilityChanged)
            CASE(DomainDisplayControlCapabilityChanged)
            CASE(DomainDisplayStatusChanged)
            CASE(DomainPerformanceControlCapabilityChanged)
            CASE(DomainPerformanceControlsChanged)
            CASE(DomainPowerControlCapabilityChanged)
            CASE(DomainPriorityChanged)
            CASE(DomainTemperatureThresholdCrossed)
            CASE(ParticipantSpecificInfoChanged)
            CASE(PolicyActiveRelationshipTableChanged)
            CASE(PolicyThermalRelationshipTableChanged)
            CASE(PolicyInitiatedCallback)
            CASE(PolicyForegroundApplicationChanged)
            CASE(PolicyOperatingSystemLpmModeChanged)
            CASE(PolicyPlatformLpmModeChanged)
            CASE(PolicyOperatingSystemConfigTdpLevelChanged)
            CASE(PolicyCoolingModePowerLimitChanged)
            CASE(PolicyCoolingModeAcousticLimitChanged)
            CASE(PolicyCoolingModePolicyChanged)
            CASE(PolicyPassiveTableChanged)
            CASE(PolicySensorOrientationChanged)
            CASE(PolicySensorSpatialOrientationChanged)
            CASE(PolicySensorProximityChanged)
            default:
                throw dptf_exception("PolicyEvent::Type is invalid.");
        }
    }

    Bool RequiresEsifEventRegistration(PolicyEvent::Type policyEventType)
    {
        return ((policyEventType == PolicyEvent::PolicyActiveRelationshipTableChanged) ||
                (policyEventType == PolicyEvent::PolicyThermalRelationshipTableChanged) ||
                (policyEventType == PolicyEvent::PolicyForegroundApplicationChanged) ||
                (policyEventType == PolicyEvent::PolicyOperatingSystemLpmModeChanged) ||
                (policyEventType == PolicyEvent::PolicyPlatformLpmModeChanged) ||
                (policyEventType == PolicyEvent::PolicyOperatingSystemConfigTdpLevelChanged) ||
                (policyEventType == PolicyEvent::PolicyCoolingModePowerLimitChanged) ||
                (policyEventType == PolicyEvent::PolicyCoolingModeAcousticLimitChanged) ||
                (policyEventType == PolicyEvent::PolicyCoolingModePolicyChanged) ||
                (policyEventType == PolicyEvent::PolicyPassiveTableChanged) ||
                (policyEventType == PolicyEvent::PolicySensorOrientationChanged) ||
                (policyEventType == PolicyEvent::PolicySensorSpatialOrientationChanged) ||
                (policyEventType == PolicyEvent::PolicySensorProximityChanged));
    }
}