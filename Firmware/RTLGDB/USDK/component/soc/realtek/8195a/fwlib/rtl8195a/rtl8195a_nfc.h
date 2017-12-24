/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */


#ifndef _RTL8195A_NFC_H_
#define _RTL8195A_NFC_H_

#include "hal_api.h"
//#include "osdep_api.h"
#ifdef CONFIG_NFC_VERIFY
#include "../test/nfc/rtl8195a_nfc_test.h"
#endif

#if CONFIG_NFC_NORMAL
//===================== Register Bit Field Definition =====================
// TODO:
//===================== Register Address Definition =====================
//TODO:
//#include "osdep_api.h"
#define N2A_Q_LENGTH 10
#define N2ARLENGTH    4
//#define NFCTAGLENGTH 36 // maximum 36*4=144 bytes
#define NFCTAG_BASE  0x7F000
#define NFCTAG_PAGESIZE 256
#define NFCTAG_MAXPAGEIDX 16//(4*(1024/NFCTAG_PAGESIZE))
#define A2NWCLENGTH    4

#define FLASHAPPLENGTH 31
#define FLASHAPP_BASE  0x7E000
#define FLASH_PAGESIZE 128
#define FLASH_MAXPAGEIDX 32//(4*(1024/FLASH_PAGESIZE))

typedef struct _A2N_CATCH_W_ {
    //uint8_t          Vaild;
    uint8_t          A2NCatchRPage;
    uint32_t         A2NCatchWData[A2NWCLENGTH];
}A2N_CATCH_W_QUEUE, *PA2N_CATCH_W_QUEUE;

typedef struct _A2N_MAILBOX_Q_ {
    uint8_t          Length;
    uint8_t          Response;
    uint32_t         Content[A2NWCLENGTH+1];
}A2N_MAILBOX_Q,*PA2N_MAILBOX_Q;

typedef struct _N2A_CATCH_R_ {
    uint8_t          Vaild;
    uint8_t          N2ACatchRPage;
    uint32_t         N2ACatchRData[N2ARLENGTH];
}N2A_CATCH_R_QUEUE, *PN2A_CATCH_R_QUEUE;


typedef struct _N2A_R_ {
    uint8_t          Vaild;
    uint8_t          N2ARPage;
}N2A_R_QUEUE, *PN2A_R_QUEUE;

typedef struct _N2A_W_ {
    uint8_t          Vaild;
    uint8_t          N2AWPage;
    uint32_t         N2AWData;
}N2A_W_QUEUE, *PN2A_W_QUEUE;

typedef struct _NFC_ADAPTER_ {
    uint8_t          Function;
    uint32_t         NFCIsr;
    uint8_t          N2ABoxOpen;
    uint8_t          A2NSeq;
    //uint8_t          NFCTagFlashWIdx;
    //uint8_t          NFCTagFlashRIdx;
//    uint32_t         NFCTag[NFCTAGLENGTH];
#if !TASK_SCHEDULER_DISABLED
    void *      VeriSema;
#else
    uint32_t         VeriSema;
#endif  
#ifdef PLATFORM_FREERTOS
    void *      NFCTask;
#else
    uint32_t         NFCTask;
#endif
#ifdef CONFIG_NFC_VERIFY
    //N2A Write Tag
    uint8_t          N2AWQRIdx;
    uint8_t          N2AWQWIdx;
    N2A_W_QUEUE N2AWQ[N2A_Q_LENGTH];
    //N2A Read Tag
    uint8_t          N2ARQRIdx;
    uint8_t          N2ARQWIdx;
    N2A_R_QUEUE N2ARQ[N2A_Q_LENGTH];
    //N2A Read Catch
    uint8_t          N2ARCRIdx;
    uint8_t          N2ARCWIdx;
    N2A_CATCH_R_QUEUE N2ACatchR[N2A_Q_LENGTH];
#endif
    //A2N Write Catch
    //uint8_t          A2NWCRIdx;
    //uint8_t          A2NWCWIdx;
    //A2N_CATCH_W_QUEUE A2NCatchW[N2A_Q_LENGTH];

    //A2N Write mailbox queue
    uint8_t          A2NWMailBox;
    uint8_t          A2NWQRIdx;
    uint8_t          A2NWQWIdx;          
    A2N_MAILBOX_Q A2NMAILQ[N2A_Q_LENGTH];

    uint8_t          TaskStop;
    void        *nfc_obj;
}NFC_ADAPTER, *PNFC_ADAPTER;

typedef enum _N2A_CMD_ {
    TAG_READ            = 0,
    TAG_WRITE           = 1,
    CATCH_READ_DATA     = 2,
    NFC_R_PRESENT       = 4,
    N2A_MAILBOX_STATE   = 5,
    EXT_CLK_REQ         = 6,
    MAX_N2ACMD
} N2A_CMD, *PN2A_CMD;

typedef enum _A2N_CMD_ {
    TAG_READ_DATA       = 0,
    CATCH_READ          = 2,
    CATCH_WRITE         = 3,
    A2N_MAILBOX_STATE   = 4,
    CONFIRM_N2A_BOX_STATE = 5,
    EXT_CLK_RSP         = 6,
    MAX_A2NCMD
} A2N_CMD, *PA2N_CMD;

// Callback event defination
typedef enum _NFC_HAL_EVENT_ {
    NFC_HAL_READER_PRESENT = (1<<0),
    NFC_HAL_READ = (1<<1),
    NFC_HAL_WRITE = (1<<2),
    NFC_HAL_ERR = (1<<3),
    NFC_HAL_CACHE_RD = (1<<4)    
}NFC_CB_EVENT, *PNFC_CB_EVENT;

void A2NWriteCatch(IN void *pNFCAdapte, IN uint8_t N2AWPage,
    IN uint8_t Length, IN uint32_t *WData);
void A2NReadCatch(IN void *pNFCAdapte, IN uint8_t   A2NRPage);
void HalNFCDmemInit(IN uint32_t *pTagData, IN uint32_t TagLen);
void HalNFCInit(PNFC_ADAPTER pNFCAdp);
void HalNFCDeinit(PNFC_ADAPTER pNFCAdp);
void HalNFCFwDownload(void);
uint32_t HalNFCDbgRead32(IN  uint32_t Addr);
void HalNFCDbgWrite32(IN  uint32_t Addr, IN  uint32_t Data);
#endif  //CONFIG_NFC_NORMAL
#endif  // #ifndef _RTL8195A_NFC_H_
