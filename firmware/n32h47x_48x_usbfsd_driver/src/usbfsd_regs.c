/*****************************************************************************
 * Copyright (c) 2023, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
*\*\file usbfsd_regs.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/


#include "usbfsd_lib.h"


/**
*\*\name    USB_SetCtrl.
*\*\fun     Set the CTRL register value.
*\*\param   wRegValue new register value.
*\*\return  none
**/
void USB_SetCtrl(uint16_t wRegValue)
{
    _SetCNTR(wRegValue);
}

/**
*\*\name    USB_GetCtrl.
*\*\fun     returns the CTRL register value.
*\*\param   none
*\*\return  CTRL register Value.
**/
uint16_t USB_GetCtrl(void)
{
    return (_GetCNTR());
}

/**
*\*\name    USB_SetSts.
*\*\fun     Set the STS register value.
*\*\param   wRegValue new register value.
*\*\return  none
**/
void USB_SetSts(uint16_t wRegValue)
{
    _SetISTR(wRegValue);
}

/**
*\*\name    USB_GetSts.
*\*\fun     Returns the STS register value.
*\*\param   none
*\*\return  STS register Value
**/
uint16_t USB_GetSts(void)
{
    return (_GetISTR());
}

/**
*\*\name    USB_GetFn.
*\*\fun     Returns the FN register value.
*\*\param   none
*\*\return  FN register Value
**/
uint16_t USB_GetFn(void)
{
    return (_GetFNR());
}

/**
*\*\name    USB_SetAddr.
*\*\fun     Set the ADDR register value.
*\*\param   wRegValue new register value.
*\*\return  none
**/
void USB_SetAddr(uint16_t wRegValue)
{
    _SetDADDR(wRegValue);
}

/**
*\*\name    USB_GetAddr.
*\*\fun     Returns the ADDR register value.
*\*\param   none
*\*\return  ADDR register Value
**/
uint16_t USB_GetAddr(void)
{
    return (_GetDADDR());
}

/**
*\*\name    USB_SetBuftab.
*\*\fun     Set the BUFTAB.
*\*\param   wRegValue New register value.
*\*\return  none
**/
void USB_SetBuftab(uint16_t wRegValue)
{
    _SetBTABLE(wRegValue);
}

/**
*\*\name    USB_GetBTABLE.
*\*\fun     Returns the BUFTAB register value.
*\*\param   none
*\*\return  BUFTAB address.
**/
uint16_t USB_GetBTABLE(void)
{
    return (_GetBTABLE());
}

/**
*\*\name    USB_SetEndPoint.
*\*\fun     Set the BUFTAB.
*\*\param   bEpNum Endpoint Number.
*\*\param   wRegValue New register value.
*\*\return  none
**/
void USB_SetEndPoint(uint8_t bEpNum, uint16_t wRegValue)
{
    _SetENDPOINT(bEpNum, wRegValue);
}

/**
*\*\name    USB_GetEndPoint.
*\*\fun     Return the Endpoint register value.
*\*\param   bEpNum Endpoint Number.
*\*\return  Endpoint register value.
**/
uint16_t USB_GetEndPoint(uint8_t bEpNum)
{
    return (_GetENDPOINT(bEpNum));
}

/**
*\*\name    USB_SetEpType.
*\*\fun     sets the type in the endpoint register.
*\*\param   bEpNum Endpoint Number.
*\*\param   wType type definition.
*\*\return  none
**/
void USB_SetEpType(uint8_t bEpNum, uint16_t wType)
{
    _SetEPType(bEpNum, wType);
}

/**
*\*\name    USB_GetEpType.
*\*\fun     Returns the endpoint type.
*\*\param   bEpNum Endpoint Number.
*\*\return  Endpoint Type
**/
uint16_t USB_GetEpType(uint8_t bEpNum)
{
    return (_GetEPType(bEpNum));
}

/**
*\*\name    SetEPTxStatus.
*\*\fun     Set the status of Tx endpoint.
*\*\param   bEpNum Endpoint Number.
*\*\param   wState new state.
*\*\return  none
**/
void SetEPTxStatus(uint8_t bEpNum, uint16_t wState)
{
    _SetEPTxStatus(bEpNum, wState);
}

