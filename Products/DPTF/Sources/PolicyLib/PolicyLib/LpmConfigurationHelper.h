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

#include "LpmEntry.h"
#include "PolicyServicesInterfaceContainer.h"

using namespace std;

class dptf_export LpmConfigurationHelper
{
public:
    LpmConfigurationHelper();
    ~LpmConfigurationHelper();

    PolicyServicesInterfaceContainer& getPolicyServices(void);
    void setPolicyServices(PolicyServicesInterfaceContainer policyServices);

    vector<UIntN> findLpmEntriesWithAcpiScope(
        std::string acpiScope,
        const vector<LpmEntry>& lpmEntries 
        ) const;
    vector<UIntN> findLpmEntriesWithParticipantIndex(
        UIntN participantIndex,
        const vector<LpmEntry>& lpmEntries
        ) const;
    vector<UIntN> findLpmEntriesWithDomainType(
        DomainType::Type domainType,
        const vector<LpmEntry>& lpmEntries
        ) const;

protected:
    void postInfoMessage(const PolicyMessage& message);
    void postWarningMessage(const PolicyMessage& message);
    void postErrorMessage(const PolicyMessage& message);
    void postDebugMessage(const PolicyMessage& message);

private:

    PolicyServicesInterfaceContainer m_policyServices;

};

