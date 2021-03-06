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

#include "ConfigTdpControl.h"
#include "BasicTypes.h"
#include <vector>

class XmlNode;

class ConfigTdpControlSet final
{
public:

    ConfigTdpControlSet(std::vector<ConfigTdpControl> configTdpControl, UIntN nominalControlIndex);
    UIntN getCount(void) const;
    const ConfigTdpControl& operator[](UIntN index) const;
    UIntN getNominalControlIndex(void) const;
    Bool operator==(const ConfigTdpControlSet& rhs) const;
    XmlNode* getXml(void);

private:

    std::vector<ConfigTdpControl> m_configTdpControl;
    UIntN m_nominalControlIndex;
};