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
#ifndef __USB_GLOBAL_VAR_H
#define __USB_GLOBAL_VAR_H
#include <USBDescriptor.h>
#include <USBTypedef.h>
#include <USBdefineValues.h>

#ifndef MAX_ENDPOINT_CNT
#error Define MAX_ENDPOINT_CNT as Maximum number of endpoints used including 0
#endif // MAX_ENDPOINT_CNT



EndPoint EP[MAX_ENDPOINT_CNT];                          //< Variable to store information about the Endpoints

//Buffers to hold data of transfers
char EP0inDataHolder[EP0_MAX_IN_DATA_HOLDER_SIZE];      //< EP0 in Data Holder
char EP0outDataHolder[EP0_MAX_OUT_DATA_HOLDER_SIZE];    //< EP0 out Data Holder
char EP1inDataHolder[EP1_MAX_IN_DATA_HOLDER_SIZE];           //< EP1 in Data Holder
char EP2outDataHolder[EP2_MAX_OUT_DATA_HOLDER_SIZE];                 //< EP2 out Data Holder
char EP2inDataHolder[EP2_MAX_IN_DATA_HOLDER_SIZE];                  //< EP2 in Data Holder

SetupMsg SetupReq;                                      //< Buffer to Store the setup Req as it will be needed again
SerialStateType SerialState;

__at 0x500 char EPSieBuffers[MAX_EP_TRANSFER_SIZE];     //< Buffers for the SIE engine
__at 0x400 EPBufferDesc BDTable[MAX_ENDPOINT_CNT];      //<Buffer Descriptor table
#endif // __USB_GLOBAL_VAR_H