/**
*\*\name    SetEPRxStatus.
*\*\fun     Set the status of Rx endpoint.
*\*\param   bEpNum Endpoint Number.
*\*\param   wState new state.
*\*\return  none
**/
void SetEPRxStatus(uint8_t bEpNum, uint16_t wState)
{
    _SetEPRxStatus(bEpNum, wState);
}

/**
*\*\name    USB_SetDouBleBuferEpStall.
*\*\fun     sets the status for Double Buffer Endpoint to STALL
*\*\param   bEpNum Endpoint Number.
*\*\param   bDir Endpoint direction.
*\*\return  none
**/
void USB_SetDouBleBuferEpStall(uint8_t bEpNum, uint8_t bDir)
{
    uint16_t Endpoint_DTOG_Status;
    Endpoint_DTOG_Status = USB_GetEndPoint(bEpNum);
    if (bDir == EP_DBUF_OUT)
    { /* OUT double buffered endpoint */
        _SetENDPOINT(bEpNum, Endpoint_DTOG_Status & ~EPRX_DATTOG1);
    }
    else if (bDir == EP_DBUF_IN)
    { /* IN double buffered endpoint */
        _SetENDPOINT(bEpNum, Endpoint_DTOG_Status & ~EPTX_DATTOG1);
    }
}

/**
*\*\name    USB_GetEpTxSts.
*\*\fun     Returns the endpoint Tx status.
*\*\param   bEpNum Endpoint Number.
*\*\return  Endpoint TX Status
**/
uint16_t USB_GetEpTxSts(uint8_t bEpNum)
{
    return (_GetEPTxStatus(bEpNum));
}

/**
*\*\name    USB_GetEpRxSts.
*\*\fun     Returns the endpoint Rx status.
*\*\param   bEpNum Endpoint Number.
*\*\return  Endpoint RX Status
**/
uint16_t USB_GetEpRxSts(uint8_t bEpNum)
{
    return (_GetEPRxStatus(bEpNum));
}

/**
*\*\name    USB_SetEpTxValid.
*\*\fun     Valid the endpoint Tx Status.
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_SetEpTxValid(uint8_t bEpNum)
{
    _SetEPTxStatus(bEpNum, EP_TX_VALID);
}

/**
*\*\name    USB_SetEpRxValid.
*\*\fun     Valid the endpoint Rx Status.
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_SetEpRxValid(uint8_t bEpNum)
{
    _SetEPRxStatus(bEpNum, EP_RX_VALID);
}

/**
*\*\name    USB_SetEpKind.
*\*\fun     set the EP_KIND bit.
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_SetEpKind(uint8_t bEpNum)
{
    _SetEP_KIND(bEpNum);
}

/**
*\*\name    USB_ClrEpKind.
*\*\fun     Clear the EP_KIND bit.
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_ClrEpKind(uint8_t bEpNum)
{
    _ClearEP_KIND(bEpNum);
}

/**
*\*\name    USB_ClrStsOut.
*\*\fun     Clear the Status Out of the related Endpoint
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_ClrStsOut(uint8_t bEpNum)
{
    _ClearEP_KIND(bEpNum);
}

/**
*\*\name    USB_SetStsOut.
*\*\fun     Set the Status Out of the related Endpoint
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_SetStsOut(uint8_t bEpNum)
{
    _SetEP_KIND(bEpNum);
}

/**
*\*\name    USB_SetEpDoubleBufer.
*\*\fun     Enable the double buffer feature for the endpoint.
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_SetEpDoubleBufer(uint8_t bEpNum)
{
    _SetEP_KIND(bEpNum);
}

/**
*\*\name    USB_ClrEpDoubleBufer.
*\*\fun     Disable the double buffer feature for the endpoint.
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_ClrEpDoubleBufer(uint8_t bEpNum)
{
    _ClearEP_KIND(bEpNum);
}

/**
*\*\name    USB_GetTxStallSts.
*\*\fun     Returns the Stall status of the Tx endpoint.
*\*\param   bEpNum Endpoint Number.
*\*\return  Tx Stall status.
**/
uint16_t USB_GetTxStallSts(uint8_t bEpNum)
{
    return (_GetTxStallStatus(bEpNum));
}

