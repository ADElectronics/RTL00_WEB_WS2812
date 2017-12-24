/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _HAL_SDIO_H_
#define _HAL_SDIO_H_

#include "rtl8195a_sdio.h"

#if SDIO_API_DEFINED
#include "spdio_api.h"
#endif

#if !SDIO_BOOT_DRIVER
#include "mailbox.h"
#endif
#define PURE_SDIO_INIC           0  // is a pure SDIO iNIC device or a SDIO iNIC + peripheral device

#if SDIO_BOOT_DRIVER
typedef struct _HAL_SDIO_ADAPTER_ {
	uint8_t				*pTXBDAddr;			/* The TX_BD start address */
	PSDIO_TX_BD		pTXBDAddrAligned;	/* The TX_BD start address, it must be 4-bytes aligned */
	PSDIO_TX_BD_HANDLE	pTXBDHdl;		/* point to the allocated memory for TX_BD Handle array */
	uint16_t				TXBDWPtr;		    /* The SDIO TX(Host->Device) BD local write index, different with HW maintained write Index. */
	uint16_t				TXBDRPtr;		    /* The SDIO TX(Host->Device) BD read index */
	uint16_t				TXBDRPtrReg;		/* The SDIO TX(Host->Device) BD read index has been write to HW register */
    uint16_t             reserve1;
    
	uint8_t				*pRXBDAddr;			/* The RX_BD start address */
	PSDIO_RX_BD		pRXBDAddrAligned;	/* The RX_BD start address, it must be 8-bytes aligned */
	PSDIO_RX_BD_HANDLE	pRXBDHdl;		/* point to the allocated memory for RX_BD Handle array */
	uint16_t				RXBDWPtr;		    /* The SDIO RX(Device->Host) BD write index */
	uint16_t				RXBDRPtr;		    /* The SDIO RX(Device->Host) BD local read index, different with HW maintained Read Index. */
	uint16_t				IntMask;			/* The Interrupt Mask */
	uint16_t				IntStatus;			/* The Interrupt Status */
	uint32_t				Events;				/* The Event to the SDIO Task */

	uint32_t				EventSema;			/* Semaphore for SDIO events, use to wakeup the SDIO task */	
    uint8_t              CCPWM;              /* the value write to register CCPWM, which will sync to Host HCPWM */
    uint8_t              reserve2;
    uint16_t             CCPWM2;             /* the value write to register CCPWM2, which will sync to Host HCPWM2 */
    
	int8_t              (*Tx_Callback)(void *pAdapter, uint8_t *pPkt, uint16_t Offset, uint16_t PktSize);	/* to hook the WLan driver TX callback function to handle a Packet TX */
	void			*pTxCb_Adapter;		/* a pointer will be used to call the TX Callback function, 
											which is from the TX CallBack function register */
	int8_t			(*pTxCallback_Backup)(void *pAdapter, uint8_t *pPkt, uint16_t Offset, uint16_t PktSize);	// Use to back up the registered TX Callback function, for MP/Normal mode switch
	void			*pTxCb_Adapter_Backup;	// Backup the pTxCb_Adapter, for MP/Normal mode switch
	_LIST			FreeTxPktList;		/* The list to queue free Tx packets handler */
	_LIST			RxPktList;			/* The list to queue RX packets */
	_LIST			FreeRxPktList;		/* The list to queue free Rx packets handler */
	SDIO_TX_PACKET	*pTxPktHandler;		/* to store allocated TX Packet handler memory address */
	SDIO_RX_PACKET	*pRxPktHandler;		/* to store allocated RX Packet handler memory address */
	uint32_t				RxInQCnt;			/* The packet count for Rx In Queue */
	uint32_t				MemAllocCnt;		// Memory allocated count, for debug only
	uint32_t				MAllocFailedCnt;	// MemAlloc Failed count, for debugging
	
//	void			*pHalOp;			/* point to HAL operation function table */
} HAL_SDIO_ADAPTER, *PHAL_SDIO_ADAPTER;

