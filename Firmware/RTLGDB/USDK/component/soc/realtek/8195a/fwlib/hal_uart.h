/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _HAL_UART_H_
#define _HAL_UART_H_

#include "rtl8195a_uart.h"

/**
 * RUART Configurations
 */
#define UART_WAIT_FOREVER       0xffffffff

#define UART_DMA_MBLK_NUM       16      // maximum block number for each DMA transfer, it must <= 16 
#define UART_DMA_BLOCK_SIZE     4092    // the block size of multiple block DMA, it cann0t over 4095

typedef struct _HAL_UART_DMA_MULTIBLK_ {
    volatile GDMA_CH_LLI_ELE GdmaChLli[UART_DMA_MBLK_NUM];
    struct GDMA_CH_LLI Lli[UART_DMA_MBLK_NUM];
    struct BLOCK_SIZE_LIST BlockSizeList[UART_DMA_MBLK_NUM];   
}UART_DMA_MULTIBLK, *PUART_DMA_MULTIBLK;

typedef struct _UART_DMA_CONFIG_ {
    uint8_t TxDmaEnable;
    uint8_t RxDmaEnable;
    uint8_t TxDmaBurstSize;
    uint8_t RxDmaBurstSize;
    void *pHalGdmaOp;
    void *pTxHalGdmaAdapter;
    void *pRxHalGdmaAdapter;
    IRQ_HANDLE TxGdmaIrqHandle;
    IRQ_HANDLE RxGdmaIrqHandle;
#if defined(E_CUT_ROM_DOMAIN) || (!defined(CONFIG_RELEASE_BUILD_LIBRARIES))
    UART_DMA_MULTIBLK *pTxDmaBlkList;       // point to multi-block list
    UART_DMA_MULTIBLK *pRxDmaBlkList;       // point to multi-block list
    uint8_t TxDmaMBChnl;     // is using DMA multiple block channel
    uint8_t RxDmaMBChnl;     // is using DMA multiple block channel
#endif
}UART_DMA_CONFIG, *PUART_DMA_CONFIG;

typedef struct _HAL_RUART_ADAPTER_ {
    uint32_t BaudRate;
    uint32_t FlowControl;
    uint32_t FifoControl;
    uint32_t Interrupts;
    uint32_t TxCount;     // how many byte to TX
    uint32_t RxCount;     // how many bytes to RX
    uint8_t *pTxBuf;
    uint8_t *pRxBuf;
    HAL_UART_State State;       // UART state
    uint8_t Status;      // Transfer Status
    uint8_t Locked;      // is UART locked for operation
    uint8_t UartIndex;
    uint8_t WordLen;     // word length select: 0 -> 7 bits, 1 -> 8 bits
    uint8_t StopBit;     // word length select: 0 -> 1 stop bit, 1 -> 2 stop bit
    uint8_t Parity;      // parity check enable
    uint8_t ParityType;  // parity check type
    uint8_t StickParity;
    uint8_t ModemStatus; // the modem status
    uint8_t DmaEnable;
    uint8_t TestCaseNumber;
    uint8_t PinmuxSelect;
    BOOL PullMode;
    IRQ_HANDLE IrqHandle;
    PUART_DMA_CONFIG DmaConfig;
    void (*ModemStatusInd)(void *pAdapter);    // modem status indication interrupt handler
    void (*TxTDCallback)(void *pAdapter);      // User Tx Done callback function
    void (*RxDRCallback)(void *pAdapter);      // User Rx Data ready callback function
    void (*TxCompCallback)(void *para);    // User Tx complete callback function
    void (*RxCompCallback)(void *para);    // User Rx complete callback function
    void *TxTDCbPara;   // the pointer agrument for TxTDCallback
    void *RxDRCbPara;   // the pointer agrument for RxDRCallback
    void *TxCompCbPara; // the pointer argument for TxCompCbPara
    void *RxCompCbPara; // the pointer argument for RxCompCallback
    void (*EnterCritical)(void);
    void (*ExitCritical)(void);

#if defined(E_CUT_ROM_DOMAIN) || (!defined(CONFIG_RELEASE_BUILD_LIBRARIES))
    //1 New member only can be added below: members above must be fixed for ROM code
    uint32_t *pDefaultBaudRateTbl;      // point to the table of pre-defined baud rate
    uint8_t *pDefaultOvsrRTbl;         // point to the table of OVSR for pre-defined baud rate
    uint16_t *pDefaultDivTbl;           // point to the table of DIV for pre-defined baud rate
    uint8_t  *pDefOvsrAdjBitTbl_10;     // point to the table of OVSR-Adj bits for 10 bits
    uint8_t  *pDefOvsrAdjBitTbl_9;     // point to the table of OVSR-Adj bits for 9 bits
    uint8_t  *pDefOvsrAdjBitTbl_8;     // point to the table of OVSR-Adj bits for 8 bits
    uint16_t *pDefOvsrAdjTbl_10;       // point to the table of OVSR-Adj for pre-defined baud rate
    uint16_t *pDefOvsrAdjTbl_9;       // point to the table of OVSR-Adj for pre-defined baud rate
    uint16_t *pDefOvsrAdjTbl_8;       // point to the table of OVSR-Adj for pre-defined baud rate
    PUART_DMA_MULTIBLK pTxDMAMBlk;  // point to the Link List Table of the DMA Multiple Block
    PUART_DMA_MULTIBLK pRxDMAMBlk;  // point to the Link List Table of the DMA Multiple Block
    uint32_t BaudRateUsing;             // Current using Baud-Rate    
    uint8_t WordLenUsing;             // Current using Word Length
    uint8_t ParityUsing;             // Current using Parity check
    uint8_t RTSCtrl;               // Software RTS Control

#if 0//CONFIG_CHIP_E_CUT
    uint8_t  TxState;
    uint8_t  RxState;
    uint32_t TxInitSize;     // how many byte to TX at atart
    uint32_t RxInitSize;     // how many bytes to RX at start

    void (*RuartEnterCritical)(void *para);   // enter critical: disable UART interrupt
    void (*RuartExitCritical)(void *para);    // exit critical: re-enable UART interrupt
    void (*TaskYield)(void *para);    // User Task Yield: do a context switch while waitting
    void *TaskYieldPara;   // the agrument (pointer) for TaskYield
#endif    // #if CONFIG_CHIP_E_CUT
#endif
}HAL_RUART_ADAPTER, *PHAL_RUART_ADAPTER;

