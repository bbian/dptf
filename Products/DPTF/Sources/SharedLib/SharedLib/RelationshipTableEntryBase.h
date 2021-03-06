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
#include <string>
#include "BasicTypes.h"
#include "Dptf.h"

class RelationshipTableEntryBase
{
public:

    RelationshipTableEntryBase(const std::string& sourceDeviceAcpiScope, const std::string& targetDeviceAcpiScope);
    virtual ~RelationshipTableEntryBase();

    const std::string& sourceDeviceAcpiScope() const;
    UIntN sourceDeviceIndex() const;
    const std::string& targetDeviceAcpiScope() const;
    UIntN targetDeviceIndex() const;
    void associateParticipant(std::string deviceAcpiScope, UIntN deviceIndex);
    void disassociateParticipant(UIntN deviceIndex);

private:

    std::string m_sourceDeviceAcpiScope;
    UIntN m_sourceDeviceIndex;
    std::string m_targetDeviceAcpiScope;
    UIntN m_targetDeviceIndex;
};