extern BOOL SDIO_Device_Init_Rom(
	IN PHAL_SDIO_ADAPTER pSDIODev
);
extern void SDIO_Device_DeInit_Rom(
	IN PHAL_SDIO_ADAPTER pSDIODev
);
extern void SDIO_Send_C2H_IOMsg_Rom(
	IN PHAL_SDIO_ADAPTER pSDIODev, 
	IN uint32_t *C2HMsg
);
extern uint8_t SDIO_Send_C2H_PktMsg_Rom(
	IN PHAL_SDIO_ADAPTER pSDIODev, 
	IN uint8_t *C2HMsg, 
	IN uint16_t MsgLen
);
extern void SDIO_Register_Tx_Callback_Rom(
	IN PHAL_SDIO_ADAPTER pSDIODev,
	IN int8_t (*Tx_Callback)(void *pAdapter, uint8_t *pPkt, uint16_t Offset, uint16_t PktSize),
	IN void *pAdapter	
);
extern int8_t SDIO_Rx_Callback_Rom(
	IN PHAL_SDIO_ADAPTER pSDIODev,
	IN void *pData,
	IN uint16_t Offset,
	IN uint16_t Length,
	IN uint8_t CmdType
);

#else   // else of "#if SDIO_BOOT_DRIVER"
typedef struct _HAL_SDIO_ADAPTER_ {
//	uint8_t				*pTxBuff;			/* point to the SDIO TX Buffer */
//	uint8_t				*pTxBuffAligned;	/* point to the SDIO TX Buffer with 4-bytes aligned */
//	uint32_t				TXFifoRPtr;		    /* The SDIO TX(Host->Device) FIFO buffer read pointer */
#if SDIO_API_DEFINED
	void 			*spdio_priv;		/*Data from User*/
#endif
	uint8_t				*pTXBDAddr;			/* The TX_BD start address */
	PSDIO_TX_BD		pTXBDAddrAligned;	/* The TX_BD start address, it must be 4-bytes aligned */
	PSDIO_TX_BD_HANDLE	pTXBDHdl;		/* point to the allocated memory for TX_BD Handle array */
	uint16_t				TXBDWPtr;		    /* The SDIO TX(Host->Device) BD local write index, different with HW maintained write Index. */
	uint16_t				TXBDRPtr;		    /* The SDIO TX(Host->Device) BD read index */
	uint16_t				TXBDRPtrReg;		/* The SDIO TX(Host->Device) BD read index has been write to HW register */
    
	uint8_t				*pRXBDAddr;			/* The RX_BD start address */
	PSDIO_RX_BD		pRXBDAddrAligned;	/* The RX_BD start address, it must be 8-bytes aligned */
	PSDIO_RX_BD_HANDLE	pRXBDHdl;		/* point to the allocated memory for RX_BD Handle array */
	uint16_t				RXBDWPtr;		    /* The SDIO RX(Device->Host) BD write index */
	uint16_t				RXBDRPtr;		    /* The SDIO RX(Device->Host) BD local read index, different with HW maintained Read Index. */
	uint16_t				IntMask;			/* The Interrupt Mask */
	uint16_t				IntStatus;			/* The Interrupt Status */
	uint32_t				Events;				/* The Event to the SDIO Task */

    uint8_t              CCPWM;              /* the value write to register CCPWM, which will sync to Host HCPWM */
    uint8_t              reserve1;
    uint16_t             CCPWM2;             /* the value write to register CCPWM2, which will sync to Host HCPWM2 */
    uint8_t              CRPWM;              /* sync from Host HRPWM */
    uint8_t              reserve2;
    uint16_t             CRPWM2;             /* sync from Host HRPWM2 */

#if !TASK_SCHEDULER_DISABLED
	_Sema			TxSema;             /* Semaphore for SDIO TX, use to wakeup the SDIO TX task */	
    _Sema           RxSema;             /* Semaphore for SDIO RX, use to wakeup the SDIO RX task */    
#else
	uint32_t				EventSema;			/* Semaphore for SDIO events, use to wakeup the SDIO task */	
#endif
	int8_t              (*Tx_Callback)(void *pAdapter, uint8_t *pPkt, uint16_t Offset, uint16_t PktSize, uint8_t type);	/* to hook the WLan driver TX callback function to handle a Packet TX */
	void			*pTxCb_Adapter;		/* a pointer will be used to call the TX Callback function, 
											which is from the TX CallBack function register */
#if SDIO_API_DEFINED
	int8_t              (*Rx_Done_Callback)(void *pAdapter, uint8_t *pPkt, uint16_t Offset, uint16_t PktSize, uint8_t type);	/* to hook RX done callback function to release packet */
	void			*pRxDoneCb_Adapter;		/* a pointer will be used to call the RX Done Callback function, 
											which is from the TX CallBack function register */
#endif
	int8_t			(*pTxCallback_Backup)(void *pAdapter, uint8_t *pPkt, uint16_t Offset, uint16_t PktSize, uint8_t type);	// Use to back up the registered TX Callback function, for MP/Normal mode switch
	void			*pTxCb_Adapter_Backup;	// Backup the pTxCb_Adapter, for MP/Normal mode switch
#if SDIO_DEBUG
	_LIST			FreeTxPktList;		/* The list to queue free Tx packets handler */
	SDIO_TX_PACKET	*pTxPktHandler;		/* to store allocated TX Packet handler memory address */
#endif
	_LIST			RxPktList;			/* The list to queue RX packets */
	_LIST			FreeRxPktList;		/* The list to queue free Rx packets handler */
//	_LIST			RecyclePktList;		/* The list to queue packets handler to be recycled */
	SDIO_RX_PACKET	*pRxPktHandler;		/* to store allocated RX Packet handler memory address */
	_Mutex			RxMutex;			/* The Mutex to protect RxPktList */
	uint32_t				RxInQCnt;			/* The packet count for Rx In Queue */
#if SDIO_DEBUG
	_Mutex			StatisticMutex;		/* The Mutex to protect Statistic data */
	uint32_t				MemAllocCnt;		// Memory allocated count, for debug only
	uint32_t				MAllocFailedCnt;	// MemAlloc Failed count, for debugging
#endif	
	void			*pHalOp;			/* point to HAL operation function table */
	RTL_MAILBOX		*pMBox;				/* the Mail box for other driver module can send message to SDIO driver */

#ifdef PLATFORM_FREERTOS
	xTaskHandle		xSDIOTxTaskHandle;	/* The handle of the SDIO Task for TX, can be used to delte the task */
    xTaskHandle     xSDIORxTaskHandle;  /* The handle of the SDIO Task speical for RX, can be used to delte the task */
#endif
    uint8_t              RxFifoBusy;         /* is the RX BD fetch hardware busy */

#if SDIO_MP_MODE
#if !TASK_SCHEDULER_DISABLED
	uint32_t				MP_Events;				/* The Event to the SDIO Task */
	_Sema			MP_EventSema;		/* Semaphore for SDIO events, use to wakeup the SDIO task */	
    RTL_MAILBOX     *pMP_MBox;  /* the Mail box for communication with other driver module */
#ifdef PLATFORM_FREERTOS
    xTaskHandle     MP_TaskHandle;      /* The handle of the MP loopback Task, can be used to delte the task */
#endif  // end of "#ifdef PLATFORM_FREERTOS"
#endif  // end of "#if !TASK_SCHEDULER_DISABLED"
	// for MP mode
    RTL_TIMER       *pPeriodTimer;      /* a timer to calculate throughput periodically */
	uint8_t				MP_ModeEn;			/* is in MP mode */
	uint8_t				MP_LoopBackEn;		/* is loop-back enabled */
	uint8_t				MP_ContinueTx;		/* is continue TX test enabled */
	uint8_t				MP_ContinueRx;		/* is continue RX test enabled */
	uint8_t				MP_ContinueRxMode;  /* continue RX test mode: static RX Buf, Dyna-Allocate RX Buf, Pre-Allocate RX Buf */
	uint8_t				MP_CRxInfinite;		/* is non-stop SDIO RX, no packet count limit */
    uint16_t				MP_CRxSize;		    /* SDIO RX test packet size */
    uint8_t              *pMP_CRxBuf;        // the buffer for continye RX test
    uint32_t             MP_CRxPktCnt;       /* SDIO RX test packet count */
    uint32_t             MP_CRxPktPendingCnt;       /* SDIO RX test packet pening count */
	uint32_t				MP_TxPktCnt;		/* SDIO TX packet count */
	uint32_t				MP_RxPktCnt;		/* SDIO RX packet count */
	uint32_t				MP_TxByteCnt;		/* SDIO TX Byte count */
	uint32_t				MP_RxByteCnt;		/* SDIO RX Byte count */
	uint32_t				MP_TxDropCnt;		/* SDIO TX Drop packet count */
	uint32_t				MP_RxDropCnt;		/* SDIO RX Drop packet count */

	uint32_t				MP_TxPktCntInPeriod;    /* SDIO TX packet count in a period */
	uint32_t				MP_RxPktCntInPeriod;	/* SDIO RX packet count in a period */
	uint32_t				MP_TxByteCntInPeriod;	/* SDIO TX Byte count in a period */
	uint32_t				MP_RxByteCntInPeriod;	/* SDIO RX Byte count in a period */

	uint32_t				MP_TxAvgTPWin[SDIO_AVG_TP_WIN_SIZE];        /* a window of SDIO TX byte count history, for average throughput calculation */
	uint32_t				MP_RxAvgTPWin[SDIO_AVG_TP_WIN_SIZE];        /* a window of SDIO RX byte count history, for average throughput calculation */
	uint32_t				MP_TxAvgTPWinSum;        /* The sum of all byte-count in the window */
	uint32_t				MP_RxAvgTPWinSum;        /* The sum of all byte-count in the window */
    uint8_t              OldestTxAvgWinIdx;      /* the index of the oldest TX byte count log */
    uint8_t              TxAvgWinCnt;            /* the number of log in the Window */
    uint8_t              OldestRxAvgWinIdx;      /* the index of the oldest RX byte count log */
    uint8_t              RxAvgWinCnt;            /* the number of log in the Window */

	_LIST			MP_RxPktList;		/* The list to queue RX packets, for MP loopback test */
#endif	// end of '#if SDIO_MP_MODE'
} HAL_SDIO_ADAPTER, *PHAL_SDIO_ADAPTER;
#endif  // end of "#else of "#if SDIO_BOOT_DRIVER""


