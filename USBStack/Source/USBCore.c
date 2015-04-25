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
#include <USBCore.h>
#include <USBGlobalVar.h>
#include <USBDescriptor.h>

/**The function sets the regiester values for USB interrupts and its configuration
*/
void UsbInit()
{
    // FSEN = 1 & PPB = 0 & UPUEN = 1 & UTRDIS = 1
    UCFG = 0b00010100;
    configureEp(0);
    configureEp(1);
    UIEbits.TRNIE = 1;
    UIEbits.IDLEIE = 1;
    UIEbits.URSTIE = 1;
    UIEbits.ACTVIE = 1;
    IPR2bits.USBIP = 1; //Make USB interrupt priority high
    PIE2bits.USBIE = 1; //Enable USB Interrupts
    UCONbits.USBEN = 1;         //Finally enable the USB module
}

/** This is the interrupt handler and does the following things
* 1) If the USB detects idle then goes in to SUSPEND
* 2) If there was a tranfer complete detects the direction and endpoint number
    a) If out (It can be setup or out) waits for completing the transfer and then calls the outTranComp()
    b) If in transfer then waits till sending all the data in the buffer and then calles the inTranComp()
* 3) If Buf activity resumes then it wakes the device from suspend
*/
void UsbInterrupHandler() __critical
{
    //--------------------------------------------//
    char temp;      // This variable will be used so that the endpoint value can be obtatined easily without doing bitshifts
    //Check if the interrupt was caused bcos the port was idle. If yes Suspend
    if(1 == UIRbits.IDLEIF)
        {
            UCONbits.SUSPND = 1;
            UIRbits.IDLEIF = 0;     //Clear the interrupt flag
        }

    if(UIRbits.ACTVIF == 1)    //If the bus has turned active clear the suspend state
        {
            UCONbits.SUSPND = 0;
            while(UIRbits.ACTVIF != 0)      //While loop needed cos the interrupt flag may not clear immediately from the suspend state
                UIRbits.ACTVIF = 0;
        }
    // else if the interrupt was bcause of a completed transfer
    while (1 == UIRbits.TRNIF)
        {
            temp = USTATbits.ENDP;  //Save the endpoint address
            //Find the direction of transfer
            // If direction is out call the OutTranHandler which does the work of copying data from the SIE buffer
            if(USTATbits.DIR == 0)
                {
                    //If the transfer is complete then call OutTranComp function which will load new data for the SIE
                    if(outTranHandler(temp))
                        {
                            EP[temp].OutTranComp();
                            EP[temp].currentStage = (EP[temp].currentStage +1);
                            if(EP[temp].currentStage == 3)
                                EP[temp].currentStage = 0;

                        }
                }
            else    //Else if Direction is In call the inTranHandler which copies data to the SIE buffer
                {
                    if(inTranHandler(temp)) //If the in transaction is complete then call the handler
                        {
                            EP[temp].InTranComp();
                            EP[temp].currentStage = (EP[temp].currentStage +1);
                            if(EP[temp].currentStage == 3)
                                EP[temp].currentStage = 0;
                        }
                }
            UIRbits.TRNIF = 0;      //Clear the interrupt flag
        }
    if(UIRbits.UERRIF == 1)
        {
            LATA = 0xff;
            while(1);
        }
    if(UIRbits.URSTIF == 1)
        {
            UIRbits.URSTIF = 0;
        }
}

