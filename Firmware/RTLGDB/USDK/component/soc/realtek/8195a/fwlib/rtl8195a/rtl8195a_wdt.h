/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2014 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _RTL8195A_WDT_H_
#define _RTL8195A_WDT_H_

#define WDGTIMERELY  (10*1024)  //us

typedef struct _WDG_REG_ {
    uint16_t     WdgScalar;
    uint8_t      WdgEnByte;
    uint8_t      WdgClear:1;
    uint8_t      WdgCunLimit:4;
    uint8_t      Rsvd:1;
    uint8_t      WdgMode:1;
    uint8_t      WdgToISR:1;
}WDG_REG, *PWDG_REG;

typedef struct _WDG_ADAPTER_ {

    WDG_REG             Ctrl;
    IRQ_HANDLE          IrqHandle;
    TIMER_ADAPTER       WdgGTimer;
    void (*UserCallback)(uint32_t callback_id);    // User callback function
    uint32_t                 callback_id;
}WDG_ADAPTER, *PWDG_ADAPTER;

typedef enum _WDG_CNTLMT_ {
    CNT1H    = 0,
    CNT3H    = 1,
    CNT7H    = 2,
    CNTFH    = 3,
    CNT1FH   = 4,
    CNT3FH   = 5,
    CNT7FH   = 6,
    CNTFFH   = 7,
    CNT1FFH  = 8,
    CNT3FFH  = 9,
    CNT7FFH  = 10,
    CNTFFFH  = 11
}WDG_CNTLMT, *PWDG_CNTLMT;


typedef enum _WDG_MODE_ {
    INT_MODE    = 0,
    RESET_MODE  = 1
}WDG_MODE, *PWDG_MODE;

extern void
WDGInitial(
    IN  uint32_t Period
);

extern void
WDGIrqInitial(
    void
);

extern void
WDGIrqInitial(
    void
);

extern void
WDGStop(
    void
);

extern void
WDGRefresh(
    void
);

extern void
WDGIrqCallBackReg(
    IN void *CallBack,
    IN uint32_t   Id
);

#endif //_RTL8195A_WDT_H_
