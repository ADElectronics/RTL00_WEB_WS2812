/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _HAL_MII_H_
#define _HAL_MII_H_

#include "rtl8195a_mii.h"


/**
 * LOG Configurations
 */

#define NOLOG

#define LOG_TAG           "NoTag"
#define LOG_INFO_HEADER   "I"
#define LOG_DEBUG_HEADER  "D"
#define LOG_ERROR_HEADER  "E"
#define LOG_TEST_HEADER   "T"

#define IDENT_TWO_SPACE    "  "
#define IDENT_FOUR_SPACE   "    "

#define LOG_INFO(...)  do {\
            DiagPrintf("\r"LOG_INFO_HEADER"/"LOG_TAG": " __VA_ARGS__);\
}while(0)

#define LOG_DEBUG(...)  do {\
            DiagPrintf("\r"LOG_DEBUG_HEADER"/"LOG_TAG": " __VA_ARGS__);\
}while(0)

#define LOG_ERROR(...)  do {\
            DiagPrintf("\r"LOG_ERROR_HEADER"/"LOG_TAG": " __VA_ARGS__);\
}while(0)

#ifdef NOLOG
    #define LOGI
    #define LOGD
    #define LOGE
    #define LOGI2
    #define LOGD2
    #define LOGE2
    #define LOGI4
    #define LOGD4
    #define LOGE4
#else
    #define LOGI  LOG_INFO
    #define LOGD  LOG_DEBUG
    #define LOGE  LOG_ERROR
    #define LOGI2(...) LOG_INFO(IDENT_TWO_SPACE __VA_ARGS__)
    #define LOGD2(...) LOG_DEBUG(IDENT_TWO_SPACE __VA_ARGS__)
    #define LOGE2(...) LOG_ERROR(IDENT_TWO_SPACE __VA_ARGS__)
    #define LOGI4(...) LOG_INFO(IDENT_FOUR_SPACE __VA_ARGS__)
    #define LOGD4(...) LOG_DEBUG(IDENT_FOUR_SPACE __VA_ARGS__)
    #define LOGE4(...) LOG_ERROR(IDENT_FOUR_SPACE __VA_ARGS__)
#endif

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define DBG_ENTRANCE LOGI(ANSI_COLOR_GREEN "=> %s() <%s>\n" ANSI_COLOR_RESET, \
        __func__, __FILE__)


// GMAC MII Configurations
#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG  "MII"
#endif


typedef enum {
	ETH_TXDONE,
	ETH_RXDONE,
	ETH_LINKUP,
	ETH_LINKDOWN
}EthernetEventType;

typedef struct _HAL_ETHER_ADAPTER_{
	IRQ_HANDLE IrqHandle;
	uint32_t InterruptMask;
	uint8_t	tx_desc_num;
	uint8_t	rx_desc_num;
	volatile uint8_t *TxDescAddr;
	volatile uint8_t *RxDescAddr;
	volatile uint8_t *pTxPktBuf;
	volatile uint8_t *pRxPktBuf;
	void (*CallBack)(uint32_t Event, uint32_t Data);
}HAL_ETHER_ADAPTER, *PHAL_ETHER_ADAPTER;



extern int32_t
HalMiiInit(
	IN void
);

extern void
HalMiiDeInit(
	IN void
);

extern int32_t
HalMiiWriteData(
	IN const char *Data,
	IN uint32_t Size
);

extern uint32_t
HalMiiSendPacket(
	IN void
);

extern uint32_t
HalMiiReceivePacket(
	IN void
);

extern uint32_t
HalMiiReadData(
	IN uint8_t *Data,
	IN uint32_t Size
);

extern void
HalMiiGetMacAddress(
	IN uint8_t *Addr
);

extern uint32_t
HalMiiGetLinkStatus(
	IN void
);

extern void
HalMiiForceLink(
	IN int32_t Speed,
	IN int32_t Duplex
);


#ifdef CONFIG_MII_VERIFY

typedef struct _HAL_MII_ADAPTER_ {
    uint32_t InterruptMask;
    PPHY_MODE_INFO pPhyModeInfo;
}HAL_MII_ADAPTER, *PHAL_MII_ADAPTER;

typedef struct _HAL_MII_OP_ {
    BOOL (*HalMiiGmacInit)(void *Data);
    BOOL (*HalMiiGmacReset)(void *Data);
    BOOL (*HalMiiGmacEnablePhyMode)(void *Data);
    uint32_t  (*HalMiiGmacXmit)(void *Data);
    void (*HalMiiGmacCleanTxRing)(void *Data);
    void (*HalMiiGmacFillTxInfo)(void *Data);
    void (*HalMiiGmacFillRxInfo)(void *Data);
    void (*HalMiiGmacTx)(void *Data);
    void (*HalMiiGmacRx)(void *Data);
    void (*HalMiiGmacSetDefaultEthIoCmd)(void *Data);
    void (*HalMiiGmacInitIrq)(void *Data);
    uint32_t  (*HalMiiGmacGetInterruptStatus)(void);
    void (*HalMiiGmacClearInterruptStatus)(uint32_t IsrStatus);
}HAL_MII_OP, *PHAL_MII_OP;

void HalMiiOpInit(IN void *Data);

typedef struct _MII_ADAPTER_ {
    PHAL_MII_OP      pHalMiiOp;
    PHAL_MII_ADAPTER pHalMiiAdapter;
    PTX_INFO         pTx_Info;
    PRX_INFO         pRx_Info;
    void*            TxBuffer;
    void*            RxBuffer;
}MII_ADAPTER, *PMII_ADAPTER;

#endif  // #ifdef CONFIG_MII_VERIFY

#endif  // #ifndef _HAL_MII_H_

