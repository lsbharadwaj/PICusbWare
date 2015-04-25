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
#include <USBTransferCompHandlers.h>
void ControlTransferHandler()
{
    char EndPt = USTATbits.ENDP;
    SetupMsg *SetupPtr;
    if(EP[EndPt].currentStage == Setup)
        {
            //----- COPY DATA -------------------
            SetupPtr = (SetupMsg*) EP[EndPt].OutMsgCpyDest;
            SetupReq.bmFields   = SetupPtr->bmFields;
            SetupReq.bRequest   = SetupPtr->bRequest;
            SetupReq.wValue     = SetupPtr->wValue;
            SetupReq.wIndex     = SetupPtr->wIndex;
            SetupReq.wLength    = SetupPtr->wLength;
            //---------------------------------
            BDTable[EndPt].BDout.BDSTAT = 0;    //This will remove stall if any
            BDTable[EndPt].BDin.BDSTAT = 0;    //This will remove stall if any
            //-------------------------------------
            EP[EndPt].InBytesTotal = 0;     //Return Success
            EP[EndPt].InBytesCopied = 0;     //Reset this counter
        }


    if(SetupReq.ReqType == 0)   //If Standard Request
        {
            switch (SetupReq.bRequest)
                {
                case SET_ADDRESS:
                    setAddress();   //Call the setAddress
                    break;
                case GET_DESCRIPTOR:
                    getDescriptor();
                    break;
                case SET_DESCRIPTOR:
                    setDescriptor();
                    break;
                default:
                    EPstall(0);
                }
        }
    else if(SetupReq.ReqType == 1)
        {
            switch (SetupReq.bRequest)
                {
                case SET_CONTROL_LINE_STATE:
                    SetControlLineState();
                    break;
                case SET_LINE_CODING:
                    SetLineCoding();
                    break;
                default:
                    EPstall(0);
//                    LATA = SetupReq.bRequest << 1;
//                    delay100ktcy(100);
//                    LATA = ~LATA;
//                    delay10ktcy(100);
//                    LATA = SetupReq.bRequest >> 3;
//                    delay100ktcy(100);
//                    LATA = ~LATA;
//                    delay10ktcy(100);
//                    while(1);

                }
        }
    else
        {
            EPstall(0);
        }
    //Arm the EP0Out always
    BDTable[EndPt].BDout.BDCNT = 8;
    BDTable[EndPt].BDout.DTSEN = 1;
    EP[EndPt].outBytesCopied = 0;
    EP[EndPt].outTranPending = 1;
    BDTable[EndPt].BDout.UOWN = 1;
}


void skip()
{
    NotificationType NotificationHdr = {.bmRequest = 0x0a,.bNotication = 0x20,.wValue = 0, .wIndex = 0, .wLength = 2};
    char *copy = (char *)NotificationHdr, i=0;
    for (i = 0; i < 8; i++)
        {
            EP1inDataHolder[i] = copy[i];
        }
    SerialState.wState = 0;
    SerialState.DSR = 1;
    SerialState.CD = 1;
    copy = (char*)SerialState;
    for (i = 0; i < 2; i++)
        {
            EP1inDataHolder[i+8] = copy[i];
        }
    EP[1].InBytesTotal = 10;
    EP[1].InBytesCopied = 0;
    EP[1].inTranPending = 1;
    inTranHandler(1);
}

void ReadComData()
{

    int i;
    if(BDTable[2].BDin.UOWN == 0)
        {
            for (i = 0 ; i< EP[2].outBytesCopied ; i++)
                EP2inDataHolder[i] = EP2outDataHolder[i];
            EP[2].InBytesCopied = 0;
            EP[2].InBytesTotal =  EP[2].outBytesCopied;
            EP[2].inTranPending = 1;
            inTranHandler(2);
        }
    EP[2].outBytesCopied = 0;
    BDTable[2].BDout.BDCNT = 8;
    BDTable[2].BDout.DTSEN = 1;
    EP[2].outBytesCopied = 0;
    EP[2].outTranPending = 1;
    BDTable[2].BDout.UOWN = 1;
}

void WriteComData()
{
//    int i;
//    if(BDTable[2].BDin.UOWN == 0)
//        {
//            LATA++;
//            for (i = 0 ; i< 20 ; i++)
//                EP2inDataHolder[i] = i + 'A';
//            EP[2].InBytesCopied = 0;
//            EP[2].InBytesTotal =  10;
//            EP[2].inTranPending = 1;
//            inTranHandler(2);
//        }
}
