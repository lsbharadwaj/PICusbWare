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
#include <pic16/pic18fregs.h>
#include <pic16/stdio.h>
#include <USBGlobalExtern.h>
#include <USBCore.h>

PUTCHAR(c)
{
    while(EP[2].inTranPending  != 0);

    EP2inDataHolder[dataCnt] = c;
    dataCnt ++;
    EP[2].InBytesCopied = 0;
    EP[2].InBytesTotal =  dataCnt;
    if(dataCnt == EP2_MAX_OUT_DATA_HOLDER_SIZE)
        {
            EP[2].inTranPending = 1;
            inTranHandler(2);
            dataCnt = 0;
        }
}

void USBflush()
{
    EP[2].inTranPending = 1;
    inTranHandler(2);
    dataCnt = 0;
}
char getchar()
{
    char updatedStart, retData;
    updatedStart = USBRingBuf.startInd + 1;
    if(updatedStart > USBRingBuf.sizeInd)
        updatedStart = 0;

    while(updatedStart == USBRingBuf.endInd);

    retData = USBRingBuf.buf[updatedStart];
    USBRingBuf.startInd = updatedStart;

    return(retData);
}


void USBgets(char *data, char maxDataSize)
{
    char c;
    char i = 0;
    while((c = getchar())!='\r' && i < maxDataSize - 1)
        {
            data[i] = c;
            i++;
        }
    data[i] = '\0';
}