typedef struct _HAL_SDIO_OP_ {
	BOOL (*HalSdioDevInit)(PHAL_SDIO_ADAPTER pSDIODev);	
	void (*HalSdioDevDeInit)(PHAL_SDIO_ADAPTER pSDIODev);
	void (*HalSdioSendC2HIOMsg)(PHAL_SDIO_ADAPTER pSDIODev, uint32_t *C2HMsg);
	uint8_t   (*HalSdioSendC2HPktMsg)(PHAL_SDIO_ADAPTER pSDIODev, uint8_t *C2HMsg, uint16_t MsgLen);
	void (*HalSdioRegTxCallback)(PHAL_SDIO_ADAPTER pSDIODev,int8_t (*CallbackFun)(void *pAdapter, uint8_t *pPkt, uint16_t Offset, uint16_t PktSize, uint8_t Type), void *pAdapter);
	int8_t   (*HalSdioRxCallback)(PHAL_SDIO_ADAPTER pSDIODev, void *pData, uint16_t Offset, uint16_t PktSize, uint8_t CmdType);
#if SDIO_API_DEFINED
	void (*HalSdioRegRxDoneCallback)(PHAL_SDIO_ADAPTER pSDIODev,int8_t (*CallbackFun)(void *pAdapter, uint8_t *pPkt, uint16_t Offset, uint16_t PktSize, uint8_t Type), void *pAdapter);
#endif
#if SDIO_MP_MODE
	void (*HalSdioDevMPApp)(PHAL_SDIO_ADAPTER pSDIODev, uint16_t argc, uint8_t  *argv[]);
#endif
}HAL_SDIO_OP, *PHAL_SDIO_OP;


