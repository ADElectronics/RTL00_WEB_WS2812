/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *                                        
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef __OSDEP_API_H_
#define __OSDEP_API_H_

#include "os_timer.h"
#include "os_support.h"
#include "osdep_service.h"


#define MAX_SEMA_COUNT                      32	/* the maximum count of a semaphore */

typedef _sema					_Sema;
typedef _mutex					_Mutex;
typedef	uint32_t						_Lock;
typedef struct TIMER_LIST		_Timer;
typedef unsigned long			_IRQL;
typedef _thread_hdl_			_THREAD_HDL_;
typedef void					THREAD_RETURN;
typedef void					THREAD_CONTEXT;


#ifndef mdelay
#define mdelay(t)					((t/portTICK_RATE_MS)>0)?(vTaskDelay(t/portTICK_RATE_MS)):(vTaskDelay(1))
#endif

#ifndef udelay
#define udelay(t)					((t/(portTICK_RATE_MS*1000))>0)?vTaskDelay(t/(portTICK_RATE_MS*1000)):(vTaskDelay(1))
#endif

/* to delete/start/stop a timer it will send a message to the timer task through a message queue,
    so we define the max wait time for message sending */
#define RTL_TIMER_API_MAX_BLOCK_TIME    1000    // unit is ms
#define RTL_TIMER_API_MAX_BLOCK_TICKS   (RTL_TIMER_API_MAX_BLOCK_TIME/portTICK_RATE_MS)

typedef void (*RTL_TIMER_CALL_BACK)(void    *pContext);

typedef struct _RTL_TIMER{
#ifdef PLATFORM_FREERTOS
    _timerHandle        TimerHandle;	// The timer handle of created FreeRTOS soft-timer
#endif    
	RTL_TIMER_CALL_BACK	CallBackFunc;	// Callback function of this timer
	uint32_t                 msPeriod;		// The period of this timer
	void                *Context;		// Timer specific context.
	uint8_t                  isPeriodical;	// Is a periodical timer
	uint8_t                  TimerName[35];	// The Name of timer
}RTL_TIMER, *PRTL_TIMER;

__inline static void RtlEnterCritical(void)
{
	rtw_enter_critical(NULL, NULL);
}

__inline static void RtlExitCritical(void)
{
	rtw_exit_critical(NULL, NULL);
}

__inline static void RtlEnterCriticalBh(IN  _Lock *plock, IN  _IRQL *pirqL)
{
	rtw_enter_critical_bh((_lock *)plock, pirqL);
}

__inline static void RtlExitCriticalBh(IN  _Lock *plock, IN  _IRQL *pirqL)
{
	rtw_exit_critical_bh((_lock *)plock, pirqL);
}

__inline static uint32_t RtlEnterCriticalMutex(IN  _Mutex *pmutex, IN  _IRQL *pirqL)
{
	return rtw_enter_critical_mutex(pmutex, pirqL);
}

__inline static void RtlExitCriticalMutex(IN  _Mutex *pmutex,IN  _IRQL *pirqL)
{
    rtw_exit_critical_mutex(pmutex, pirqL);
}

__inline static void RtlInitTimer(
    IN  _Timer *ptimer,
    IN  void *Data,
    IN  void (*pfunc)(void *),
    IN  void* cntx
)
{
	ptimer->Function = pfunc;
	ptimer->Data = (unsigned long)cntx;
	InitTimer(ptimer);
}

__inline static void RtlSetTimer(
    IN  _Timer *ptimer,
    IN  uint32_t delay_time
)
{	
	ModTimer(ptimer , (JIFFIES+(delay_time*RTL_HZ/1000)));	
}

__inline static void RtlCancelTimer(
    IN  _Timer *ptimer,
    IN  uint8_t *bcancelled
)
{
	DelTimerSync(ptimer); 	
	*bcancelled=  _TRUE;//TRUE ==1; FALSE==0
}

__inline static uint32_t RtlSystime2Ms(IN  uint32_t systime)
{
	return rtw_systime_to_ms(systime);
}

__inline static uint32_t RtlMs2Systime(IN  uint32_t ms)
{
	return rtw_ms_to_systime(ms);
}

extern uint8_t*	RtlZmalloc(uint32_t sz);
extern uint8_t*	RtlMalloc(uint32_t sz);
extern void	RtlMfree(uint8_t *pbuf, uint32_t sz);

extern void* RtlMalloc2d(uint32_t h, uint32_t w, uint32_t size);
extern void	RtlMfree2d(void *pbuf, uint32_t h, uint32_t w, uint32_t size);

extern void	RtlInitSema(_Sema *sema, uint32_t init_val);
extern void	RtlFreeSema(_Sema	*sema);
extern void	RtlUpSema(_Sema	*sema);
extern void	RtlUpSemaFromISR(_Sema	*sema);
extern uint32_t	RtlDownSema(_Sema *sema);
extern uint32_t	RtlDownSemaWithTimeout(_Sema *sema, uint32_t ms);

extern void	RtlMutexInit(_Mutex *pmutex);
extern void	RtlMutexFree(_Mutex *pmutex);

extern void	RtlSpinlockInit(_Lock *plock);
extern void	RtlSpinlockFree(_Lock *plock);
extern void	RtlSpinlock(_Lock	*plock);
extern void	RtlSpinunlock(_Lock	*plock);
extern void	RtlSpinlockEx(_Lock	*plock);
extern void	RtlSpinunlockEx(_Lock	*plock);

extern void	RtlSleepSchedulable(uint32_t ms);

