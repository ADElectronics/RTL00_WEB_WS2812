/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
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


#define _OSDEP_API_C_

#include <osdep_api.h>
#include "osdep_service.h"

extern _LONG_CALL_ char *_strcpy(char *dest, const char *src);
extern _LONG_CALL_ void *_memset(void *dst0, int Val,SIZE_T length);

uint8_t* RtlMalloc(IN  uint32_t sz)
{
	uint8_t 	*pbuf=NULL;

	pbuf = rtw_malloc((uint32_t)sz);

	return pbuf;		
}


uint8_t* RtlZmalloc(IN  uint32_t sz)
{
    uint8_t  *pbuf;
 
    pbuf= rtw_malloc((uint32_t)sz);

    if (pbuf != NULL) {
        _memset(pbuf, 0, sz);
    }

    return pbuf;    
}

void RtlMfree(IN  uint8_t *pbuf, IN  uint32_t sz)
{
    rtw_mfree(pbuf, sz);	
}

void* RtlMalloc2d(IN  uint32_t h, IN  uint32_t w, IN  uint32_t size)
{
	//uint32_t j;

	void **a = (void **) rtw_malloc2d(h, w, size);
	if(a == NULL)
	{
		DBG_ERROR_LOG("%s: alloc memory fail!\n", __FUNCTION__);
		return NULL;
	}

	return a;
}

void RtlMfree2d(IN  void *pbuf, IN  uint32_t h, IN  uint32_t w, IN  uint32_t size)
{
	rtw_mfree2d(pbuf, h, w, size);
}

void RtlInitSema(IN  _Sema *sema, IN  uint32_t init_val)
{
	rtw_init_sema(sema, init_val);
}

void RtlFreeSema(IN  _Sema *sema)
{
	rtw_free_sema(sema);
}

void RtlUpSema(IN  _Sema *sema)
{
	rtw_up_sema(sema);
}

void RtlUpSemaFromISR(IN  _Sema *sema)
{
	rtw_up_sema_from_isr(sema);
}

uint32_t RtlDownSema(IN   _Sema *sema)
{
	rtw_down_sema(sema);
	return  _SUCCESS;
}

uint32_t RtlDownSemaWithTimeout(IN   _Sema *sema,IN   uint32_t ms)
{
	return rtw_down_timeout_sema(sema, ms);
}

void	RtlMutexInit(IN _Mutex *pmutex)
{
	rtw_mutex_init(pmutex);
}

void RtlMutexFree(IN _Mutex *pmutex)
{
	rtw_mutex_free(pmutex);
}

void RtlSpinlockInit(IN  _Lock *plock)
{
	rtw_spinlock_init((_lock *)plock);
}

void RtlSpinlockFree(IN  _Lock *plock)
{
	rtw_spinlock_free((_lock *)plock);
}

void RtlSpinlock(IN  _Lock *plock)
{
    rtw_spin_lock((_lock *)plock);
}

void RtlSpinunlock(IN  _Lock *plock)
{
	rtw_spin_unlock((_lock *)plock);
}

void RtlSpinlockEx(IN  _Lock *plock)
{
}

void RtlSpinunlockEx(IN  _Lock *plock)
{
}

uint32_t	 RtlGetCurrentTime(void)
{
    return rtw_get_current_time();
}

void RtlSleepSchedulable(IN  uint32_t ms) 
{
}

void RtlMsleepOS(IN uint32_t ms)
{
	rtw_msleep_os(ms);
}

void RtlUsleepOS(IN  uint32_t us)
{
	rtw_usleep_os(us);
}

void RtlMdelayOS(IN   uint32_t ms)
{
   	rtw_mdelay_os(ms); 
}

void RtlUdelayOS(IN  uint32_t us)
{
	rtw_udelay_os(us);
}

void RtlYieldOS(void)
{
	rtw_yield_os();
}


#if defined(__ICCARM__)
uint64_t RtlModular64(IN  uint64_t n, IN  uint64_t base)
{
	unsigned int __base = (base);	
	unsigned int __rem;	
	//(void)(((typeof((n)) *)0) == ((__uint64_t *)0));
	if (((n) >> 32) == 0) {	
		__rem = (unsigned int)(n) % __base;
		(n) = (unsigned int)(n) / __base;
	} else 					
		__rem = __Div64_32(&(n), __base);
	return __rem;

}
#else
uint64_t RtlModular64(IN  uint64_t x, IN  uint64_t y)
{
	return rtw_modular64(x, y);
}
#endif

