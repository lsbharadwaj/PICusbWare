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
#include <USBClassReq.h>
#ifdef USE_USB_LIB
void SetControlLineState()
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
        }
}
void SetLineCoding()
{
    if(EP[0].currentStage == Setup)
        {
        }
    else if(EP[0].currentStage == Data)
        {
            //Prepare for handshake
            EP[0].DTSExpectedIn = 1;    //Expected data toggle value = 1
            EP[0].inTranPending = 1;     //Enable sending of data
            inTranHandler(0);           //get it ready for the next transaction
        }
    else
        {
        }
}

#endif