/**
*\*\name    USB_GetRxStallSts.
*\*\fun     Returns the Stall status of the Rx endpoint.
*\*\param   bEpNum Endpoint Number.
*\*\return  Rx Stall status.
**/
uint16_t USB_GetRxStallSts(uint8_t bEpNum)
{
    return (_GetRxStallStatus(bEpNum));
}

/**
*\*\name    USB_ClrEpCtrsRx.
*\*\fun     Clear the CTR_RX bit.
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_ClrEpCtrsRx(uint8_t bEpNum)
{
    _ClearEP_CTR_RX(bEpNum);
}

/**
*\*\name    USB_ClrEpCtrsTx.
*\*\fun     Clear the CTR_TX bit.
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_ClrEpCtrsTx(uint8_t bEpNum)
{
    _ClearEP_CTR_TX(bEpNum);
}

/**
*\*\name    USB_DattogRx.
*\*\fun     Toggle the DTOG_RX bit.
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_DattogRx(uint8_t bEpNum)
{
    _ToggleDTOG_RX(bEpNum);
}

/**
*\*\name    USB_DattogTx.
*\*\fun     Toggle the DTOG_TX bit.
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_DattogTx(uint8_t bEpNum)
{
    _ToggleDTOG_TX(bEpNum);
}

/**
*\*\name    USB_ClrDattogRx.
*\*\fun     Clear the DTOG_RX bit.
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_ClrDattogRx(uint8_t bEpNum)
{
    _ClearDTOG_RX(bEpNum);
}

/**
*\*\name    USB_ClrDattogTx.
*\*\fun     Clear the DTOG_TX bit.
*\*\param   bEpNum Endpoint Number.
*\*\return  none
**/
void USB_ClrDattogTx(uint8_t bEpNum)
{
    _ClearDTOG_TX(bEpNum);
}

/**
*\*\name    USB_SetEpAddress.
*\*\fun     Set the endpoint address.
*\*\param   bEpNum Endpoint Number.
*\*\param   bAddr New endpoint address.
*\*\return  none
**/
void USB_SetEpAddress(uint8_t bEpNum, uint8_t bAddr)
{
    _SetEPAddress(bEpNum, bAddr);
}

/**
*\*\name    USB_GetEpAddress.
*\*\fun     Get the endpoint address.
*\*\param   bEpNum Endpoint Number.
*\*\return  Endpoint address.
**/
uint8_t USB_GetEpAddress(uint8_t bEpNum)
{
    return (_GetEPAddress(bEpNum));
}

/**
*\*\name    USB_SetEpTxAddr.
*\*\fun     Set the endpoint Tx buffer address.
*\*\param   bEpNum Endpoint Number.
*\*\param   wAddr new address.
*\*\return  none
**/
void USB_SetEpTxAddr(uint8_t bEpNum, uint16_t wAddr)
{
    _SetEPTxAddr(bEpNum, wAddr);
}

/**
*\*\name    USB_SetEpRxAddr.
*\*\fun     Set the endpoint Rx buffer address.
*\*\param   bEpNum Endpoint Number.
*\*\param   wAddr new address.
*\*\return  none
**/
void USB_SetEpRxAddr(uint8_t bEpNum, uint16_t wAddr)
{
    _SetEPRxAddr(bEpNum, wAddr);
}

/**
*\*\name    USB_GetEpTxAddr.
*\*\fun     Returns the endpoint Tx buffer address.
*\*\param   bEpNum Endpoint Number.
*\*\return  Tx buffer address.
**/
uint16_t USB_GetEpTxAddr(uint8_t bEpNum)
{
    return (_GetEPTxAddr(bEpNum));
}

/**
*\*\name    USB_GetEpRxAddr.
*\*\fun     Returns the endpoint Rx buffer address.
*\*\param   bEpNum Endpoint Number.
*\*\return  Rx buffer address.
**/
uint16_t USB_GetEpRxAddr(uint8_t bEpNum)
{
    return (_GetEPRxAddr(bEpNum));
}

