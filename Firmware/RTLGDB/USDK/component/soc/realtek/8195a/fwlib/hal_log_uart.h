/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _HAL_LOG_UART_H_
#define _HAL_LOG_UART_H_

#include "hal_diag.h"

#define LOG_UART_WAIT_FOREVER       0xffffffff

// Define Line Control Register Bits
typedef enum {
    LCR_DLS_5B = 0,      // Data Length: 5 bits
    LCR_DLS_6B = BIT(0),      // Data Length: 6 bits
    LCR_DLS_7B = BIT(1),      // Data Length: 7 bits
    LCR_DLS_8B = (BIT(1)|BIT(0)),      // Data Length: 7 bits

    LCR_STOP_1B = 0,      // Number of stop bits: 1
    LCR_STOP_2B = BIT(2), // Number of stop bits: 1.5(data len=5) or 2

    LCR_PARITY_NONE = 0,      // Parity Enable: 0
    LCR_PARITY_ODD = BIT(3),      // Parity Enable: 1, Even Parity: 0
    LCR_PARITY_EVEN = (BIT(4)|BIT(3)), // Parity Enable: 1, Even Parity: 1

    LCR_BC = BIT(6),      // Break Control Bit
    LCR_DLAB = BIT(7)      // Divisor Latch Access Bit
} LOG_UART_LINE_CTRL;

// define Log UART Interrupt Indication ID
/*
IIR[3:0]:
0000 = modem status
0001 = no interrupt pending
0010 = THR empty
0100 = received data available
0110 = receiver line status
0111 = busy detect
1100 = character timeout
*/
typedef enum {
    IIR_MODEM_STATUS = 0,   // Clear to send or data set ready or ring indicator or data carrier detect.
    IIR_NO_PENDING = 1,
    IIR_THR_EMPTY = 2,   // TX FIFO level lower than threshold or FIFO empty
    IIR_RX_RDY = 4,     // RX data ready
    IIR_RX_LINE_STATUS = 6, // Overrun/parity/framing errors or break interrupt
    IIR_BUSY = 7,
    IIR_CHAR_TIMEOUT = 12   // timeout: Rx dara ready but no read 
} LOG_UART_INT_ID;

// Define Interrupt Enable Bit
typedef enum {
    IER_ERBFI = BIT(0),   // Enable Received Data Available Interrupt
    IER_ETBEI = BIT(1),   // Enable Transmit Holding Register Empty Interrupt
    IER_ELSI =  BIT(2),   // Enable Receiver Line Status Interrupt
    IER_EDSSI = BIT(3),   // Enable Modem Status Interrupt
    IER_PTIME = BIT(7)    // Programmable THRE Interrupt Mode Enable
} LOG_UART_INT_EN;

// Define Line Status Bit
typedef enum {
    LSR_DR =   BIT(0),   // Data Ready bit
    LSR_OE =   BIT(1),   // Overrun error bit
    LSR_PE =   BIT(2),   // Parity Error bit
    LSR_FE =   BIT(3),   // Framing Error bit
    LSR_BI =   BIT(4),   // Break Interrupt bit
    LSR_THRE = BIT(5),   // Transmit Holding Register Empty bit(IER_PTIME=0)
    LSR_FIFOF = BIT(5),  // Transmit FIFO Full bit(IER_PTIME=1)
    LSR_TEMT = BIT(6),   // Transmitter Empty bit 
    LSR_RFE =  BIT(7)    // Receiver FIFO Error bit    
} LOG_UART_LINE_STATUS;

enum {
    LOG_UART_RST_TX_FIFO = 0x01,
    LOG_UART_RST_RX_FIFO = 0x02
};

#define LOG_UART_TX_FIFO_DEPTH      16
#define LOG_UART_RX_FIFO_DEPTH      16

