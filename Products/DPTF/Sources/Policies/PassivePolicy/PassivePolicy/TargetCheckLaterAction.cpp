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
#include "TargetCheckLaterAction.h"
using namespace std;

TargetCheckLaterAction::TargetCheckLaterAction(
    PolicyServicesInterfaceContainer& policyServices, std::shared_ptr<TimeInterface> time,
    ParticipantTracker& participantTracker, ThermalRelationshipTable& trt,
    std::shared_ptr<CallbackScheduler> callbackScheduler, TargetMonitor& targetMonitor,
    UtilizationStatus utilizationBiasThreshold, UIntN target)
    : TargetActionBase(policyServices, time, participantTracker, trt, callbackScheduler, targetMonitor, 
    utilizationBiasThreshold, target)
{
}

TargetCheckLaterAction::~TargetCheckLaterAction()
{
}

void TargetCheckLaterAction::execute()
{
    try
    {
        // schedule a callback as soon as possible
        postDebugMessage(PolicyMessage(FLF, "Attempting to schedule callback for target participant.", getTarget()));
        getCallbackScheduler()->scheduleCallbackAfterShortestSamplePeriod(getTarget());
    }
    catch (...)
    {
        postWarningMessage(PolicyMessage(FLF, "Failed to schedule callback for target participant.", getTarget()));
    }
}
