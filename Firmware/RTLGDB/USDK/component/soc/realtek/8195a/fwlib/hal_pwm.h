/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _HAL_PWM_H_
#define _HAL_PWM_H_

#include "basic_types.h"

#define MAX_PWM_CTRL_PIN        4
// the minimum tick time for G-timer is 61 us (clock source = 32768Hz, reload value=1 and reload takes extra 1T)
//#define GTIMER_TICK_US            31   // micro-second, 1000000/32768 ~= 30.5
#define MIN_GTIMER_TIMEOUT    61  // in micro-sec, use this value to set the g-timer to generate tick for PWM. 61=(1000000/32768)*2
#define PWM_GTIMER_TICK_TIME    61  // in micro-sec, use this value to set the g-timer to generate tick for PWM. 61=(1000000/32768)*2

typedef struct _HAL_PWM_ADAPTER_ {
    uint8_t pwm_id;      // the PWM ID, 0~3
    uint8_t sel;         // PWM Pin selection, 0~3
    uint8_t gtimer_id;   // using G-Timer ID, there are 7 G-timer, but we prefer to use timer 3~6
    uint8_t enable;      // is enabled
//    uint32_t timer_value;    // the G-Timer auto-reload value, source clock is 32768Hz, reload will takes extra 1 tick. To set the time of a tick of PWM
    uint32_t tick_time;  // the tick time for the G-timer
    uint32_t period;    // the period of a PWM control cycle, in PWM tick
    uint32_t pulsewidth;    // the pulse width in a period of a PWM control cycle, in PWM tick. To control the ratio
//    float duty_ratio;   // the dyty ratio = pulswidth/period
}HAL_PWM_ADAPTER, *PHAL_PWM_ADAPTER;


extern HAL_Status 
HAL_Pwm_Init(
    HAL_PWM_ADAPTER *pPwmAdapt,
    uint32_t pwm_id,
    uint32_t sel
);

extern void 
HAL_Pwm_Enable(
    HAL_PWM_ADAPTER *pPwmAdapt
);

extern void 
HAL_Pwm_Disable(
    HAL_PWM_ADAPTER *pPwmAdapt
);

extern void
HAL_Pwm_SetDuty(
    HAL_PWM_ADAPTER *pPwmAdapt,
    uint32_t period,
    uint32_t pulse_width
);


#endif

