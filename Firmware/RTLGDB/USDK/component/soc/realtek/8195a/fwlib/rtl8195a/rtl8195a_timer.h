/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _RTL8195A_TIMER_H_
#define _RTL8195A_TIMER_H_


#define TIMER_TICK_US               31

#define TIMER_LOAD_COUNT_OFF        0x00
#define TIMER_CURRENT_VAL_OFF       0x04
#define TIMER_CTL_REG_OFF           0x08
#define TIMER_EOI_OFF               0x0c
#define TIMER_INT_STATUS_OFF        0x10
#define TIMER_INTERVAL              0x14
#define TIMERS_INT_STATUS_OFF       0xa0
#define TIMERS_EOI_OFF              0xa4
#define TIMERS_RAW_INT_STATUS_OFF   0xa8
#define TIMERS_COMP_VER_OFF         0xac

#define MAX_TIMER_VECTOR_TABLE_NUM                  6

#define HAL_TIMER_READ32(addr)            (*((volatile uint32_t*)(TIMER_REG_BASE + addr)))//HAL_READ32(TIMER_REG_BASE, addr)
#define HAL_TIMER_WRITE32(addr, value)    ((*((volatile uint32_t*)(TIMER_REG_BASE + addr))) = value)//HAL_WRITE32(TIMER_REG_BASE, addr, value)
#define HAL_TIMER_READ16(addr)            (*((volatile uint16_t*)(TIMER_REG_BASE + addr)))//HAL_READ16(TIMER_REG_BASE, addr)
#define HAL_TIMER_WRITE16(addr, value)    ((*((volatile uint16_t*)(TIMER_REG_BASE + addr))) = value)//HAL_WRITE16(TIMER_REG_BASE, addr, value)
#define HAL_TIMER_READ8(addr)             (*((volatile uint8_t*)(TIMER_REG_BASE + addr)))//HAL_READ8(TIMER_REG_BASE, addr)
#define HAL_TIMER_WRITE8(addr, value)     ((*((volatile uint8_t*)(TIMER_REG_BASE + addr))) = value)//HAL_WRITE8(TIMER_REG_BASE, addr, value)

_LONG_CALL_ uint32_t
HalGetTimerIdRtl8195a(
    IN  uint32_t     *TimerID
);

_LONG_CALL_ BOOL
HalTimerInitRtl8195a(
    IN  void    *Data
);

_LONG_CALL_ uint32_t
HalTimerReadCountRtl8195a(
    IN  uint32_t     TimerId
);

_LONG_CALL_ void
HalTimerIrqClearRtl8195a(
    IN  uint32_t TimerId
);

_LONG_CALL_ void
HalTimerDisRtl8195a(
    IN  uint32_t TimerId
);

_LONG_CALL_ void
HalTimerEnRtl8195a(
    IN  uint32_t TimerId
);

_LONG_CALL_ void
HalTimerDumpRegRtl8195a(
    IN  uint32_t TimerId
);

// ROM Code patch
HAL_Status
HalTimerInitRtl8195a_Patch(
    IN  void    *Data
);

uint32_t
HalTimerReadCountRtl8195a_Patch(
    IN  uint32_t TimerId
);

void
HalTimerReLoadRtl8195a_Patch(
    IN  uint32_t TimerId,
    IN  uint32_t LoadUs
);

uint32_t
HalTimerReadCountRtl8195a_Patch(
    IN  uint32_t TimerId
);

void
HalTimerIrqEnRtl8195a(
    IN  uint32_t TimerId
);

void
HalTimerIrqDisRtl8195a(
    IN  uint32_t TimerId
);

void
HalTimerClearIsrRtl8195a(
    IN  uint32_t TimerId
);

void
HalTimerEnRtl8195a_Patch(
    IN  uint32_t TimerId
);

void
HalTimerDisRtl8195a_Patch(
    IN  uint32_t TimerId
);

void
HalTimerDeInitRtl8195a_Patch(
    IN  void    *Data
);

#if defined(CONFIG_CHIP_C_CUT) || defined(CONFIG_CHIP_E_CUT)

__weak _LONG_CALL_
void
HalTimerIrq2To7HandleV02(
    IN  void    *Data
);

__weak _LONG_CALL_ROM_
HAL_Status
HalTimerIrqRegisterRtl8195aV02(
    IN  void    *Data
);

__weak _LONG_CALL_
HAL_Status
HalTimerInitRtl8195aV02(
    IN  void    *Data
);

__weak _LONG_CALL_
uint32_t
HalTimerReadCountRtl8195aV02(
    IN  uint32_t TimerId
);

__weak _LONG_CALL_
void
HalTimerReLoadRtl8195aV02(
    IN  uint32_t TimerId,
    IN  uint32_t LoadUs
);

__weak _LONG_CALL_ROM_
HAL_Status
HalTimerIrqUnRegisterRtl8195aV02(
    IN  void    *Data
);

__weak _LONG_CALL_
void
HalTimerDeInitRtl8195aV02(
    IN  void    *Data
);

#endif  // end of "#ifdef CONFIG_CHIP_C_CUT"

#ifdef CONFIG_CHIP_E_CUT
_LONG_CALL_ void
HalTimerReLoadRtl8195a_V04(
    IN  uint32_t TimerId,
    IN  uint32_t LoadUs
);

_LONG_CALL_ HAL_Status
HalTimerInitRtl8195a_V04(
    IN  void    *Data
);
#endif  // #ifdef CONFIG_CHIP_E_CUT

// HAL functions wrapper
#ifndef CONFIG_RELEASE_BUILD_LIBRARIES
static __inline HAL_Status
HalTimerInit(
    IN  void    *Data
)
{
#ifdef CONFIG_CHIP_E_CUT
    return (HalTimerInitRtl8195a_V04(Data));
#else
    return (HalTimerInitRtl8195a_Patch(Data));
#endif
}

static __inline void
HalTimerEnable(
    IN  uint32_t TimerId
)
{
    HalTimerIrqEnRtl8195a(TimerId);
    HalTimerEnRtl8195a_Patch(TimerId);
}

static __inline void
HalTimerDisable(
    IN  uint32_t TimerId
)
{
    HalTimerDisRtl8195a_Patch(TimerId);
}

static __inline void
HalTimerClearIsr(
    IN  uint32_t TimerId
)
{
    HalTimerClearIsrRtl8195a(TimerId);
}

static __inline void
HalTimerReLoad(
    IN  uint32_t TimerId,
    IN  uint32_t LoadUs
)
{
#ifdef CONFIG_CHIP_E_CUT
    HalTimerReLoadRtl8195a_V04(TimerId, LoadUs);
#else
    HalTimerReLoadRtl8195a_Patch(TimerId, LoadUs);
#endif
}

#if defined(CONFIG_CHIP_A_CUT) || defined(CONFIG_CHIP_B_CUT)

static __inline void
HalTimerDeInit(
    IN  void    *Data
)
{
    HalTimerDeInitRtl8195a_Patch(Data);
}

#else

static __inline void
HalTimerDeInit(
    IN  void    *Data
)
{
    HalTimerDeInitRtl8195aV02(Data);
}

#endif      // end of "#ifndef CONFIG_CHIP_C_CUT"
#endif  // #ifndef CONFIG_RELEASE_BUILD_LIBRARIES
#endif //_RTL8195A_TIMER_H_