typedef struct _HAL_RUART_OP_ {
    void (*HalRuartAdapterLoadDef)(void *pAdp, uint8_t UartIdx);    // Load UART adapter default setting
    void (*HalRuartTxGdmaLoadDef)(void *pAdp, void *pCfg);     // Load TX GDMA default setting
    void (*HalRuartRxGdmaLoadDef)(void *pAdp, void *pCfg);     // Load RX GDMA default setting
    HAL_Status (*HalRuartResetRxFifo)(void *Data);
    HAL_Status (*HalRuartInit)(void *Data);
    void (*HalRuartDeInit)(void *Data);
    HAL_Status (*HalRuartPutC)(void *Data, uint8_t TxData);
    uint32_t  (*HalRuartSend)(void *Data, uint8_t *pTxData, uint32_t Length, uint32_t Timeout);
    HAL_Status  (*HalRuartIntSend)(void *Data, uint8_t *pTxData, uint32_t Length);
    HAL_Status  (*HalRuartDmaSend)(void *Data, uint8_t *pTxData, uint32_t Length);
    HAL_Status  (*HalRuartStopSend)(void *Data);
    HAL_Status (*HalRuartGetC)(void *Data, uint8_t *pRxByte);
    uint32_t  (*HalRuartRecv)(void *Data, uint8_t  *pRxData, uint32_t Length, uint32_t Timeout);
    HAL_Status  (*HalRuartIntRecv)(void *Data, uint8_t  *pRxData, uint32_t Length);
    HAL_Status  (*HalRuartDmaRecv)(void *Data, uint8_t  *pRxData, uint32_t Length);
    HAL_Status  (*HalRuartStopRecv)(void *Data);
    uint8_t   (*HalRuartGetIMR)(void *Data);
    void (*HalRuartSetIMR)(void *Data);
    uint32_t  (*HalRuartGetDebugValue)(void *Data, uint32_t DbgSel);
    void (*HalRuartDmaInit)(void *Data);
    void (*HalRuartRTSCtrl)(void *Data, BOOLEAN RtsCtrl);
    void (*HalRuartRegIrq)(void *Data);
    void (*HalRuartIntEnable)(void *Data);
    void (*HalRuartIntDisable)(void *Data);
}HAL_RUART_OP, *PHAL_RUART_OP;

typedef struct _RUART_DATA_ {
    PHAL_RUART_ADAPTER pHalRuartAdapter;
    BOOL PullMode;
    uint8_t   BinaryData;
    uint8_t   SendBuffer;
    uint8_t   RecvBuffer;
}RUART_DATA, *PRUART_DATA;

typedef struct _RUART_ADAPTER_ {
    PHAL_RUART_OP      pHalRuartOp;
    PHAL_RUART_ADAPTER pHalRuartAdapter;
    PUART_DMA_CONFIG   pHalRuartDmaCfg;
}RUART_ADAPTER, *PRUART_ADAPTER;

extern void
HalRuartOpInit(
        IN void *Data
);

extern HAL_Status
HalRuartTxGdmaInit(
    PHAL_RUART_ADAPTER pHalRuartAdapter,
    PUART_DMA_CONFIG pUartGdmaConfig,
    uint8_t IsMultiBlk    
);

extern void
HalRuartTxGdmaDeInit(
    PUART_DMA_CONFIG pUartGdmaConfig
);

extern HAL_Status
HalRuartRxGdmaInit(
    PHAL_RUART_ADAPTER pHalRuartAdapter,
    PUART_DMA_CONFIG pUartGdmaConfig,
    uint8_t IsMultiBlk    
);

extern void
HalRuartRxGdmaDeInit(
    PUART_DMA_CONFIG pUartGdmaConfig
);

extern HAL_Status
HalRuartResetTxFifo(
    void *Data
);

extern HAL_Status HalRuartResetTRxFifo(IN void *Data);

extern HAL_Status
HalRuartResetRxFifo(
    IN void *Data
);

extern HAL_Status 
HalRuartSetBaudRate(
        IN void *Data
);

extern HAL_Status 
HalRuartInit(
    IN void *Data
);

extern void
HalRuartDeInit(
    IN void *Data
);

extern HAL_Status 
HalRuartDisable(
    IN void *Data
);

extern HAL_Status 
HalRuartEnable(
    IN void *Data
);

HAL_Status 
HalRuartFlowCtrl(
    IN void *Data
);

void
HalRuartEnterCritical(
    IN void *Data
);

void
HalRuartExitCritical(
    IN void *Data
);

HAL_Status
HalRuartDmaSend(
    IN void *Data,
    IN uint8_t *pTxBuf,
    IN uint32_t Length
);

HAL_Status
HalRuartDmaRecv(
    IN void *Data,
    IN uint8_t *pRxBuf,
    IN uint32_t Length
);

extern const HAL_RUART_OP _HalRuartOp;
extern HAL_Status RuartLock (PHAL_RUART_ADAPTER pHalRuartAdapter);
extern void RuartUnLock (PHAL_RUART_ADAPTER pHalRuartAdapter);

#endif

