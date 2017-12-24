/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _HAL_I2S_H_
#define _HAL_I2S_H_

#include "rtl8195a_i2s.h"

/* User Define Flags */

#define I2S_MAX_ID                  1   // valid I2S index 0 ~ I2S_MAX_ID

/**********************************************************************/
/* I2S HAL initial data structure */
typedef struct _HAL_I2S_INIT_DAT_ {
    uint8_t                  I2SIdx;         /*I2S index used*/
    uint8_t                  I2SEn;          /*I2S module enable tx/rx/tx+rx*/
    uint8_t                  I2SMaster;      /*I2S Master or Slave mode*/
    uint8_t                  I2SWordLen;     /*I2S Word length 16 or 24bits*/

    uint8_t                  I2SChNum;       /*I2S Channel number mono or stereo*/
    uint8_t                  I2SPageNum;     /*I2S Page Number 2~4*/
    uint16_t                 I2SPageSize;    /*I2S page Size 1~4096 word*/

    uint8_t                  *I2STxData;     /*I2S Tx data pointer*/

    uint8_t                  *I2SRxData;     /*I2S Rx data pointer*/

    uint32_t                 I2STxIntrMSK;   /*I2S Tx Interrupt Mask*/
    uint32_t                 I2STxIntrClr;   /*I2S Tx Interrupt register to clear */

    uint32_t                 I2SRxIntrMSK;   /*I2S Rx Interrupt Mask*/
    uint32_t                 I2SRxIntrClr;   /*I2S Rx Interrupt register to clear*/

	uint16_t                 I2STxIdx;       /*I2S TX page index */
	uint16_t                 I2SRxIdx;       /*I2S RX page index */

	uint16_t                 I2SHWTxIdx;       /*I2S HW TX page index */
	uint16_t                 I2SHWRxIdx;       /*I2S HW RX page index */

	
    uint16_t                 I2SRate;        /*I2S sample rate*/
    uint8_t                  I2STRxAct;      /*I2S tx rx act*/	
}HAL_I2S_INIT_DAT, *PHAL_I2S_INIT_DAT;

/**********************************************************************/
/* I2S Data Structures */
/* I2S Module Selection */
typedef enum _I2S_MODULE_SEL_ {
        I2S0_SEL    =   0x0,
        I2S1_SEL    =   0x1,
}I2S_MODULE_SEL,*PI2S_MODULE_SEL;
/*
typedef struct _HAL_I2S_ADAPTER_ {
    uint32_t                       Enable:1;
    I2S_CTL_REG               I2sCtl;
    I2S_SETTING_REG           I2sSetting;
    uint32_t                       abc;
    uint8_t                        I2sIndex;
}HAL_I2S_ADAPTER, *PHAL_I2S_ADAPTER;
*/
/* I2S HAL Operations */
typedef struct _HAL_I2S_OP_ {
    RTK_STATUS  (*HalI2SInit)       (void *Data);
    RTK_STATUS  (*HalI2SDeInit)     (void *Data);
    RTK_STATUS  (*HalI2STx)       	(void *Data, uint8_t *pBuff);
    RTK_STATUS  (*HalI2SRx)      	(void *Data, uint8_t *pBuff);
    RTK_STATUS  (*HalI2SEnable)     (void *Data);
    RTK_STATUS  (*HalI2SIntrCtrl)   (void *Data);
    uint32_t         (*HalI2SReadReg)    (void *Data, uint8_t I2SReg);
    RTK_STATUS  (*HalI2SSetRate)    (void *Data);
    RTK_STATUS  (*HalI2SSetWordLen) (void *Data);
    RTK_STATUS  (*HalI2SSetChNum)   (void *Data);
    RTK_STATUS  (*HalI2SSetPageNum) (void *Data);
    RTK_STATUS  (*HalI2SSetPageSize) (void *Data);

    RTK_STATUS  (*HalI2SClrIntr)    (void *Data);
    RTK_STATUS  (*HalI2SClrAllIntr) (void *Data);
    RTK_STATUS  (*HalI2SDMACtrl)    (void *Data); 
/*
    void (*HalI2sOnOff)(void *Data);
    BOOL (*HalI2sInit)(void *Data);
    BOOL (*HalI2sSetting)(void *Data);
    BOOL (*HalI2sEn)(void *Data);
    BOOL (*HalI2sIsrEnAndDis) (void *Data);
    BOOL (*HalI2sDumpReg)(void *Data);
    BOOL (*HalI2s)(void *Data);
*/
}HAL_I2S_OP, *PHAL_I2S_OP;


/**********************************************************************/

/* I2S Pinmux Selection */
#if 0
typedef enum _I2S0_PINMUX_ {
    I2S0_TO_S0      =   0x0,
    I2S0_TO_S1      =   0x1,
    I2S0_TO_S2      =   0x2,
}I2S0_PINMUX, *PI2S0_PINMUX;

