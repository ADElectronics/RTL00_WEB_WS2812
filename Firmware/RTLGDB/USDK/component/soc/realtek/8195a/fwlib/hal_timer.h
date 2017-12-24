/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _HAL_TIMER_H_
#define _HAL_TIMER_H_
#include "basic_types.h"
#include "hal_platform.h"
#include "rtl8195a_timer.h"

#define GTIMER_CLK_HZ           (32768)
#define GTIMER_TICK_US          (1000000/GTIMER_CLK_HZ)

typedef enum _TIMER_MODE_ {
    FREE_RUN_MODE = 0,
    USER_DEFINED = 1
}TIMER_MODE, *PTIMER_MODE;


typedef struct _TIMER_ADAPTER_ {

    uint32_t         TimerLoadValueUs;	//+00
    uint32_t         TimerIrqPriority;	//+04
    TIMER_MODE  TimerMode;			//+08
    IRQ_HANDLE  IrqHandle;			//+0c
    uint8_t          TimerId;			//+1c?
    uint8_t          IrqDis;				//+1d?

}TIMER_ADAPTER, *PTIMER_ADAPTER;


typedef struct _HAL_TIMER_OP_ {
    uint32_t  (*HalGetTimerId)(uint32_t *TimerId);	//+00
    BOOL (*HalTimerInit)(void *Data);		//+04
    uint32_t  (*HalTimerReadCount)(uint32_t TimerId);	//+08
    void (*HalTimerIrqClear)(uint32_t TimerId);	//+0c
    void (*HalTimerDis)(uint32_t TimerId);		//+10
    void (*HalTimerEn)(uint32_t TimerId);		//+14
    void (*HalTimerDumpReg)(uint32_t TimerId);	//+18
}HAL_TIMER_OP, *PHAL_TIMER_OP;

#ifdef CONFIG_TIMER_MODULE
// This variable declared in ROM code
extern HAL_TIMER_OP HalTimerOp;
#endif

void HalTimerOpInit_Patch(
    IN  void *Data
);


//======================================================
// ROM Function prototype
_LONG_CALL_ void HalTimerOpInitV02(IN  void *Data);

#ifndef CONFIG_RELEASE_BUILD_LIBRARIES
#define HalTimerOpInit      HalTimerOpInit_Patch
#endif

#ifdef CONFIG_RELEASE_BUILD_LIBRARIES
void HalTimerOpInit(
    void *Data
);

HAL_Status
HalTimerInit(
    void *Data
);

void
HalTimerEnable(
    uint32_t TimerId
);

void
HalTimerDisable(
    uint32_t TimerId
);

void
HalTimerReLoad(
    uint32_t TimerId,
    uint32_t LoadUs
);

void
HalTimerDeInit(
    void *Data
);
#endif  // #ifdef CONFIG_RELEASE_BUILD_LIBRARIES
#endif
