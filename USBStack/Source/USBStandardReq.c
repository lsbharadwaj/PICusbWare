/*
//    This file belongs to PICusbWare
//    A free USB firmware for PIC18f4550 to be compiled with SDCC
//
//    Copyright (C) 2015  L.S.Bharadwaj (lsbharadwaj[at]gmail.com)
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License along
//    with this program; if not, write to the Free Software Foundation, Inc.,
//    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//  ================================================================================
*/
#include <USBStandardReq.h>
void setDescriptor()
{
    if(EP[0].currentStage == Setup)
        {
            configureEp(2);
            configureEp(3);
            configureEp(4);
            //Prepare for handshake
            EP[0].DTSExpectedIn = 1;    //Expected data toggle value = 1
            EP[0].inTranPending = 1;     //Enable sending of data
            inTranHandler(0);           //get it ready for the next transaction
            EP[0].currentStage = Data;    //This has no data stage
        }
    else    //(EP[0].currentStage == Handshake)    //handshake completed so I can set the address now
        {

        }
}

void getDescriptor()
{
    static char DataTempHolder[USB_CONFIG_DESC_TOT_LENGTH];
    int i;
    int cnt = 0;
    if(EP[0].currentStage == Setup)
        {
            switch (SetupReq.wValueHigh)
                {
                case USB_DEVICE_DESCRIPTOR_TYPE:
                    //First copy all the data from rom to ram
                    for(i = 0 ; i < sizeof(DeviceDescriptor); i++)
                        {
                            DataTempHolder[i] = DDesc[i];
                        }
                    EP[0].InBytesTotal = SetupReq.wLength < sizeof(DeviceDescriptor)? SetupReq.wLength : sizeof(DeviceDescriptor);
                    break;
                case USB_CONFIGURATION_DESCRIPTOR_TYPE:
                    for(i = 0 ; i < USB_CONFIG_DESC_TOT_LENGTH; i++)
                        {
                            DataTempHolder[i] = cdc_config_descriptor[i];
                        }
                    EP[0].InBytesTotal = SetupReq.wLength < USB_CONFIG_DESC_TOT_LENGTH? SetupReq.wLength : USB_CONFIG_DESC_TOT_LENGTH;
                    break;
                case USB_STRING_DESCRIPTOR_TYPE:
                    for(i=0 ; i < SetupReq.wValueLow; i++)
                        {
                            cnt += (int)cdc_str_descs[cnt];
                        }
                    for(i = 0 ; i < cdc_str_descs[cnt]; i++)
                        {
                            DataTempHolder[i] = cdc_str_descs[i + cnt];
                        }
                    EP[0].InBytesTotal = SetupReq.wLength < cdc_str_descs[cnt]? SetupReq.wLength : cdc_str_descs[cnt];
                    break;
                default:
                    EPstall(0);
                }
            EP[0].DTSExpectedIn = 1;    //Expected data toggle value = 1
            EP[0].InMsgCpySrc = DataTempHolder;
            EP[0].inTranPending = 1;    //Expected data toggle value = 1
            inTranHandler(0);           //get it ready to send data to pc
        }
    //Prepare for handshake stage
    else if(EP[0].currentStage == Data)
        {
            EP[0].DTSExpectedOut = 1;   //Set the expected data toggle value
        }
    else    //Debug
        {
            ;
        }
}

void setAddress()
{
    if(EP[0].currentStage == Setup)
        {
            //Prepare for handshake
            EP[0].DTSExpectedIn = 1;    //Expected data toggle value = 1
            EP[0].inTranPending = 1;     //Enable sending of data
            inTranHandler(0);           //get it ready for the next transaction
            EP[0].currentStage = Data;    //This has no data stage
        }
    else    //(EP[0].currentStage == Handshake)    //handshake completed so I can set the address now
        {
            UADDR = SetupReq.wValue;
        }
}
