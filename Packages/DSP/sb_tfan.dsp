################################################################################
## Copyright (c) 2013 Intel Corporation All Rights Reserved
##
## Licensed under the Apache License, Version 2.0 (the "License"); you may not
## use this file except in compliance with the License.
##
## You may obtain a copy of the License at
##     http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS"BASIS, WITHOUT
## WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
##
## See the License for the specific language governing permissions and
## limitations under the License.
##
################################################################################
#
# Eco-System Independent Framework v1 (ESIF)
# ESIF Device Support Package (DSP)
#
# DSP Package: sb_tfan
#      Format: DSP Compiler
#     Version: 1.0
#        HMAC: 0000000000000000000000000000000000000000
#
# =====                            ======
# ===== AUTO GENERATED DO NOT EDIT ======
# =====                            ======
#
#
# H=Name, VerMaj, VerMin, Description, Type, BusEnum, acpiDevice, acpiUID, acpiType, acpiScope, pciVendorID, pciDeviceID, pciBus, pciDevice, pciFunction, pciRevision, pciClass, pciSubClass, pciProgIF
# T=actionType, tempXform, tempC1, tempC2, powerXform, timeXform
# E=alias, eventKey, eventType, eventGroup, eventDataType, eventGUID
# D=name, description, qualifier, domainType, priority
# C=capability, capabilityByte Array
# P=Primitive, Qualifier, Instance, Operation, RequestType, ReturnType
# A=ActionPriority, ActionType, IsKernel, p1, p2, p3, p4, p5
#
H,"sb_tfan",1,0,"Fan Device","EF0328E6-AC05-43F9-9291-16C0810EE05B",0,"INT3404","","","","","","","","","","","",""
T,1,6,,,1,8
T,4,5,,,0,8
T,29,6,,,1,8
#
#
D,"DFL","Default Domain","D0","FE9FCDF3-CC97-4C49-A713-890DDB30FFB9",0,4
C,0x1 ,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
#
# GET_DEVICE_DESCRIPTION
P,60,255,1,24,"<schema></schema>",9,"<schema></schema>"
A,0,4,True,"_STR",,,,
# GET_DEVICE_HARDWARE_ID
P,53,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,4,True,"_HID",,,,
# GET_DEVICE_STATUS
P,88,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,4,True,"_STA",,,,
# GET_DEVICE_UNIQUE_ID
P,67,255,1,24,"<schema></schema>",8,"<schema></schema>"
A,0,4,True,"_UID",,,,
# GET_FAN_INFORMATION
P,84,255,1,24,"<schema></schema>",7,"<schema></schema>"
A,0,4,True,"_FIF",,,,
# GET_FAN_PERFORMANCE_STATES
P,85,255,1,24,"<schema></schema>",7,"<schema></schema>"
A,0,4,True,"_FPS",,,,
# GET_FAN_STATUS
P,86,255,1,24,"<schema></schema>",7,"<schema></schema>"
A,0,4,True,"_FST",,,,
# SET_FAN_LEVEL
P,87,255,2,3,"<schema></schema>",24,"<schema></schema>"
A,0,4,True,"_FSL",,,,