/**
*\*\name    USB_SetEpTxCnt.
*\*\fun     Set the Tx count.
*\*\param   bEpNum Endpoint Number.
*\*\param   wCount new count value.
*\*\return  none
**/
void USB_SetEpTxCnt(uint8_t bEpNum, uint16_t wCount)
{
    _SetEPTxCount(bEpNum, wCount);
}

/**
*\*\name    USB_SetEpCntRxReg.
*\*\fun     Set the Count Rx Register value.
*\*\param   pdwReg point to the register.
*\*\param   wCount new count value.
*\*\return  none
**/
void USB_SetEpCntRxReg(uint32_t* pdwReg, uint16_t wCount)
{
    _SetEPCountRxReg(dwReg, wCount);
}

/**
*\*\name    USB_SetEpRxCnt.
*\*\fun     Set the Rx count.
*\*\param   bEpNum Endpoint Number.
*\*\param   wCount new count value.
*\*\return  none
**/
void USB_SetEpRxCnt(uint8_t bEpNum, uint16_t wCount)
{
    _SetEPRxCount(bEpNum, wCount);
}

/**
*\*\name    USB_GetEpTxCnt.
*\*\fun     Get the Tx count.
*\*\param   bEpNum Endpoint Number.
*\*\return  Tx count value.
**/
uint16_t USB_GetEpTxCnt(uint8_t bEpNum)
{
    return (_GetEPTxCount(bEpNum));
}

/**
*\*\name    USB_GetEpRxCnt.
*\*\fun     Get the Rx count.
*\*\param   bEpNum Endpoint Number.
*\*\return  Rx count value.
**/
uint16_t USB_GetEpRxCnt(uint8_t bEpNum)
{
    return (_GetEPRxCount(bEpNum));
}

/**
*\*\name    USB_SetEpDblBuferAddr.
*\*\fun     Set the addresses of the buffer 0 and 1.
*\*\param   bEpNum Endpoint Number.
*\*\param   wBuf0Addr new address of buffer 0.
*\*\param   wBuf1Addr new address of buffer 1.
*\*\return  none
**/
void USB_SetEpDblBuferAddr(uint8_t bEpNum, uint16_t wBuf0Addr, uint16_t wBuf1Addr)
{
    _SetEPDblBuffAddr(bEpNum, wBuf0Addr, wBuf1Addr);
}

/**
*\*\name    USB_SetEpDblBuf0Addr.
*\*\fun     Set the Buffer 0 address.
*\*\param   bEpNum Endpoint Number.
*\*\param   wBuf0Addr new address.
*\*\return  none
**/
void USB_SetEpDblBuf0Addr(uint8_t bEpNum, uint16_t wBuf0Addr)
{
    _SetEPDblBuf0Addr(bEpNum, wBuf0Addr);
}

/**
*\*\name    USB_SetEpDblBuf1Addr.
*\*\fun     Set the Buffer 1 address.
*\*\param   bEpNum Endpoint Number.
*\*\param   wBuf0Addr new address.
*\*\return  none
**/
void USB_SetEpDblBuf1Addr(uint8_t bEpNum, uint16_t wBuf1Addr)
{
    _SetEPDblBuf1Addr(bEpNum, wBuf1Addr);
}

/**
*\*\name    USB_GetEpDblBuf0Addr.
*\*\fun     Returns the address of the Buffer 0.
*\*\param   bEpNum Endpoint Number.
*\*\return  Address of the Buffer 0.
**/
uint16_t USB_GetEpDblBuf0Addr(uint8_t bEpNum)
{
    return (_GetEPDblBuf0Addr(bEpNum));
}

/**
*\*\name    USB_GetEpDblBuf1Addr.
*\*\fun     Returns the address of the Buffer 1.
*\*\param   bEpNum Endpoint Number.
*\*\return  Address of the Buffer 1.
**/
uint16_t USB_GetEpDblBuf1Addr(uint8_t bEpNum)
{
    return (_GetEPDblBuf1Addr(bEpNum));
}

/**
*\*\name    USB_SetEpDblBuferCnt.
*\*\fun     Set the number of bytes for a double Buffer endpoint.
*\*\param   bDir Endpoint direction.
*\*\param   wCount new count value.
*\*\return  none
**/
void USB_SetEpDblBuferCnt(uint8_t bEpNum, uint8_t bDir, uint16_t wCount)
{
    _SetEPDblBuffCount(bEpNum, bDir, wCount);
}

