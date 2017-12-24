/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _HAL_PCM_H_
#define _HAL_PCM_H_

#include "rtl8195a_pcm.h"
/*
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

    PGDMA_CH_LLI_ELE            pLli;
    uint32_t                         NextPlli;
    uint8_t                    TestItem;
    uint8_t                          ChNum;
    uint8_t                          GdmaIndex;
    uint8_t                          IsrCtrl:1;
    uint8_t                          GdmaOnOff:1;
    uint8_t                          Llpctrl:1;
    uint8_t                          Lli0:1;
    uint8_t                          Rsvd4to7:4;
    uint8_t                          GdmaIsrType;
}HAL_GDMA_ADAPTER, *PHAL_GDMA_ADAPTER;

*/

typedef struct _HAL_PCM_ADAPTER_ {
    uint32_t                       Enable:1;
    PCM_CTL_REG               PcmCtl;
    PCM_CHCNR03_REG           PcmChCNR03;
    PCM_TSR03_REG             PcmTSR03;
    PCM_BSIZE03_REG           PcmBSize03;
    uint32_t                       abc;
    uint8_t                        PcmIndex;
    uint8_t                        PcmCh;
}HAL_PCM_ADAPTER, *PHAL_PCM_ADAPTER;


typedef struct _HAL_PCM_OP_ {
    void (*HalPcmOnOff)(void *Data);
    BOOL (*HalPcmInit)(void *Data);
    BOOL (*HalPcmSetting)(void *Data);
    BOOL (*HalPcmEn)(void *Data);
    BOOL (*HalPcmIsrEnAndDis) (void *Data);
    BOOL (*HalPcmDumpReg)(void *Data);
    BOOL (*HalPcm)(void *Data);
}HAL_PCM_OP, *PHAL_PCM_OP;


void HalPcmOpInit(
    IN  void *Data
);


#endif
