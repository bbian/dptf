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
#pragma once

#include "PolicyServices.h"
#include "ParticipantSetSpecificInfoInterface.h"

class PolicyServicesParticipantSetSpecificInfo final : public PolicyServices, public ParticipantSetSpecificInfoInterface
{
public:

    PolicyServicesParticipantSetSpecificInfo(DptfManager* dptfManager, UIntN policyIndex);

    // _DTI
    virtual void setParticipantDeviceTemperatureIndication(UIntN participantIndex, const Temperature& temperature) override final;

    // _SCP
    virtual void setParticipantCoolingPolicy(UIntN participantIndex, const CoolingPreference& coolingPreference) override final;
};