extern BOOL SDIO_Device_Init(
	IN PHAL_SDIO_ADAPTER pSDIODev
);
extern void SDIO_Device_DeInit(
	IN PHAL_SDIO_ADAPTER pSDIODev
);
extern void SDIO_Send_C2H_IOMsg(
	IN PHAL_SDIO_ADAPTER pSDIODev, 
	IN uint32_t *C2HMsg
);
extern uint8_t SDIO_Send_C2H_PktMsg(
	IN PHAL_SDIO_ADAPTER pSDIODev, 
	IN uint8_t *C2HMsg, 
	IN uint16_t MsgLen
);
extern void SDIO_Register_Tx_Callback(
	IN PHAL_SDIO_ADAPTER pSDIODev,
	IN int8_t (*Tx_Callback)(void *pAdapter, uint8_t *pPkt, uint16_t Offset, uint16_t PktSize, uint8_t Type),
	IN void *pAdapter	
);
#if SDIO_API_DEFINED
extern void SDIO_Register_Rx_Done_Callback(
	IN PHAL_SDIO_ADAPTER pSDIODev,
	IN int8_t (*Rx_Done_Callback)(void *pAdapter, uint8_t *pPkt, uint16_t Offset, uint16_t PktSize, uint8_t Type),
	IN void *pAdapter	
);
#endif
extern int8_t SDIO_Rx_Callback(
	IN PHAL_SDIO_ADAPTER pSDIODev,
	IN void *pData,
	IN uint16_t Offset,
	IN uint16_t Length,
	IN uint8_t CmdType
);
#if SDIO_MP_MODE
extern void SDIO_DeviceMPApp(
	IN PHAL_SDIO_ADAPTER pSDIODev,
	IN uint16_t argc, 
    IN uint8_t  *argv[]
);
#endif

extern PHAL_SDIO_ADAPTER pgSDIODev;
extern void HalSdioInit(void);
extern void HalSdioDeInit(void);
#endif	// #ifndef _HAL_SDIO_H_