/**
*\*\name    USB_SetEpDblBuf0Cnt.
*\*\fun     Set the number of bytes in the buffer 0 of a double Buffer endpoint.
*\*\param   bDir Endpoint direction.
*\*\param   wCount new count value.
*\*\return  none
**/
void USB_SetEpDblBuf0Cnt(uint8_t bEpNum, uint8_t bDir, uint16_t wCount)
{
    _SetEPDblBuf0Count(bEpNum, bDir, wCount);
}

/**
*\*\name    USB_SetEpDblBuf1Cnt.
*\*\fun     Set the number of bytes in the buffer 1 of a double Buffer endpoint.
*\*\param   bDir Endpoint direction.
*\*\param   wCount new count value.
*\*\return  none
**/
void USB_SetEpDblBuf1Cnt(uint8_t bEpNum, uint8_t bDir, uint16_t wCount)
{
    _SetEPDblBuf1Count(bEpNum, bDir, wCount);
}

/**
*\*\name    USB_GetEpDblBuf0Cnt.
*\*\fun     Returns the number of byte received in the buffer 0 of a double Buffer endpoint.
*\*\param   bEpNum Endpoint Number.
*\*\return  Endpoint Buffer 0 count
**/
uint16_t USB_GetEpDblBuf0Cnt(uint8_t bEpNum)
{
    return (_GetEPDblBuf0Count(bEpNum));
}

/**
*\*\name    USB_GetEpDblBuf1Cnt.
*\*\fun     Returns the number of byte received in the buffer 1 of a double Buffer endpoint.
*\*\param   bEpNum Endpoint Number.
*\*\return  Endpoint Buffer 1 count
**/
uint16_t USB_GetEpDblBuf1Cnt(uint8_t bEpNum)
{
    return (_GetEPDblBuf1Count(bEpNum));
}

/**
*\*\name    GetEPDblBufDir.
*\*\fun     gets direction of the double buffered endpoint
*\*\param   bEpNum Endpoint Number.
*\*\return  EP_DBUF_OUT, EP_DBUF_IN, EP_DBUF_ERR if the endpoint counter not yet programmed.
**/
EP_DBUF_DIR GetEPDblBufDir(uint8_t bEpNum)
{
    if ((uint16_t)(*_pEPRxCount(bEpNum) & 0xFC00) != 0)
        return (EP_DBUF_OUT);
    else if (((uint16_t)(*_pEPTxCount(bEpNum)) & 0x03FF) != 0)
        return (EP_DBUF_IN);
    else
        return (EP_DBUF_ERR);
}

/**
*\*\name    USB_FreeUserBuf.
*\*\fun     free buffer used from the application realizing it to the line toggles
*\*\param   bEpNum Endpoint Number.
*\*\param   bDir Endpoint direction.
*\*\return  none
**/
void USB_FreeUserBuf(uint8_t bEpNum, uint8_t bDir)
{
    if (bDir == EP_DBUF_OUT)
    { /* OUT double buffered endpoint */
        _ToggleDTOG_TX(bEpNum);
    }
    else if (bDir == EP_DBUF_IN)
    { /* IN double buffered endpoint */
        _ToggleDTOG_RX(bEpNum);
    }
}

/**
*\*\name    USB_ToWord.
*\*\fun     merge two byte in a word.
*\*\param   bh byte high
*\*\param   bl bytes low.
*\*\return  resulted word.
**/
uint16_t USB_ToWord(uint8_t bh, uint8_t bl)
{
    uint16_t wRet;
    wRet = (uint16_t)bl | ((uint16_t)bh << 8);
    return (wRet);
}

/**
*\*\name    USB_ByteSwap.
*\*\fun     Swap two byte in a word.
*\*\param   wSwW word to Swap.
*\*\return  resulted word.
**/
uint16_t USB_ByteSwap(uint16_t wSwW)
{
    uint8_t bTemp;
    uint16_t wRet;
    bTemp = (uint8_t)(wSwW & 0xff);
    wRet  = (wSwW >> 8) | ((uint16_t)bTemp << 8);
    return (wRet);
}