/** Currently no support for Isochornus
*/
void configureEp(char ind)
{
    char EndPtNo;
    char *UEPptr;
    char i;
    EndPtNo = EPConfigurationData[ind].EPno;
    UEPptr = &UEP0 + EndPtNo;

    EP[EndPtNo].currentStage = Setup;
    //if supports setup
    *UEPptr = *UEPptr | 0b00010000;     //Enable Handshake
    if(EPConfigurationData[ind].isPacket != 1)
        {
            *UEPptr = *UEPptr | 0b00001000;   //Disable control packet
            EP[EndPtNo].isPacket = 0;
        }
    else
        {
            EP[EndPtNo].isPacket = 1;
        }
    if(EPConfigurationData[ind].Dir == 1)
        {
            //Set Control Register
            *UEPptr = *UEPptr | 0b00000010; //Enable In direction
            //Set structure variables
            EP[EndPtNo].DTSExpectedIn = EPConfigurationData[ind].DTSExpected;
            EP[EndPtNo].InMsgCpySrc = EPConfigurationData[ind].Buffer;
            EP[EndPtNo].InTranComp = EPConfigurationData[ind].TranCompHandler;
            EP[EndPtNo].inEpSize = EPConfigurationData[ind].EPSize;
            EP[EndPtNo].InBytesCopied = 0;
            EP[EndPtNo].InBytesTotal = 0;
            EP[EndPtNo].inTranPending = EPConfigurationData[ind].UOWNinit;

            //----Set the Buffer Desc--------------
            BDTable[EndPtNo].BDin.BDCNT = EP[EndPtNo].inEpSize;
            BDTable[EndPtNo].BDin.BDSTAT = 0;
            BDTable[EndPtNo].BDin.DTSEN = 1;
            BDTable[EndPtNo].BDin.DTS = EP[EndPtNo].DTSExpectedIn;
            BDTable[EndPtNo].BDin.BDADR = (int)EPSieBuffers;
            for (i = 0; i < ind ; i++)
                BDTable[EndPtNo].BDin.BDADR = BDTable[EndPtNo].BDin.BDADR + EPConfigurationData[i].EPSize;
            BDTable[EndPtNo].BDin.UOWN = EPConfigurationData[ind].UOWNinit;
        }
    else
        {
            *UEPptr = *UEPptr | 0b00000100; //Enable out direction
            EP[EndPtNo].outBufferSize = EPConfigurationData[ind].BufferSize;
            EP[EndPtNo].DTSExpectedOut = EPConfigurationData[ind].DTSExpected;
            EP[EndPtNo].OutMsgCpyDest = EPConfigurationData[ind].Buffer;
            EP[EndPtNo].OutTranComp = EPConfigurationData[ind].TranCompHandler;
            EP[EndPtNo].outEpSize = EPConfigurationData[ind].EPSize;
            EP[EndPtNo].outBytesCopied = 0;
            EP[EndPtNo].outTranPending = EPConfigurationData[ind].UOWNinit;

            //----Set the Buffer Desc--------------
            BDTable[EndPtNo].BDout.BDCNT = EP[EndPtNo].outEpSize;
            BDTable[EndPtNo].BDout.BDSTAT = 0;
            BDTable[EndPtNo].BDout.DTSEN = 1;
            BDTable[EndPtNo].BDout.DTS = EP[EndPtNo].DTSExpectedOut;
            BDTable[EndPtNo].BDout.BDADR = (int)EPSieBuffers;
            for (i = 0; i < ind ; i++)
                BDTable[EndPtNo].BDout.BDADR = BDTable[EndPtNo].BDout.BDADR + EPConfigurationData[i].EPSize;
            BDTable[EndPtNo].BDout.UOWN = EPConfigurationData[ind].UOWNinit;
        }
}

void EPstall(char EpNo)
{
    BDTable[EpNo].BDout.BDSTAT = 0b10000100;
    BDTable[EpNo].BDin.BDSTAT = 0b10000100;
}