typedef enum _I2S1_PINMUX_ {
    I2S1_TO_S0      =   0x0,
    I2S1_TO_S1      =   0x1,
}I2S1_PINMUX, *PI2S1_PINMUX;
#endif

typedef enum _I2S_PINMUX_ {
    I2S_S0      =   0,
    I2S_S1      =   1,
    I2S_S2      =   2,
    I2S_S3      =   3
}I2S_PINMUX, *PI2S_PINMUX;


/* I2S Module Status */
typedef enum _I2S_MODULE_STATUS_ {
    I2S_DISABLE     =   0x0,
    I2S_ENABLE      =   0x1,
}I2S_MODULE_STATUS, *PI2S_MODULE_STATUS;


/* I2S Device Status */
typedef enum _I2S_Device_STATUS_ {
    I2S_STS_UNINITIAL   =   0x00,
    I2S_STS_INITIALIZED =   0x01,
    I2S_STS_IDLE        =   0x02,
    
    I2S_STS_TX_READY    =   0x03,    
    I2S_STS_TX_ING      =   0x04,
    
    I2S_STS_RX_READY    =   0x05,
    I2S_STS_RX_ING      =   0x06,

    I2S_STS_TRX_READY   =   0x07,    
    I2S_STS_TRX_ING     =   0x08,
    
    I2S_STS_ERROR       =   0x09,
}I2S_Device_STATUS, *PI2S_Device_STATUS;


/* I2S Feature Status */
typedef enum _I2S_FEATURE_STATUS_{
    I2S_FEATURE_DISABLED    =   0,
    I2S_FEATURE_ENABLED     =   1,
}I2S_FEATURE_STATUS,*PI2S_FEATURE_STATUS;

/* I2S Device Mode */
typedef enum _I2S_DEV_MODE_ {
	I2S_MASTER_MODE =   0x0,
    I2S_SLAVE_MODE  =   0x1
}I2S_DEV_MODE, *PI2S_DEV_MODE;

/* I2S Word Length */
typedef enum _I2S_WORD_LEN_ {
	I2S_WL_16 = 0x0,
    I2S_WL_24 = 0x1,    
}I2S_WORD_LEN, *PI2S_WORD_LEN;

/* I2S Bus Transmit/Receive */
typedef enum _I2S_DIRECTION_ {
    I2S_ONLY_RX     =   0x0,
    I2S_ONLY_TX     =   0x1,
    I2S_TXRX        =   0x2
}I2S_DIRECTION, *PI2S_DIRECTION;

/* I2S Channel number */
typedef enum _I2S_CH_NUM_ {
    I2S_CH_STEREO   =   0x0,
    I2S_CH_RSVD     =   0x1,
    I2S_CH_MONO     =   0x2
}I2S_CH_NUM, *PI2S_CH_NUM;

/* I2S Page number */
typedef enum _I2S_PAGE_NUM_ {
    I2S_1PAGE       =   0x0,
    I2S_2PAGE       =   0x1,
    I2S_3PAGE       =   0x2,
    I2S_4PAGE       =   0x3
}I2S_PAGE_NUM, *PI2S_PAGE_NUM;

/* I2S Sample rate*/
typedef enum _I2S_SAMPLE_RATE_ {
    I2S_SR_8KHZ     =   0x00,	// /12
    I2S_SR_16KHZ    =   0x01,	// /6
    I2S_SR_24KHZ    =   0x02,	// /4
	I2S_SR_32KHZ	= 	0x03,	// /3
    I2S_SR_48KHZ    =   0x05,	// /2
	I2S_SR_96KHZ	=	0x06,	// x1, base 96kHz
	I2S_SR_7p35KHZ	= 	0x10,
	I2S_SR_11p02KHZ	= 	0x11,
	I2S_SR_22p05KHZ	= 	0x12,
	I2S_SR_29p4KHZ	= 	0x13,
	I2S_SR_44p1KHZ	= 	0x15,	
	I2S_SR_88p2KHZ	= 	0x16	// x1, base 88200Hz
}I2S_SAMPLE_RATE, *PI2S_SAMPLE_RATE;

/* I2S TX interrupt mask/status */
typedef enum _I2S_TX_IMR_ {
    I2S_TX_INT_PAGE0_OK = (1<<0),
    I2S_TX_INT_PAGE1_OK = (1<<1),
    I2S_TX_INT_PAGE2_OK = (1<<2),
    I2S_TX_INT_PAGE3_OK = (1<<3),
    I2S_TX_INT_FULL     = (1<<4),
    I2S_TX_INT_EMPTY    = (1<<5)    
} I2S_TX_IMR, *PI2S_TX_IMR;

