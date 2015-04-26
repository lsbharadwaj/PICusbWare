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
#ifndef __USB_TYPEDEF_H
#define __USB_TYPEDEF_H


typedef void (*FncPtr)();


typedef union
{
    struct
    {
        char BDSTAT;
        char BDCNT;
        unsigned int BDADR;
    };
    struct
    {
        unsigned BC8     : 1;
        unsigned BC9     : 1;
        unsigned BSTALL  : 1;
        unsigned DTSEN   : 1;
        unsigned INCDIS  : 1;
        unsigned KEN     : 1;
        unsigned DTS     : 1;
        unsigned UOWN    : 1;
        char;
        unsigned int;
    };
    struct
    {
        unsigned            : 2;
        unsigned PID        : 4;
        unsigned            : 2;
        char                    ;
        unsigned int            ;

    };
} BufferDesc;

typedef struct
{
    BufferDesc BDout;
    BufferDesc BDin;
} EPBufferDesc;


typedef __code struct
{
    char    bLength;
    char    bDescriptorType;
    short   bcdUSB;
    char    bDeviceClass;
    char    bDeviceSubClass;
    char    bDeviceProtocol;
    char    bMaxPacketSize;
    short   idVendor;
    short   idProduct;
    short   bcdDevice;
    char    iManufacturer;
    char    iProduct;
    char    iSerialNumber;
    char    bNumConfig;
} DeviceDescriptor;

typedef struct
{
    unsigned    currentStage   :2;
    unsigned    DTSExpectedOut :1;
    unsigned    DTSExpectedIn :1;
    unsigned    inTranPending  :1;
    unsigned    outTranPending  :1;
    unsigned    isPacket        :1;
    unsigned    TransferError   :1;
    char *      InMsgCpySrc;
    char *      OutMsgCpyDest;
    short       InBytesTotal;
    short       InBytesCopied;
    short       outBytesCopied;
    short       outBufferSize;
    char       outEpSize;
    char       inEpSize;
    FncPtr    InTranComp;
    FncPtr   OutTranComp;
} EndPoint;
//--------------------------

typedef union
{
    struct
    {
        unsigned char   Recipient :5;
        unsigned char   ReqType   :2;
        unsigned char   Direction :1;
        unsigned char   bRequest;
        unsigned short  wValue;
        unsigned short  wIndex;
        unsigned short  wLength;
    };
    struct
    {
        unsigned char bmFields;
        unsigned char;
        unsigned char wValueLow;   //DescrIndex
        unsigned char wValueHigh;   //DescrType
        unsigned short;
        unsigned short;
    };
} SetupMsg;


typedef __code struct
{
    unsigned char EPno:4;
    unsigned char Dir :1;
    unsigned char isPacket:1;
    unsigned char DTSExpected:1;
    unsigned char UOWNinit :1;
    char *Buffer;
    FncPtr TranCompHandler;
    short EPSize;
    short BufferSize;
} EPConfig;


typedef union
{
    struct
    {
        short CD            :1;
        short DSR           :1;
        short bBreak        :1;
        short RI            :1;
        short bFraming      :1;
        short bParity       :1;
        short bOverRun      :1;
    };
    short   wState;
}SerialStateType;

typedef struct
{
    char bmRequest;
    char bNotication;
    short  wValue;
    short   wIndex;
    short   wLength;
}NotificationType;

enum Stages
{
    Setup = 0,
    Data,
    Handshake
};

typedef struct
{
    char startInd;
    char endInd;
    char sizeInd;
    char buf[24];
}ringBufType;
#endif // __USB_TYPEDEF_H
