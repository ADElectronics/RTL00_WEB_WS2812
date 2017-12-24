/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */
#ifndef _HAL_API_H_
#define _HAL_API_H_

#include "basic_types.h"
#include "hal_irqn.h"

#define HAL_READ32(base, addr)            \
        rtk_le32_to_cpu(*((volatile uint32_t*)(base + addr)))
    
#define HAL_WRITE32(base, addr, value32)  \
        ((*((volatile uint32_t*)(base + addr))) = rtk_cpu_to_le32(value32))


#define HAL_READ16(base, addr)            \
        rtk_le16_to_cpu(*((volatile uint16_t*)(base + addr)))
        
#define HAL_WRITE16(base, addr, value)  \
        ((*((volatile uint16_t*)(base + addr))) = rtk_cpu_to_le16(value))
    

#define HAL_READ8(base, addr)            \
        (*((volatile uint8_t*)(base + addr)))
            
#define HAL_WRITE8(base, addr, value)  \
        ((*((volatile uint8_t*)(base + addr))) = value)

#if 0
// These "extern _LONG_CALL_" function declaration are for RAM code building only
// For ROM code building, thses code should be marked off
extern _LONG_CALL_ uint8_t 
HalPinCtrlRtl8195A(
    IN uint32_t  Function, 
    IN uint32_t  PinLocation, 
    IN BOOL   Operation
    );

extern _LONG_CALL_ void 
HalSerialPutcRtl8195a(
    IN  uint8_t c
    );

extern _LONG_CALL_ uint8_t 
HalSerialGetcRtl8195a(
    IN  BOOL    PullMode
    );

extern _LONG_CALL_ uint32_t
HalSerialGetIsrEnRegRtl8195a(void);

extern _LONG_CALL_ void
HalSerialSetIrqEnRegRtl8195a (
    IN  uint32_t SetValue
    );

extern _LONG_CALL_  void
VectorTableInitForOSRtl8195A(
    IN  void *PortSVC,
    IN  void *PortPendSVH,
    IN  void *PortSysTick    
    );

extern _LONG_CALL_ BOOL
VectorIrqRegisterRtl8195A(
    IN  PIRQ_HANDLE pIrqHandle
    );

extern _LONG_CALL_ BOOL
VectorIrqUnRegisterRtl8195A(
    IN  PIRQ_HANDLE pIrqHandle
    );

extern _LONG_CALL_ void
VectorIrqEnRtl8195A(
    IN  PIRQ_HANDLE pIrqHandle
    );

extern _LONG_CALL_  void
VectorIrqDisRtl8195A(
    IN  PIRQ_HANDLE pIrqHandle
    );
#endif

extern BOOLEAN SpicFlashInitRtl8195A(uint8_t SpicBitMode);
extern void InitWDGIRQ(void);

#define PinCtrl HalPinCtrlRtl8195A

#define DiagPutChar	HalSerialPutcRtl8195a
#define DiagGetChar HalSerialGetcRtl8195a
#define DiagGetIsrEnReg HalSerialGetIsrEnRegRtl8195a
#define DiagSetIsrEnReg HalSerialSetIrqEnRegRtl8195a

#define InterruptForOSInit VectorTableInitForOSRtl8195A
#define InterruptRegister VectorIrqRegisterRtl8195A
#define InterruptUnRegister  VectorIrqUnRegisterRtl8195A

#define InterruptEn VectorIrqEnRtl8195A
#define InterruptDis VectorIrqDisRtl8195A

#define SpicFlashInit SpicFlashInitRtl8195A
#define Calibration32k En32KCalibration
#define WDGInit InitWDGIRQ

typedef enum  _HAL_Status
{
  HAL_OK            = 0x00,
  HAL_BUSY          = 0x01,
  HAL_TIMEOUT       = 0x02,
  HAL_ERR_PARA      = 0x03,     // error with invaild parameters 
  HAL_ERR_MEM       = 0x04,     // error with memory allocation failed
  HAL_ERR_HW        = 0x05,     // error with hardware error

  HAL_ERR_UNKNOWN   = 0xee      // unknown error
  
} HAL_Status;


#endif //_HAL_API_H_