/* I2S RX interrupt mask/status */
typedef enum _I2S_RX_IMR_ {
    I2S_RX_INT_PAGE0_OK = (1<<0),
    I2S_RX_INT_PAGE1_OK = (1<<1),
    I2S_RX_INT_PAGE2_OK = (1<<2),
    I2S_RX_INT_PAGE3_OK = (1<<3),
    I2S_RX_INT_EMPTY    = (1<<4),
    I2S_RX_INT_FULL     = (1<<5)    
} I2S_RX_IMR, *PI2S_RX_IMR;

/* I2S User Callbacks */
typedef struct _SAL_I2S_USER_CB_{
    void (*TXCB)        (void *Data);
    void (*TXCCB)       (void *Data);
    void (*RXCB)        (void *Data);
    void (*RXCCB)       (void *Data);
    void (*RDREQCB)     (void *Data);
    void (*ERRCB)       (void *Data);
    void (*GENCALLCB)   (void *Data);
}SAL_I2S_USER_CB,*PSAL_I2S_USER_CB;

typedef struct _I2S_USER_CB_{
    void (*TxCCB)(uint32_t id, char *pbuf);
    uint32_t TxCBId;
    void (*RxCCB)(uint32_t id, char *pbuf);
    uint32_t RxCBId;
}I2S_USER_CB,*PI2S_USER_CB;

/* Software API Level I2S Handler */
typedef struct _HAL_I2S_ADAPTER_{
    uint8_t                      DevNum;             //I2S device number
    uint8_t                      PinMux;             //I2S pin mux seletion
    uint8_t                      RSVD0;              //Reserved
    volatile uint8_t             DevSts;             //I2S device status
    
    uint32_t                     RSVD2;              //Reserved
    uint32_t                     I2SExd;             //I2S extended options:
                                                //bit 0: I2C RESTART supported,
                                                //          0 for NOT supported,
                                                //          1 for supported
                                                //bit 1: I2C General Call supported
                                                //          0 for NOT supported,
                                                //          1 for supported
                                                //bit 2: I2C START Byte supported
                                                //          0 for NOT supported,
                                                //          1 for supported
                                                //bit 3: I2C Slave-No-Ack
                                                //         supported
                                                //          0 for NOT supported,
                                                //          1 for supported
                                                //bit 4: I2C bus loading,
                                                //          0 for 100pf, 
                                                //          1  for 400pf
                                                //bit 5: I2C slave ack to General
                                                //         Call
                                                //bit 6: I2C User register address
                                                //bit 7: I2C 2-Byte User register
                                                //         address
                                                //bit 31~bit 8: Reserved
    uint32_t                     ErrType;         //
    uint32_t                     TimeOut;            //I2S IO Timeout count
                                                                            
    PHAL_I2S_INIT_DAT       pInitDat;           //Pointer to I2S initial data struct
    I2S_USER_CB             UserCB;            //Pointer to I2S User Callback
    IRQ_HANDLE              IrqHandle;          // Irq Handler

    uint32_t* TxPageList[4];       // The Tx DAM buffer: pointer of each page
    uint32_t* RxPageList[4];       // The Tx DAM buffer: pointer of each page
}HAL_I2S_ADAPTER, *PHAL_I2S_ADAPTER;

typedef struct _HAL_I2S_DEF_SETTING_{
    uint8_t I2SMaster;           // Master or Slave mode
    uint8_t DevSts;             //I2S device status
    uint8_t I2SChNum;           //I2S Channel number mono or stereo
    uint8_t I2SPageNum;         //I2S Page number 2~4
    uint8_t  I2STRxAct;          //I2S tx rx act, tx only or rx only or tx+rx
    uint8_t  I2SWordLen;         //I2S Word length 16bit or 24bit
    uint16_t I2SPageSize;        //I2S Page size 1~4096 word
                                                
    uint16_t I2SRate;            //I2S sample rate 8k ~ 96khz
    
    uint32_t I2STxIntrMSK;   /*I2S Tx Interrupt Mask*/
    uint32_t I2SRxIntrMSK;   /*I2S Rx Interrupt Mask*/
}HAL_I2S_DEF_SETTING, *PHAL_I2S_DEF_SETTING;



/**********************************************************************/
HAL_Status
RtkI2SLoadDefault(IN  void *Adapter, IN  void *Setting);

HAL_Status
RtkI2SInit(IN  void *Data);

HAL_Status
RtkI2SDeInit(IN  void *Data);

HAL_Status
RtkI2SEnable(IN  void *Data);

HAL_Status
RtkI2SDisable(IN  void *Data);

extern HAL_Status 
HalI2SInit( IN void *Data);

extern void 
HalI2SDeInit( IN void *Data);

extern HAL_Status 
HalI2SDisable( IN void *Data);

extern HAL_Status 
HalI2SEnable( IN void *Data);




/**********************************************************************/


void I2S0ISRHandle(void *Data);
void I2S1ISRHandle(void *Data);


/**********************************************************************/

void HalI2SOpInit(
    IN  void *Data
);


#endif

