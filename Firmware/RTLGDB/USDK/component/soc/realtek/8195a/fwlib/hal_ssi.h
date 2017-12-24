/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _HAL_SSI_H_
#define _HAL_SSI_H_

#include "rtl8195a_ssi.h"

/**
 * LOG Configurations
 */

extern uint32_t SSI_DBG_CONFIG;
extern uint8_t SPI0_IS_AS_SLAVE;


#define SSI_DBG_ENTRANCE(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_ENTRANCE)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE ANSI_COLOR_GREEN __VA_ARGS__ ANSI_COLOR_RESET); \
}while(0)

#define SSI_DBG_INIT(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INIT)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INIT_V(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INIT_V)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INIT_VV(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INIT_VV)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_PINMUX(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_PINMUX)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_ENDIS(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_ENDIS)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INT(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INT_V(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT_V)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INT_HNDLR(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT_HNDLR)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INT_READ(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT_READ)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INT_WRITE(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT_WRITE)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_STATUS(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_STATUS)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_FIFO(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_FIFO)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_READ(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_READ)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_WRITE(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_WRITE)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_SLV_CTRL(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_SLV_CTRL)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

typedef enum _SSI_DBG_TYPE_LIST_ {
    DBG_TYPE_ENTRANCE  = 1 << 0,
    DBG_TYPE_INIT      = 1 << 1,
    DBG_TYPE_INIT_V    = 1 << 2,
    DBG_TYPE_INIT_VV   = 1 << 3,
    DBG_TYPE_PINMUX    = 1 << 4,
    DBG_TYPE_ENDIS     = 1 << 5,
    DBG_TYPE_INT       = 1 << 6,
    DBG_TYPE_INT_V     = 1 << 7,
    DBG_TYPE_INT_HNDLR = 1 << 8,
    DBG_TYPE_INT_READ  = 1 << 9,
    DBG_TYPE_INT_WRITE = 1 << 10,
    DBG_TYPE_STATUS    = 1 << 11,
    DBG_TYPE_FIFO      = 1 << 12,
    DBG_TYPE_READ      = 1 << 13,
    DBG_TYPE_WRITE     = 1 << 14,
    DBG_TYPE_SLV_CTRL  = 1 << 15
} SSI_DBG_TYPE_LIST, *PSSI_DBG_TYPE_LIST;

 typedef struct _SSI_DMA_CONFIG_ {
    void *pHalGdmaOp;
    void *pTxHalGdmaAdapter;
    void *pRxHalGdmaAdapter;
    uint8_t    RxDmaBurstSize;
    uint8_t    TxDmaBurstSize;
    uint8_t    RxDmaEnable;
    uint8_t    TxDmaEnable;
    IRQ_HANDLE RxGdmaIrqHandle;
    IRQ_HANDLE TxGdmaIrqHandle;
}SSI_DMA_CONFIG, *PSSI_DMA_CONFIG;

#ifdef CONFIG_GDMA_EN
typedef struct _HAL_SSI_DMA_MULTIBLK_ {
    volatile GDMA_CH_LLI_ELE GdmaChLli[16];
    struct GDMA_CH_LLI Lli[16];
    struct BLOCK_SIZE_LIST BlockSizeList[16];   
}SSI_DMA_MULTIBLK, *PSSI_DMA_MULTIBLK;
#endif
/**
 * DesignWare SSI Configurations
 */
