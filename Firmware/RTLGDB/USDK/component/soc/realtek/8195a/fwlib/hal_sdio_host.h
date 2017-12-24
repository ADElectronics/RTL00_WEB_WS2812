/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _HAL_SDIO_HOST_H_
#define _HAL_SDIO_HOST_H_


#include "rtl8195a_sdio_host.h"


#define SDIO_HOST_WAIT_FOREVER       0xFFFFFFFF


typedef struct _HAL_SDIO_HOST_OP_ {
	HAL_Status	(*HalSdioHostInitHost)			(void *Data);
	HAL_Status	(*HalSdioHostInitCard)			(void *Data);
	HAL_Status	(*HalSdioHostDeInit)			(void *Data);
	HAL_Status	(*HalSdioHostRegIrq)			(void *Data);
	HAL_Status	(*HalSdioHostReadBlocksDma)		(void *Data, uint64_t ReadAddr, uint32_t BlockCnt);
	HAL_Status	(*HalSdioHostWriteBlocksDma)	(void *Data, uint64_t WriteAddr, uint32_t BlockCnt);
	HAL_Status	(*HalSdioHostStopTransfer)		(void *Data);
	HAL_Status	(*HalSdioHostGetCardStatus) 	(void *Data);
	HAL_Status	(*HalSdioHostGetSdStatus) 		(void *Data);
    HAL_Status  (*HalSdioHostChangeSdClock)     (void *Data, uint8_t Frequency);
	HAL_Status	(*HalSdioHostErase)				(void *Data, uint64_t StartAddr, uint64_t EndAddr);
	HAL_Status	(*HalSdioHostGetWriteProtect)	(void *Data);
	HAL_Status	(*HalSdioHostSetWriteProtect)	(void *Data, uint8_t Setting);
}HAL_SDIO_HOST_OP, *PHAL_SDIO_HOST_OP;

// SDIO error type 
typedef enum _SDIO_ERR_TYPE_ {
    SDIO_ERR_DAT_CRC    =   0x01,
    SDIO_ERR_CMD_TIMEOUT    =   0x02,
}SDIO_ERR_TYPE;

typedef enum _SDIO_XFER_TYPE_{
	SDIO_XFER_NOR	= 0x00, // normal 
	SDIO_XFER_R	= 0x01,	// read and write block
	SDIO_XFER_W	= 0x02,	// read and write block
}SDIO_XFER_TYPE;

typedef struct _HAL_SDIO_HOST_ADAPTER_{
	IRQ_HANDLE				IrqHandle;			//+0..
	ADMA2_DESC_FMT			*AdmaDescTbl;		//+16
	uint32_t						Response[4];		//+20,24,28,32
	uint32_t						CardOCR;			//+36
	uint32_t 					CardStatus;			//+40
	uint32_t						IsWriteProtect;		//+44
	uint8_t 						SdStatus[SD_STATUS_LEN]; //+48..
	uint8_t						Csd[CSD_REG_LEN];	//+112..
    volatile uint8_t             CmdCompleteFlg;	//+128
    volatile uint8_t             XferCompleteFlg; //+129
	volatile uint8_t             ErrIntFlg;		//+130
    volatile uint8_t             CardCurState;	//+131
	uint8_t						IsSdhc;		//+132
	uint8_t						CurrSdClk;	//+133
	uint16_t 					RCA;		//+134
	uint16_t						SdSpecVer;	//+136
	SDIO_ERR_TYPE			errType;	//+140
	SDIO_XFER_TYPE			XferType;	//+144
	void (*XferCompCallback)(void *pAdapter);
	void *XferCompCbPara;
	void (*ErrorCallback)(void *pAdapter);
	void *ErrorCbPara;
	void (*CardInsertCallBack)(void *pAdapter);
	void *CardInsertCbPara;
	void (*CardRemoveCallBack)(void *pAdapter);
	void *CardRemoveCbPara;
}HAL_SDIO_HOST_ADAPTER, *PHAL_SDIO_HOST_ADAPTER;

extern HAL_SDIO_HOST_ADAPTER SdioHostAdapter;

extern HAL_Status 
HalSdioHostInit(
	IN void *Data
);

extern HAL_Status 
HalSdioHostDeInit(
	IN void *Data
);

extern HAL_Status 
HalSdioHostEnable(
	IN void *Data
);

extern HAL_Status 
HalSdioHostDisable(
	IN void *Data
);

extern void
HalSdioHostOpInit(
	IN void *Data
);

#endif