/**This function automatically recieves data and copies the data to the right location.
* Upon completion it returns a 1 and does not set uown
*/
char outTranHandler(char EPno)
{
    char *dest, *src, cnt, ret = 0;
    cnt = BDTable[EPno].BDout.BDCNT;        //The number of bytes sent by the host
    src = (char*)(BDTable[EPno].BDout.BDADR);       //have to copy from the location the data has landed in SIE
    dest = EP[EPno].OutMsgCpyDest + EP[EPno].outBytesCopied ;   //Append the data to the already present data
    if(EP[EPno].outTranPending == 0)
    {
        return(1);
    }
    //If transfer is Control
    if(EP[EPno].isPacket == 1)
        {
            if(BDTable[EPno].BDout.PID == 0b1101)
                {
                    EP[EPno].currentStage = Setup;          //The next stage will be data irrespective of wat was currnet
                    BDTable[EPno].BDin.UOWN = 0;            //Stop in EP
                    UCONbits.PKTDIS = 0;    //Enable the SIE after the setup packet
                    dest = EP[EPno].OutMsgCpyDest;   //This data will be copied from the start address
                    EP[EPno].outBytesCopied = 0;     //Reset the out bytes copied. This wil be added again below
                    ret = 1;                            //Transfer complete
                }
            if(EP[EPno].currentStage == Data)
                {
                    if(EP[EPno].outBytesCopied + cnt == SetupReq.wLength)
                        {
                            ret = 1;
                        }
                }
        }
    else
        {
            if (cnt < EP[EPno].outEpSize)
                {
                    ret = 1;
                }
        }
    if( EP[EPno].outBytesCopied + cnt > EP[EPno].outBufferSize)
        {
            EP[EPno].TransferError = 1;
            cnt = EP[EPno].outBufferSize - EP[EPno].outBytesCopied;
            ret = 1;
        }
    else
        {
            EP[EPno].TransferError = 0;
        }
    EP[EPno].outBytesCopied += cnt;
    while( cnt > 0)     //Copy the data
        {
            *dest = *src;
            dest++;
            src++;
            cnt --;
        }
    BDTable[EPno].BDout.BDSTAT = 0;
    BDTable[EPno].BDout.BDCNT = EP[EPno].outEpSize;
    BDTable[EPno].BDout.DTSEN = 1;
    BDTable[EPno].BDout.DTS = EP[EPno].DTSExpectedOut;
    EP[EPno].DTSExpectedOut ^= 1;//Next data is opposite polarity
    if(ret == 0)
        {
            BDTable[EPno].BDout.UOWN = 1;
        }
    else
        {
            EP[EPno].outTranPending  = 0;
        }
    return (ret);
}

/**This function automatically sends data and copies the data into the SIE after transaction.
* Upon completion it returns a 1
*/
char inTranHandler(char EPno)
{
    char *dest, *src, cnt, remaining, ret;
    //Compute the amount of remaining data to be transferred = Total to be transferred - Total transferred so far
    remaining = EP[EPno].InBytesTotal - EP[EPno].InBytesCopied;
    //If the endpoint size is larger than the amount of data left
    if(EP[EPno].inTranPending == 0)
    {
        return(1);
    }
    if(remaining < EP[EPno].inEpSize)
        {
            cnt = remaining;    //set the amount of data to be transffered equal to the the remaining data
            ret = 1;            //Also it indicates a completeion of transfer
        }
    else if (EP[EPno].isPacket == 1 && (EP[EPno].inEpSize + EP[EPno].InBytesCopied) >= SetupReq.wLength && EP[EPno].currentStage == Data)
        {
            cnt = remaining;    //set the amount of data to be transffered equal to the the remaining data
            ret = 1;            //Also it indicates a completeion of transfer
        }
    else
        {
            cnt = EP[EPno].inEpSize;    //If there is more data than wat the endpoint can take then transfer the ENDPt size data
            ret = 0;                    //There are more transfactions left
        }
    BDTable[EPno].BDin.BDCNT = cnt;     //Set the count for the sie
    dest = (char*)(BDTable[EPno].BDin.BDADR);   //destination is the sie buffer
    src = EP[EPno].InMsgCpySrc + EP[EPno].InBytesCopied; //Shift by the amount which has been already copied
    EP[EPno].InBytesCopied += cnt;      //Increase the InBytes copied count
    while( cnt > 0)     //copy the data
        {
            *dest = *src;
            dest++;
            src++;
            cnt --;
        }
    BDTable[EPno].BDin.BDSTAT = 0;
    BDTable[EPno].BDin.DTSEN = 1;
    BDTable[EPno].BDin.DTS = EP[EPno].DTSExpectedIn;   //Set the expected toggle
    EP[EPno].DTSExpectedIn ^= 1;  //The next data will be opposite
    BDTable[EPno].BDin.UOWN = 1;
    if(ret == 1)
        EP[EPno].inTranPending = 0;
    return (0);
}