typedef struct _HAL_SSI_ADAPTOR_ {
    SSI_DMA_CONFIG DmaConfig;
    IRQ_HANDLE IrqHandle;
    //
    void (*RxCompCallback)(void *Para);
    void *RxCompCbPara;
    void *RxData;
    void (*TxCompCallback)(void *Para);
    void *TxCompCbPara;
    void *TxData;
    uint32_t  DmaRxDataLevel;
    uint32_t  DmaTxDataLevel;
    uint32_t  InterruptPriority;
    uint32_t  RxLength;
    uint32_t  RxLengthRemainder;
    uint32_t  RxThresholdLevel;
    uint32_t  TxLength;
    uint32_t  TxThresholdLevel;
    uint32_t  SlaveSelectEnable;
    //
    uint16_t  ClockDivider;
    uint16_t  DataFrameNumber;
    //
    uint8_t   ControlFrameSize;
    uint8_t   DataFrameFormat;
    uint8_t   DataFrameSize;
    uint8_t   DmaControl;
    uint8_t   Index;
    uint8_t   InterruptMask;
    uint8_t   MicrowireDirection;
    uint8_t   MicrowireHandshaking;
    uint8_t   MicrowireTransferMode;
    uint8_t   PinmuxSelect;
    uint8_t   Role;
    uint8_t   SclkPhase;
    uint8_t   SclkPolarity;
    uint8_t   SlaveOutputEnable;
    uint8_t   TransferMode;
    uint8_t   TransferMechanism;

    // Extend
    uint8_t Reserve;
    uint8_t HaveTxChannel;
    uint8_t HaveRxChannel;
    uint8_t DefaultRxThresholdLevel;
    #ifdef CONFIG_GDMA_EN
    SSI_DMA_MULTIBLK DmaTxMultiBlk, DmaRxMultiBlk;
    #endif
    uint32_t ReservedDummy;
    void (*TxIdleCallback)(void *Para);
    void *TxIdleCbPara;    
}HAL_SSI_ADAPTOR, *PHAL_SSI_ADAPTOR;

typedef struct _HAL_SSI_OP_{
    HAL_Status (*HalSsiPinmuxEnable)(void *Adaptor);
    HAL_Status (*HalSsiPinmuxDisable)(void *Adaptor);
    HAL_Status (*HalSsiEnable)(void *Adaptor);
    HAL_Status (*HalSsiDisable)(void *Adaptor);
    HAL_Status (*HalSsiInit)(void *Adaptor);
    HAL_Status (*HalSsiSetSclkPolarity)(void *Adaptor);
    HAL_Status (*HalSsiSetSclkPhase)(void *Adaptor);
    HAL_Status (*HalSsiWrite)(void *Adaptor, uint32_t value);
    HAL_Status (*HalSsiLoadSetting)(void *Adaptor, void *Setting);
    HAL_Status (*HalSsiSetInterruptMask)(void *Adaptor);
    HAL_Status (*HalSsiSetDeviceRole)(void *Adaptor, uint32_t Role);
    HAL_Status (*HalSsiInterruptEnable)(void *Adaptor);
    HAL_Status (*HalSsiInterruptDisable)(void *Adaptor);
    HAL_Status (*HalSsiReadInterrupt)(void *Adaptor, void *RxData, uint32_t Length);
    HAL_Status (*HalSsiSetRxFifoThresholdLevel)(void *Adaptor);
    HAL_Status (*HalSsiSetTxFifoThresholdLevel)(void *Adaptor);
    HAL_Status (*HalSsiWriteInterrupt)(void *Adaptor, uint8_t *TxData, uint32_t Length);
    HAL_Status (*HalSsiSetSlaveEnableRegister)(void *Adaptor, uint32_t SlaveIndex);
    uint32_t  (*HalSsiBusy)(void *Adaptor);
    uint32_t  (*HalSsiReadable)(void *Adaptor);
    uint32_t  (*HalSsiWriteable)(void *Adaptor);
    uint32_t  (*HalSsiGetInterruptMask)(void *Adaptor);
    uint32_t  (*HalSsiGetRxFifoLevel)(void *Adaptor);
    uint32_t  (*HalSsiGetTxFifoLevel)(void *Adaptor);
    uint32_t  (*HalSsiGetStatus)(void *Adaptor);
    uint32_t  (*HalSsiGetInterruptStatus)(void *Adaptor);
    uint32_t  (*HalSsiRead)(void *Adaptor);
    uint32_t  (*HalSsiGetRawInterruptStatus)(void *Adaptor);
    uint32_t  (*HalSsiGetSlaveEnableRegister)(void *Adaptor);
}HAL_SSI_OP, *PHAL_SSI_OP;

