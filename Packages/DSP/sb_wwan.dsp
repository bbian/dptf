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
# DSP Package: sb_wwan
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
H,"sb_wwan",1,0,"WWAN Device","6B9F5338-5DCB-4FDC-8E41-2C0985D28FBC",0,"INT3408","","15","","","","","","","","","",""
T,1,6,,,1,8
T,4,5,,,0,8
T,29,6,,,1,8
#
E,"RFCS",0x96A88C88-A778-4484-9FF5-FD46DBDB09C1,33,4,3,0x127FB178-2FF0-4286-8A3F-9161B6E87D57
E,"RFPC",0x740EE466-E3E4-4A9D-B210-C788A19553A4,32,4,24,0xC13C9EAF-9F51-4027-BFE2-E278152D238B
#
D,"DFL","Default Domain","D0","E03D4763-1EC3-4D3C-AFAE-4CFA1D0B42F5",0,15
C,0x6100 ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x1,0x2,0x0
#
# GET_DEVICE_DESCRIPTION
P,60,255,1,24,"<schema></schema>",9,"<schema></schema>"
A,0,4,True,"_STR",,,,
# GET_DEVICE_HARDWARE_ID
P,53,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,4,True,"_HID",,,,
# GET_DEVICE_UNIQUE_ID
P,67,255,1,24,"<schema></schema>",8,"<schema></schema>"
A,0,4,True,"_UID",,,,
# GET_PARTICIPANT_TYPE
P,139,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,4,True,"PTYP",,,,
# GET_RFPROFILE_BIT_ERROR
P,265,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,41,False,16,,,,
A,1,1,True,0,,,,
# GET_RFPROFILE_CENTER_FREQUENCY
P,245,255,1,24,"<schema></schema>",40,"<schema></schema>"
A,0,41,False,0,,,,
A,1,1,True,1500000,,,,
# GET_RFPROFILE_CHANNEL_NUMBER
P,260,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,41,False,1,,,,
A,1,1,True,0,,,,
# GET_RFPROFILE_CLIP_PERCENT_LEFT
P,255,255,2,24,"<schema></schema>",29,"<schema></schema>"
A,0,41,False,2,,,,
A,1,1,True,0,,,,
# GET_RFPROFILE_CLIP_PERCENT_RIGHT
P,256,255,2,24,"<schema></schema>",29,"<schema></schema>"
A,0,41,False,3,,,,
A,1,1,True,0,,,,
# GET_RFPROFILE_CONNECT_STATUS
P,264,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,41,False,4,,,,
A,1,1,True,0,,,,
# GET_RFPROFILE_DEFAULT_CENTER_FREQUENCY
P,254,255,1,24,"<schema></schema>",40,"<schema></schema>"
A,0,41,False,5,,,,
A,1,1,True,1500000,,,,
# GET_RFPROFILE_FREQUENCY_ADJUST_RESOLUTION
P,257,255,1,24,"<schema></schema>",40,"<schema></schema>"
A,0,41,False,6,,,,
A,1,1,True,0,,,,
# GET_RFPROFILE_FREQUENCY_SPREAD_LEFT
P,246,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,41,False,7,,,,
A,1,1,True,1,,,,
# GET_RFPROFILE_FREQUENCY_SPREAD_RIGHT
P,251,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,41,False,8,,,,
A,1,1,True,1,,,,
# GET_RFPROFILE_NOISE_POWER
P,261,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,41,False,9,,,,
A,1,1,True,0,,,,
# GET_RFPROFILE_NOTCH_LEFT
P,258,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,41,False,10,,,,
A,1,1,True,0,,,,
# GET_RFPROFILE_NOTCH_RIGHT
P,259,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,41,False,11,,,,
A,1,1,True,0,,,,
# GET_RFPROFILE_RSSI
P,263,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,41,False,12,,,,
A,1,1,True,0,,,,
# GET_RFPROFILE_SHAPE_LEFT
P,247,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,41,False,13,,,,
A,1,1,True,0,,,,
# GET_RFPROFILE_SHAPE_RIGHT
P,253,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,41,False,14,,,,
A,1,1,True,0,,,,
# GET_RFPROFILE_SIGNAL_TO_NOISE_RATIO
P,262,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,41,False,15,,,,
A,1,1,True,0,,,,
# GET_TEMPERATURE
P,14,255,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/_tmp",,,
A,1,1,True,32,,,,
# GET_TEMPERATURE_THRESHOLD_COUNT
P,72,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,4,True,"PATC",,,,
A,1,1,True,2,,,,
# GET_TEMPERATURE_THRESHOLD_HYSTERESIS
P,15,255,1,24,"<schema></schema>",3,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/gtsh",,,
A,1,4,True,"GTSH",,,,
A,2,1,True,2,,,,
# GET_TEMPERATURE_THRESHOLDS
P,143,0,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,29,True,"GTT0",,,,
# GET_TEMPERATURE_THRESHOLDS
P,143,1,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,29,True,"GTT1",,,,
# GET_TRIP_POINT_ACTIVE
P,1,0,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac0",,,
A,1,4,True,"_AC0",,,,
# GET_TRIP_POINT_ACTIVE
P,1,1,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac1",,,
A,1,4,True,"_AC1",,,,
# GET_TRIP_POINT_ACTIVE
P,1,2,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac2",,,
A,1,4,True,"_AC2",,,,
# GET_TRIP_POINT_ACTIVE
P,1,3,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac3",,,
A,1,4,True,"_AC3",,,,
# GET_TRIP_POINT_ACTIVE
P,1,4,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac4",,,
A,1,4,True,"_AC4",,,,
# GET_TRIP_POINT_ACTIVE
P,1,5,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac5",,,
A,1,4,True,"_AC5",,,,
# GET_TRIP_POINT_ACTIVE
P,1,6,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac6",,,
A,1,4,True,"_AC6",,,,
# GET_TRIP_POINT_ACTIVE
P,1,7,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac7",,,
A,1,4,True,"_AC7",,,,
# GET_TRIP_POINT_ACTIVE
P,1,8,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac8",,,
A,1,4,True,"_AC8",,,,
# GET_TRIP_POINT_ACTIVE
P,1,9,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac9",,,
A,1,4,True,"_AC9",,,,
# GET_TRIP_POINT_CRITICAL
P,13,255,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_crt",,,
A,1,4,True,"_CRT",,,,
# GET_TRIP_POINT_HOT
P,12,255,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_hot",,,
A,1,4,True,"_HOT",,,,
# GET_TRIP_POINT_PASSIVE
P,11,255,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_psv",,,
A,1,4,True,"_PSV",,,,
# GET_TRIP_POINT_WARM
P,177,255,1,24,"<schema></schema>",6,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_cr3",,,
A,1,4,True,"_CR3",,,,
# SET_TEMPERATURE
P,241,255,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/_tmp",,,
# SET_TEMPERATURE_THRESHOLDS
P,47,0,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,29,True,"STT0",,,,
# SET_TEMPERATURE_THRESHOLDS
P,47,1,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,29,True,"STT1",,,,
# SET_TRIP_POINT_ACTIVE
P,202,0,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac0",,,
# SET_TRIP_POINT_ACTIVE
P,202,1,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac1",,,
# SET_TRIP_POINT_ACTIVE
P,202,2,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac2",,,
# SET_TRIP_POINT_ACTIVE
P,202,3,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac3",,,
# SET_TRIP_POINT_ACTIVE
P,202,4,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac4",,,
# SET_TRIP_POINT_ACTIVE
P,202,5,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac5",,,
# SET_TRIP_POINT_ACTIVE
P,202,6,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac6",,,
# SET_TRIP_POINT_ACTIVE
P,202,7,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac7",,,
# SET_TRIP_POINT_ACTIVE
P,202,8,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac8",,,
# SET_TRIP_POINT_ACTIVE
P,202,9,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_ac9",,,
# SET_TRIP_POINT_CRITICAL
P,203,255,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_crt",,,
# SET_TRIP_POINT_HOT
P,204,255,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_hot",,,
# SET_TRIP_POINT_PASSIVE
P,206,255,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_psv",,,
# SET_TRIP_POINT_WARM
P,205,255,2,6,"<schema></schema>",24,"<schema></schema>"
A,0,20,False,"@ESIF","/participants/%nm%/trippoint/_cr3",,,