// Define FIFO Control Register Bits
typedef enum {
    FCR_FIFO_EN      = BIT(0),   // FIFO Enable.
    FCR_RST_RX       = BIT(1),   // RCVR FIFO Reset, self clear
    FCR_RST_TX       = BIT(2),   // XMIT FIFO Reset, self clear
    FCR_TX_TRIG_EMP  = 0,        // TX Empty Trigger: FIFO empty
    FCR_TX_TRIG_2CH  = BIT(4),   // TX Empty Trigger: 2 characters in the FIFO
    FCR_TX_TRIG_QF   = BIT(5),   // TX Empty Trigger: FIFO 1/4 full
    FCR_TX_TRIG_HF   = (BIT(5)|BIT(4)),   // TX Empty Trigger: FIFO 1/2 full
    FCR_TX_TRIG_MASK = (BIT(5)|BIT(4)),   // TX Empty Trigger Bit Mask
    FCR_RX_TRIG_1CH  = 0,        // RCVR Trigger: 1 character in the FIFO
    FCR_RX_TRIG_QF   = BIT(6),   // RCVR Trigger: FIFO 1/4 full
    FCR_RX_TRIG_HF   = BIT(7),   // RCVR Trigger: FIFO 1/2 full
    FCR_RX_TRIG_AF   = (BIT(7)|BIT(6)),  // RCVR Trigger: FIFO 2 less than full
    FCR_RX_TRIG_MASK = (BIT(7)|BIT(6))   // RCVR Trigger bits Mask
} LOG_UART_FIFO_CTRL;

typedef struct _HAL_LOG_UART_ADAPTER_ {
    uint32_t BaudRate;		//00
    uint32_t FIFOControl;	//+04
    uint32_t IntEnReg;		//+08
    uint8_t Parity;			//+0c
    uint8_t Stop;			//+0d
    uint8_t DataLength;		//+0e

    uint8_t LineStatus;		//+0f
    volatile uint32_t TxCount;   //+10 how many byte to TX
    volatile uint32_t RxCount;   //+14 how many bytes to RX
    volatile uint8_t *pTxBuf;	//+18
    volatile uint8_t *pRxBuf;	//+1c
    uint8_t *pTxStartAddr;		//+20
    uint8_t *pRxStartAddr;		//+24

    IRQ_HANDLE IrqHandle;	//+28
    void (*LineStatusCallback)(void *para, uint8_t status);    //+38 User Line Status interrupt callback
    void (*TxCompCallback)(void *para);    //+3c User Tx complete callback
    void (*RxCompCallback)(void *para);    //+40 User Rx complete callback
    void *LineStatusCbPara; //+44 the argument for LineStatusCallback
    void *TxCompCbPara; //+48 the argument for TxCompCallback
    void *RxCompCbPara; //+4c the argument for RxCompCallback

    void (*api_irq_handler)(uint32_t id, LOG_UART_INT_ID event);	//+0x50
    uint32_t api_irq_id;	//+0x54
}HAL_LOG_UART_ADAPTER, *PHAL_LOG_UART_ADAPTER;

void HalLogUartIrqHandle(void * Data);
void HalLogUartSetBaudRate(HAL_LOG_UART_ADAPTER *pUartAdapter);
void HalLogUartSetLineCtrl(HAL_LOG_UART_ADAPTER *pUartAdapter);
void HalLogUartSetIntEn(HAL_LOG_UART_ADAPTER *pUartAdapter);
uint32_t HalLogUartInitSetting(HAL_LOG_UART_ADAPTER *pUartAdapter);
uint32_t HalLogUartRecv(HAL_LOG_UART_ADAPTER *pUartAdapter,
                    uint8_t  *pRxData, uint32_t Length, uint32_t TimeoutMS);
uint32_t HalLogUartSend(HAL_LOG_UART_ADAPTER *pUartAdapter,
        uint8_t *pTxData, uint32_t Length, uint32_t TimeoutMS);
HAL_Status HalLogUartIntSend(HAL_LOG_UART_ADAPTER *pUartAdapter,
        uint8_t *pTxData, uint32_t Length);
HAL_Status HalLogUartIntRecv(HAL_LOG_UART_ADAPTER *pUartAdapter,
        uint8_t  *pRxData, uint32_t Length);
void HalLogUartAbortIntSend(HAL_LOG_UART_ADAPTER *pUartAdapter);
void HalLogUartAbortIntRecv(HAL_LOG_UART_ADAPTER *pUartAdapter);
HAL_Status HalLogUartRstFIFO(HAL_LOG_UART_ADAPTER *pUartAdapter, uint8_t RstCtrl);
void HalLogUartEnable(HAL_LOG_UART_ADAPTER *pUartAdapter);
void HalLogUartDisable(HAL_LOG_UART_ADAPTER *pUartAdapter);
void HalLogUartWaitTxFifoEmpty(void);

#endif