extern void	RtlMsleepOS(uint32_t ms);
extern void	RtlUsleepOS(uint32_t us);
extern void RtlMdelayOS(uint32_t ms);
extern void RtlUdelayOS(uint32_t us);
extern void RtlYieldOS(void);

#define RtlUpMutex(mutex)		RtlUpSema(mutex)
#define RtlDownMutex(mutex)		RtlDownSema(mutex)

__inline static uint8_t RtlCancelTimerEx(IN  _Timer *ptimer)
{
	DelTimerSync(ptimer);
	return 0; 
}


static __inline void ThreadEnter(IN  char *name)
{
	DBG_8195A("\rRTKTHREAD_enter %s\n", name);
}

#define ThreadExit() do{DBG_8195A("\rRTKTHREAD_exit %s\n", __FUNCTION__);}while(0)

__inline static void FlushSignalsThread(void) 
{
}


#define RTL_RND(sz, r) ((((sz)+((r)-1))/(r))*(r))
#define RTL_RND4(x)	(((x >> 2) + (((x & 3) == 0) ?  0: 1)) << 2)

__inline static uint32_t RtlRnd4(IN  uint32_t sz)
{

	uint32_t	val;

	val = ((sz >> 2) + ((sz & 3) ? 1: 0)) << 2;
	
	return val;

}

__inline static uint32_t RtlRnd8(IN  uint32_t sz)
{

	uint32_t	val;

	val = ((sz >> 3) + ((sz & 7) ? 1: 0)) << 3;
	
	return val;

}

__inline static uint32_t RtlRnd128(IN  uint32_t sz)
{

	uint32_t	val;

	val = ((sz >> 7) + ((sz & 127) ? 1: 0)) << 7;
	
	return val;

}

__inline static uint32_t RtlRnd256(IN  uint32_t sz)
{

	uint32_t	val;

	val = ((sz >> 8) + ((sz & 255) ? 1: 0)) << 8;
	
	return val;

}

__inline static uint32_t RtlRnd512(IN  uint32_t sz)
{

	uint32_t	val;

	val = ((sz >> 9) + ((sz & 511) ? 1: 0)) << 9;
	
	return val;

}

__inline static uint32_t BitShift(IN  uint32_t BitMask)
{
	uint32_t i;

	for (i = 0; i <= 31; i++)
		if (((BitMask>>i) &  0x1) == 1) break;

	return i;
}


//#ifdef __GNUC__
#ifdef PLATFORM_LINUX
#define STRUCT_PACKED __attribute__ ((packed))
#else
#define STRUCT_PACKED
#endif


//Atomic integer operations
#define RTL_ATOMIC_T atomic_t

static inline void RTL_ATOMIC_SET(IN  RTL_ATOMIC_T *v, IN  uint32_t i)
{
	ATOMIC_SET(v,i);
}

static inline uint32_t RTL_ATOMIC_READ(IN  RTL_ATOMIC_T *v)
{
	return ATOMIC_READ(v);
}

static inline void RTL_ATOMIC_ADD(IN  RTL_ATOMIC_T *v, IN  uint32_t i)
{
	ATOMIC_ADD(v,i);
}

static inline void RTL_ATOMIC_SUB(IN  RTL_ATOMIC_T *v, IN  uint32_t i)
{
	ATOMIC_SUB(v,i);
}

static inline void RTL_ATOMIC_INC(IN  RTL_ATOMIC_T *v)
{
	ATOMIC_INC(v);
}

static inline void RTL_ATOMIC_DEC(IN  RTL_ATOMIC_T *v)
{
	ATOMIC_DEC(v);
}

static inline uint32_t RTL_ATOMIC_ADD_RETURN(IN  RTL_ATOMIC_T *v, IN  uint32_t i)
{
	return ATOMIC_ADD_RETURN(v, i);
}

static inline uint32_t RTL_ATOMIC_SUB_RETURN(IN  RTL_ATOMIC_T *v, IN  uint32_t i)
{
	return ATOMIC_SUB_RETURN(v, i);
}

static inline uint32_t RTL_ATOMIC_INC_RETURN(IN  RTL_ATOMIC_T *v)
{
	return ATOMIC_INC_RETURN(v);
}

static inline uint32_t RTL_ATOMIC_DEC_RETURN(IN  RTL_ATOMIC_T *v)
{
	return ATOMIC_DEC_RETURN(v);
}

extern uint64_t RtlModular64(uint64_t x, uint64_t y);

extern PRTL_TIMER
RtlTimerCreate(
    IN char *pTimerName,
    IN uint32_t TimerPeriodMS,
    IN RTL_TIMER_CALL_BACK CallbckFunc,
    IN void *pContext,
    IN uint8_t isPeriodical
);

extern void
RtlTimerDelete(
    IN PRTL_TIMER pTimerHdl
);

extern uint8_t
RtlTimerStart(
    IN PRTL_TIMER pTimerHdl,
    IN uint8_t isFromISR
);

extern uint8_t
RtlTimerStop(
    IN PRTL_TIMER pTimerHdl,
    IN uint8_t isFromISR
);

extern uint8_t
RtlTimerReset(
    IN PRTL_TIMER pTimerHdl,
    IN uint8_t isFromISR
);

extern uint8_t
RtlTimerChangePeriod(
    IN PRTL_TIMER pTimerHdl,
    IN uint32_t NewPeriodMS,
    IN uint8_t isFromISR
);

#endif	//#ifndef __OSDEP_API_H_