typedef struct _DW_SSI_DEFAULT_SETTING_ {
    void (*RxCompCallback)(void *Para);
    void *RxCompCbPara;
    void *RxData;
    void (*TxCompCallback)(void *Para);
    void *TxCompCbPara;
    void *TxData;
    uint32_t  DmaRxDataLevel;
    uint32_t  DmaTxDataLevel;
    uint32_t  InterruptPriority;
    uint32_t  RxLength;
    uint32_t  RxLengthRemainder;
    uint32_t  RxThresholdLevel;
    uint32_t  TxLength;
    uint32_t  TxThresholdLevel;
    uint32_t  SlaveSelectEnable;
    //
    uint16_t  ClockDivider;
    uint16_t  DataFrameNumber;
    //
    uint8_t   ControlFrameSize;
    uint8_t   DataFrameFormat;
    uint8_t   DataFrameSize;
    uint8_t   DmaControl;
    //uint8_t   Index;
    uint8_t   InterruptMask;
    uint8_t   MicrowireDirection;
    uint8_t   MicrowireHandshaking;
    uint8_t   MicrowireTransferMode;
    //uint8_t   PinmuxSelect;
    //uint8_t   Role;
    uint8_t   SclkPhase;
    uint8_t   SclkPolarity;
    uint8_t   SlaveOutputEnable;
    uint8_t   TransferMode;
    uint8_t   TransferMechanism;
} DW_SSI_DEFAULT_SETTING, *PDW_SSI_DEFAULT_SETTING;


struct spi_s {
    HAL_SSI_ADAPTOR spi_adp;
    HAL_SSI_OP      spi_op;
    uint32_t irq_handler;
    uint32_t irq_id;
    uint32_t dma_en;
    uint32_t state;
    uint8_t sclk;
#ifdef CONFIG_GDMA_EN    
    HAL_GDMA_ADAPTER spi_gdma_adp_tx;
    HAL_GDMA_ADAPTER spi_gdma_adp_rx;
#endif    
    uint32_t bus_tx_done_handler;
    uint32_t bus_tx_done_irq_id;
};

void HalSsiOpInit(void *Adaptor);
static __inline__ void HalSsiSetSclk(
    IN PHAL_SSI_ADAPTOR pHalSsiAdapter,
    IN uint32_t ClkRate)
{
    HalSsiSetSclkRtl8195a((void*)pHalSsiAdapter, ClkRate);
}

HAL_Status HalSsiInit(void * Data);
HAL_Status HalSsiDeInit(void * Data);
HAL_Status HalSsiEnable(void * Data);
HAL_Status HalSsiDisable(void * Data);
HAL_Status HalSsiEnterCritical(void * Data);
HAL_Status HalSsiExitCritical(void * Data);
HAL_Status HalSsiTimeout(uint32_t StartCount, uint32_t TimeoutCnt);
HAL_Status HalSsiStopRecv(void * Data);
HAL_Status HalSsiSetFormat(void * Data);
#ifdef CONFIG_GDMA_EN    
HAL_Status HalSsiTxGdmaInit(PHAL_SSI_OP pHalSsiOp, PHAL_SSI_ADAPTOR pHalSsiAdapter);
void HalSsiTxGdmaDeInit(PHAL_SSI_ADAPTOR pHalSsiAdapter);
HAL_Status HalSsiRxGdmaInit(PHAL_SSI_OP pHalSsiOp, PHAL_SSI_ADAPTOR pHalSsiAdapter);
void HalSsiRxGdmaDeInit(PHAL_SSI_ADAPTOR pHalSsiAdapter);
HAL_Status HalSsiRxMultiBlkChnl(PHAL_SSI_ADAPTOR pHalSsiAdapter);
HAL_Status HalSsiDmaRecv(void * Adapter, uint8_t * pRxData, uint32_t Length);
HAL_Status HalSsiDmaSend(void *Adapter, uint8_t *pTxData, uint32_t Length);

static __inline__ void
HalSsiDmaInit(
    IN PHAL_SSI_ADAPTOR pHalSsiAdapter
)
{
    #if CONFIG_CHIP_E_CUT
    HalSsiDmaInitRtl8195a_V04((void *)pHalSsiAdapter);
    #else
    HalSsiDmaInitRtl8195a((void *)pHalSsiAdapter);
    #endif
}
/*
static __inline__ HAL_Status HalSsiDmaSend(void *Adapter, uint8_t *pTxData, uint32_t Length)
{
    return (HalSsiDmaSendRtl8195a(Adapter, pTxData, Length));
}

static __inline__ HAL_Status HalSsiDmaRecv(void *Adapter, uint8_t  *pRxData, uint32_t Length)
{
    return (HalSsiDmaRecvRtl8195a(Adapter, pRxData, Length));
}
*/   

#endif  // end of "#ifdef CONFIG_GDMA_EN"

#endif

