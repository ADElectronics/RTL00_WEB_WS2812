/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _HAL_GDMA_H_
#define _HAL_GDMA_H_

#include "rtl8195a_gdma.h"

typedef struct _GDMA_CH_LLI_ELE_ {
    uint32_t                   Sarx;
    uint32_t                   Darx;
    uint32_t                   Llpx;
    uint32_t                   CtlxLow;
    uint32_t                   CtlxUp;
    uint32_t                   Temp;
}GDMA_CH_LLI_ELE, *PGDMA_CH_LLI_ELE;
#if 1
#if 0
typedef struct _GDMA_CH_LLI_ {
    PGDMA_CH_LLI_ELE      pLliEle;
    PGDMA_CH_LLI          pNextLli;
}GDMA_CH_LLI, *PGDMA_CH_LLI;

typedef struct _BLOCK_SIZE_LIST_ {
    uint32_t                  BlockSize;
    PBLOCK_SIZE_LIST     pNextBlockSiz;
}BLOCK_SIZE_LIST, *PBLOCK_SIZE_LIST;
#else
struct GDMA_CH_LLI {
    PGDMA_CH_LLI_ELE                pLliEle;
    struct GDMA_CH_LLI             *pNextLli;
};

struct BLOCK_SIZE_LIST {
    uint32_t                             BlockSize;
    struct BLOCK_SIZE_LIST          *pNextBlockSiz;
};

#endif

#endif
typedef struct _HAL_GDMA_ADAPTER_ {
    uint32_t                   ChSar;
    uint32_t                   ChDar;
    GDMA_CHANNEL_NUM      ChEn;
    GDMA_CTL_REG          GdmaCtl;
    GDMA_CFG_REG          GdmaCfg;
    uint32_t                   PacketLen;
    uint32_t                   BlockLen;
    uint32_t                   MuliBlockCunt;
    uint32_t                   MaxMuliBlock;
    struct GDMA_CH_LLI          *pLlix;
    struct BLOCK_SIZE_LIST      *pBlockSizeList;

    PGDMA_CH_LLI_ELE      pLli;
    uint32_t                   NextPlli;
    uint8_t                    TestItem;
    uint8_t                    ChNum;
    uint8_t                    GdmaIndex;
    uint8_t                    IsrCtrl:1;
    uint8_t                    GdmaOnOff:1;
    uint8_t                    Llpctrl:1;
    uint8_t                    Lli0:1;
    uint8_t                    Rsvd4to7:4;
    uint8_t                    GdmaIsrType;
}HAL_GDMA_ADAPTER, *PHAL_GDMA_ADAPTER;

typedef struct _HAL_GDMA_CHNL_ {
    uint8_t GdmaIndx;
    uint8_t GdmaChnl;
    uint8_t IrqNum;
    uint8_t Reserved;
}HAL_GDMA_CHNL, *PHAL_GDMA_CHNL;

typedef struct _HAL_GDMA_BLOCK_ {
    uint32_t SrcAddr;
    uint32_t DstAddr;
    uint32_t BlockLength;
    uint32_t SrcOffset;
    uint32_t DstOffset;
}HAL_GDMA_BLOCK, *PHAL_GDMA_BLOCK;

typedef struct _HAL_GDMA_OP_ {
    void (*HalGdmaOnOff)(void *Data);
    BOOL (*HalGdamChInit)(void *Data);
    BOOL (*HalGdmaChSeting)(void *Data);
    BOOL (*HalGdmaChBlockSeting)(void *Data);
    void (*HalGdmaChDis)(void *Data);
    void (*HalGdmaChEn)(void *Data);
    void (*HalGdmaChIsrEnAndDis) (void *Data);
    uint8_t   (*HalGdmaChIsrClean)(void *Data);
    void (*HalGdmaChCleanAutoSrc)(void *Data);
    void (*HalGdmaChCleanAutoDst)(void *Data);
}HAL_GDMA_OP, *PHAL_GDMA_OP;

typedef struct _HAL_GDMA_OBJ_ {
    HAL_GDMA_ADAPTER HalGdmaAdapter;
    IRQ_HANDLE GdmaIrqHandle;
    volatile GDMA_CH_LLI_ELE GdmaChLli[16];
    struct GDMA_CH_LLI Lli[16];
    struct BLOCK_SIZE_LIST BlockSizeList[16];
    uint8_t Busy;      // is transfering
    uint8_t BlockNum;
} HAL_GDMA_OBJ, *PHAL_GDMA_OBJ;

void HalGdmaOpInit(IN  void *Data);
void HalGdmaOn(PHAL_GDMA_ADAPTER pHalGdmaAdapter);
void HalGdmaOff(PHAL_GDMA_ADAPTER pHalGdmaAdapter);
BOOL HalGdmaChInit(PHAL_GDMA_ADAPTER pHalGdmaAdapter);
void HalGdmaChDis(PHAL_GDMA_ADAPTER pHalGdmaAdapter);
void HalGdmaChEn(PHAL_GDMA_ADAPTER pHalGdmaAdapter);
BOOL HalGdmaChSeting(PHAL_GDMA_ADAPTER pHalGdmaAdapter);
BOOL HalGdmaChBlockSeting(PHAL_GDMA_ADAPTER pHalGdmaAdapter);
void HalGdmaChIsrEn(PHAL_GDMA_ADAPTER pHalGdmaAdapter);
void HalGdmaChIsrDis(PHAL_GDMA_ADAPTER pHalGdmaAdapter);
uint8_t HalGdmaChIsrClean(PHAL_GDMA_ADAPTER pHalGdmaAdapter);
void HalGdmaChCleanAutoSrc(PHAL_GDMA_ADAPTER pHalGdmaAdapter);
void HalGdmaChCleanAutoDst(PHAL_GDMA_ADAPTER pHalGdmaAdapter);

extern HAL_Status HalGdmaChnlRegister (uint8_t GdmaIdx, uint8_t ChnlNum);
extern void HalGdmaChnlUnRegister (uint8_t GdmaIdx, uint8_t ChnlNum);
extern PHAL_GDMA_CHNL HalGdmaChnlAlloc (HAL_GDMA_CHNL *pChnlOption);
extern void HalGdmaChnlFree (HAL_GDMA_CHNL *pChnl);
extern BOOL HalGdmaMemCpyInit(PHAL_GDMA_OBJ pHalGdmaObj);
extern void HalGdmaMemCpyDeInit(PHAL_GDMA_OBJ pHalGdmaObj);
extern void* HalGdmaMemCpy(PHAL_GDMA_OBJ pHalGdmaObj, void* pDest, void* pSrc, uint32_t len);
extern void HalGdmaMemAggr(PHAL_GDMA_OBJ pHalGdmaObj, PHAL_GDMA_BLOCK pHalGdmaBlock);
extern BOOL HalGdmaMemCpyAggrInit(PHAL_GDMA_OBJ pHalGdmaObj);

extern const HAL_GDMA_OP _HalGdmaOp;
extern const HAL_GDMA_CHNL GDMA_Chnl_Option[];
extern const HAL_GDMA_CHNL GDMA_Multi_Block_Chnl_Option[];
extern const uint16_t HalGdmaChnlEn[6];

#endif
