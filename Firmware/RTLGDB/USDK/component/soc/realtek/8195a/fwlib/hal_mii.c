/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "rtl8195a.h"

#ifdef CONFIG_MII_EN

#include "hal_mii.h"

HAL_ETHER_ADAPTER HalEtherAdp;



int32_t
HalMiiInit(
	IN void
)
{
	if (FunctionChk(MII, S0) == _FALSE)
		return HAL_ERR_UNKNOWN;
	else
		return HalMiiInitRtl8195a();
}


void
HalMiiDeInit(
	IN void
)
{
	HalMiiDeInitRtl8195a();
}


int32_t
HalMiiWriteData(
	IN const char *Data,
	IN uint32_t Size
)
{
	return HalMiiWriteDataRtl8195a(Data, Size);
}


uint32_t
HalMiiSendPacket(
	IN void
)
{
	return HalMiiSendPacketRtl8195a();
}


uint32_t
HalMiiReceivePacket(
	IN void
)
{
	return HalMiiReceivePacketRtl8195a();
}


uint32_t
HalMiiReadData(
	IN uint8_t *Data,
	IN uint32_t Size
)
{
	return HalMiiReadDataRtl8195a(Data, Size);
}


void
HalMiiGetMacAddress(
	IN uint8_t *Addr
)
{
	HalMiiGetMacAddressRtl8195a(Addr);
}


uint32_t
HalMiiGetLinkStatus(
	IN void
)
{
	return HalMiiGetLinkStatusRtl8195a();
}


void
HalMiiForceLink(
	IN int32_t Speed,
	IN int32_t Duplex
)
{
	HalMiiForceLinkRtl8195a(Speed, Duplex);
}


#ifdef CONFIG_MII_VERIFY
void
HalMiiOpInit(
    IN void *Data
)
{
    PHAL_MII_OP pHalMiiOp = (PHAL_MII_OP) Data;


    pHalMiiOp->HalMiiGmacInit          = HalMiiGmacInitRtl8195a;
    pHalMiiOp->HalMiiGmacReset         = HalMiiGmacResetRtl8195a;
    pHalMiiOp->HalMiiGmacEnablePhyMode = HalMiiGmacEnablePhyModeRtl8195a;
    pHalMiiOp->HalMiiGmacXmit          = HalMiiGmacXmitRtl8195a;
    pHalMiiOp->HalMiiGmacCleanTxRing   = HalMiiGmacCleanTxRingRtl8195a;
    pHalMiiOp->HalMiiGmacFillTxInfo    = HalMiiGmacFillTxInfoRtl8195a;
    pHalMiiOp->HalMiiGmacFillRxInfo    = HalMiiGmacFillRxInfoRtl8195a;
    pHalMiiOp->HalMiiGmacTx            = HalMiiGmacTxRtl8195a;
    pHalMiiOp->HalMiiGmacRx            = HalMiiGmacRxRtl8195a;
    pHalMiiOp->HalMiiGmacSetDefaultEthIoCmd   = HalMiiGmacSetDefaultEthIoCmdRtl8195a;
    pHalMiiOp->HalMiiGmacInitIrq       = HalMiiGmacInitIrqRtl8195a;
    pHalMiiOp->HalMiiGmacGetInterruptStatus   = HalMiiGmacGetInterruptStatusRtl8195a;
    pHalMiiOp->HalMiiGmacClearInterruptStatus = HalMiiGmacClearInterruptStatusRtl8195a;
}
#endif  // #ifdef CONFIG_MII_VERIFY

#endif  // #ifdef CONFIG_MII_EN