/******************************************************************************
 * Function: RtlTimerCallbckEntry
 * Desc: This function is a timer callback wrapper. All OS timer callback 
 *      will call this function and then call the real callback function inside
 *      this function.
 *
 * Para:
 * 	 pxTimer: The FreeRTOS timer handle which is expired and call this callback.
 *
 * Return: None
 *
 ******************************************************************************/
#ifdef PLATFORM_FREERTOS
void RtlTimerCallbckEntry (IN _timerHandle pxTimer)
{
    PRTL_TIMER pTimer;

    if (NULL == pxTimer) {
        MSG_TIMER_ERR("RtlTimerCallbckEntry: NULL Timer Handle Err!\n");
        return;
    }
    
    pTimer = (PRTL_TIMER) rtw_timerGetID( pxTimer );
    pTimer->CallBackFunc(pTimer->Context);
}
#endif  // end of "#ifdef PLATFORM_FREERTOS"

/******************************************************************************
 * Function: RtlTimerCreate
 * Desc: To create a software timer.
 *
 * Para:
 * 	 pTimerName: A string for the timer name.
 * 	 TimerPeriodMS: The timer period, the unit is milli-second.
 *   CallbckFunc: The callback function of this timer.
 *   pContext: A pointer will be used as the parameter to call the timer 
 *              callback function.
 *   isPeriodical: Is this timer periodical ? (Auto reload after expired)
 * Return: The created timer handle, a pointer. It can be used to delete the 
 *          timer. If timer createion failed, return NULL.
 *
 ******************************************************************************/
PRTL_TIMER RtlTimerCreate(
    IN char *pTimerName,
    IN uint32_t TimerPeriodMS,
    IN RTL_TIMER_CALL_BACK CallbckFunc,
    IN void *pContext,
    IN uint8_t isPeriodical)
{
    PRTL_TIMER pTimer;
    uint32_t timer_ticks;
    int i;

    pTimer = (PRTL_TIMER)RtlZmalloc(sizeof(RTL_TIMER));
    if (NULL == pTimer) {
        MSG_TIMER_ERR("RtlTimerCreate: Alloc Mem Err!\n");
        return NULL;
    }

    if (portTICK_RATE_MS >= TimerPeriodMS) {
        timer_ticks = 1;    // at least 1 system tick
    }
    else {
        timer_ticks = TimerPeriodMS/portTICK_RATE_MS;
    }

    pTimer->TimerHandle = rtw_timerCreate ((const char*)(pTimer->TimerName), timer_ticks, 
            (portBASE_TYPE)isPeriodical, (void *) pTimer, RtlTimerCallbckEntry);

#ifdef PLATFORM_FREERTOS    // if any RTOS is used
    if (pTimer->TimerHandle) {
        pTimer->msPeriod = TimerPeriodMS;
        pTimer->CallBackFunc = CallbckFunc;
        pTimer->Context = pContext;
        pTimer->isPeriodical = isPeriodical;
        // copy the timer name
        if (NULL != pTimerName) {
            for(i = 0; i < sizeof(pTimer->TimerName); i++)
            {
                pTimer->TimerName[i] = pTimerName[i]; 
                if(pTimerName[i] == '\0')
                {
                    break;
                }
            }
        }
        else {
            _strcpy((char*)(pTimer->TimerName), "None");
        }
        MSG_TIMER_INFO("RtlTimerCreate: SW Timer Created: Name=%s Period=%d isPeriodical=%d\n", \
            pTimer->TimerName, pTimer->msPeriod, pTimer->isPeriodical);
    }
    else 
#endif
    {
        RtlMfree((uint8_t *)pTimer, sizeof(RTL_TIMER));
        pTimer = NULL;
        MSG_TIMER_ERR("RtlTimerCreate: OS Create Timer Failed!\n");
    }

    return (pTimer);    
}

