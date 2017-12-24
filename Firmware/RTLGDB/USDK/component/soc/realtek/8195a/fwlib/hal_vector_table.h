/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */


#ifndef _HAL_VECTOR_TABLE_H_
#define _HAL_VECTOR_TABLE_H_




extern _LONG_CALL_ROM_ void
VectorTableInitRtl8195A(
    IN  uint32_t StackP
);

extern _LONG_CALL_ROM_ void
VectorTableInitForOSRtl8195A(
    IN  void *PortSVC,
    IN  void *PortPendSVH,
    IN  void *PortSysTick    
);

extern _LONG_CALL_ROM_ BOOL
VectorIrqRegisterRtl8195A(
    IN  PIRQ_HANDLE pIrqHandle
);

extern _LONG_CALL_ROM_ BOOL
VectorIrqUnRegisterRtl8195A(
    IN  PIRQ_HANDLE pIrqHandle
);


extern _LONG_CALL_ROM_ void
VectorIrqEnRtl8195A(
    IN  PIRQ_HANDLE pIrqHandle
);

extern _LONG_CALL_ROM_ void
VectorIrqDisRtl8195A(
    IN  PIRQ_HANDLE pIrqHandle
);

 
extern _LONG_CALL_ROM_ void
HalPeripheralIntrHandle(void);
#endif //_HAL_VECTOR_TABLE_H_