/******************************************************************************
 * Function: RtlTimerDelete
 * Desc: To delete a created software timer.
 *
 * Para:
 * 	 pTimerHdl: The timer to be deleted
 *
 * Return: None
 *
 ******************************************************************************/
void RtlTimerDelete(IN PRTL_TIMER pTimerHdl)
{
#ifdef PLATFORM_FREERTOS
    portBASE_TYPE ret;
#endif

    if (NULL == pTimerHdl) {
        MSG_TIMER_ERR("RtlTimerDelete: NULL Timer Handle!\n");
        return;
    }

    MSG_TIMER_INFO("RtlTimerDelete: Name=%s\n", pTimerHdl->TimerName);
#ifdef PLATFORM_FREERTOS
    /* try to delete the soft timer and wait max RTL_TIMER_API_MAX_BLOCK_TICKS 
        to send the delete command to the timer command queue */
	ret = rtw_timerDelete(pTimerHdl->TimerHandle, RTL_TIMER_API_MAX_BLOCK_TICKS);
    if (pdPASS != ret) {
        MSG_TIMER_ERR("RtlTimerDelete: Delete OS Timer Failed!\n");
    }
#endif    
    RtlMfree((uint8_t *)pTimerHdl, sizeof(RTL_TIMER));

}

/******************************************************************************
 * Function: RtlTimerStart
 * Desc: To start a created timer..
 *
 * Para:
 * 	 pTimerHdl: The timer to be started.
 *	isFromISR: The flag to indicate that is this function is called from an ISR.
 *
 * Return: _SUCCESS or _FAIL
 *
 ******************************************************************************/
uint8_t RtlTimerStart(IN PRTL_TIMER pTimerHdl, IN uint8_t isFromISR)
{
#ifdef PLATFORM_FREERTOS
    uint8_t ret=_FAIL;
    portBASE_TYPE HigherPriorityTaskWoken=pdFALSE;

    if (isFromISR) {
        if (pdPASS == rtw_timerStartFromISR(pTimerHdl->TimerHandle,&HigherPriorityTaskWoken))
        {
            // start OS timer successful
            if (pdFALSE != HigherPriorityTaskWoken) {
                rtw_yield_os();
            }
            ret = _SUCCESS;
        }
        else {
            MSG_TIMER_ERR("RtlTimerStart: Start Timer(%s) from ISR failed\n", pTimerHdl->TimerName);
        }
    }
    else {
        if (pdPASS == rtw_timerStart(pTimerHdl->TimerHandle, RTL_TIMER_API_MAX_BLOCK_TICKS)) {
            ret = _SUCCESS;
        }
        else {
            MSG_TIMER_ERR("RtlTimerStart: Start Timer(%s) failed\n", pTimerHdl->TimerName);
        }
    }

    MSG_TIMER_INFO("RtlTimerStart: SW Timer %s Started\n", pTimerHdl->TimerName);

    return ret;
#endif
}

/******************************************************************************
 * Function: RtlTimerStop
 * Desc: To stop a running timer..
 *
 * Para:
 * 	 pTimerHdl: The timer to be stoped.
 *	isFromISR: The flag to indicate that is this function is called from an ISR.
 *
 * Return: _SUCCESS or _FAIL
 *
 ******************************************************************************/
uint8_t RtlTimerStop(IN PRTL_TIMER pTimerHdl, IN uint8_t isFromISR)
{
#ifdef PLATFORM_FREERTOS
    uint8_t ret=_FAIL;
    portBASE_TYPE HigherPriorityTaskWoken=pdFALSE;

    if (isFromISR) {
        if (pdPASS == rtw_timerStopFromISR(pTimerHdl->TimerHandle,&HigherPriorityTaskWoken))
        {
            // start OS timer successful
            if (pdFALSE != HigherPriorityTaskWoken) {
                rtw_yield_os();
            }
            ret = _SUCCESS;
        }
    }
    else {
        if (pdPASS == rtw_timerStop(pTimerHdl->TimerHandle, RTL_TIMER_API_MAX_BLOCK_TICKS)) {
            ret = _SUCCESS;
        }
    }

    if (_FAIL == ret) {
        MSG_TIMER_ERR("RtlTimerStop: Stop Timer(%s) Failed, IsFromISR=%d\n", pTimerHdl->TimerName, isFromISR);
    }

    MSG_TIMER_INFO("RtlTimerStop: SW Timer %s Stoped\n", pTimerHdl->TimerName);

    return ret;
#endif
}

/******************************************************************************
 * Function: RtlTimerReset
 * Desc: To reset a timer. A reset will get a re-start and reset
 *          the timer ticks counting. A running timer expired time is relative 
 *          to the time when Reset function be called. Please ensure the timer
 *          is in active state (Started). A stopped timer also will be started
 *          when this function is called.
 *
 * Para:
 * 	 pTimerHdl: The timer to be reset.
 *	isFromISR: The flag to indicate that is this function is called from an ISR.
 *
 * Return: _SUCCESS or _FAIL
 *
 ******************************************************************************/
uint8_t
RtlTimerReset(
    IN PRTL_TIMER pTimerHdl,
    IN uint8_t isFromISR
)
{
#ifdef PLATFORM_FREERTOS
    uint8_t ret=_FAIL;
    portBASE_TYPE HigherPriorityTaskWoken=pdFALSE;

    if (isFromISR) {
        if (pdPASS == rtw_timerResetFromISR(pTimerHdl->TimerHandle,&HigherPriorityTaskWoken))
        {
            // start OS timer successful
            if (pdFALSE != HigherPriorityTaskWoken) {
                rtw_yield_os();
            }
            ret = _SUCCESS;
        }
    }
    else {
        if (pdPASS == rtw_timerReset(pTimerHdl->TimerHandle, RTL_TIMER_API_MAX_BLOCK_TICKS)) {
            ret = _SUCCESS;
        }
    }

    if (_FAIL == ret) {
        MSG_TIMER_ERR("RtlTimerReset: Reset Timer(%s) Failed, IsFromISR=%d\n", pTimerHdl->TimerName, isFromISR);
    }

    MSG_TIMER_INFO("RtlTimerReset: SW Timer %s Reset\n", pTimerHdl->TimerName);

    return ret;
#endif
}

/******************************************************************************
 * Function: RtlTimerChangePeriod
 * Desc: To change the period of a timer that was created previously.
 *
 * Para:
 * 	 pTimerHdl: The timer handle to be changed the priod.
 *   NewPeriodMS: The new timer period, in milli-second.
 *	 isFromISR: The flag to indicate that is this function is called from an ISR.
 *
 * Return: _SUCCESS or _FAIL
 *
 ******************************************************************************/
uint8_t RtlTimerChangePeriod(
    IN PRTL_TIMER pTimerHdl,
    IN uint32_t NewPeriodMS,
    IN uint8_t isFromISR)
{
#ifdef PLATFORM_FREERTOS
    uint32_t timer_ticks;
    uint8_t ret=_FAIL;
    portBASE_TYPE HigherPriorityTaskWoken=pdFALSE;

    if (portTICK_RATE_MS >= NewPeriodMS) {
        timer_ticks = 1;    // at least 1 system tick
    }
    else {
        timer_ticks = NewPeriodMS/portTICK_RATE_MS;
    }

    if (isFromISR) {
        if (pdPASS == rtw_timerChangePeriodFromISR(pTimerHdl->TimerHandle, timer_ticks, &HigherPriorityTaskWoken))
        {
            // start OS timer successful
            if (pdFALSE != HigherPriorityTaskWoken) {
                taskYIELD();
            }
            ret = _SUCCESS;
        }
    }
    else {
        if (pdPASS == rtw_timerChangePeriod(pTimerHdl->TimerHandle, timer_ticks, RTL_TIMER_API_MAX_BLOCK_TICKS)) {
            ret = _SUCCESS;
        }
    }

    if (_FAIL == ret) {
        MSG_TIMER_ERR("RtlTimerChangePeriod: Change Timer(%s) Period Failed, IsFromISR=%d\n", pTimerHdl->TimerName, isFromISR);
    }
    else {
        pTimerHdl->msPeriod = NewPeriodMS;
        MSG_TIMER_INFO("RtlTimerChangePeriod: SW Timer %s change period to %d\n", pTimerHdl->TimerName, pTimerHdl->msPeriod);
    }

    
    return ret;
#endif
}

