/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "rtl8195a.h"
//#include <stdarg.h>
#include "rtl_consol.h"
#include "FreeRTOS.h"
#include "task.h"
#include <event_groups.h>
#include "semphr.h"
#if defined(configUSE_WAKELOCK_PMU) && (configUSE_WAKELOCK_PMU == 1)
#include "freertos_pmu.h"
#endif
#include "tcm_heap.h"

// Those symbols will be defined in linker script for gcc compiler
// If not doing this would cause extra memory cost
#if defined (__GNUC__)

    extern volatile UART_LOG_CTL    UartLogCtl;
    extern volatile UART_LOG_CTL    *pUartLogCtl;
    extern uint8_t                       *ArgvArray[MAX_ARGV];
    extern UART_LOG_BUF             UartLogBuf;

#ifdef CONFIG_UART_LOG_HISTORY
    extern uint8_t  UartLogHistoryBuf[UART_LOG_HISTORY_LEN][UART_LOG_CMD_BUFLEN];
#endif

#else

MON_RAM_BSS_SECTION 
    volatile UART_LOG_CTL    UartLogCtl;
MON_RAM_BSS_SECTION 
    volatile UART_LOG_CTL    *pUartLogCtl;
MON_RAM_BSS_SECTION 
    uint8_t                       *ArgvArray[MAX_ARGV];
MON_RAM_BSS_SECTION 
    UART_LOG_BUF             UartLogBuf;

#ifdef CONFIG_UART_LOG_HISTORY
MON_RAM_BSS_SECTION
    uint8_t  UartLogHistoryBuf[UART_LOG_HISTORY_LEN][UART_LOG_CMD_BUFLEN];
#endif

#endif

#ifdef CONFIG_KERNEL
static void (*up_sema_from_isr)(_sema *) = NULL;
#endif


_LONG_CALL_
extern uint8_t
UartLogCmdChk(
    IN  uint8_t  RevData,
    IN  UART_LOG_CTL    *prvUartLogCtl,
    IN  uint8_t  EchoFlag
);

_LONG_CALL_
extern void
ArrayInitialize(
    IN  uint8_t  *pArrayToInit,
    IN  uint8_t  ArrayLen,
    IN  uint8_t  InitValue
);

_LONG_CALL_
extern void
UartLogHistoryCmd(
    IN  uint8_t  RevData,
    IN  UART_LOG_CTL    *prvUartLogCtl,
    IN  uint8_t  EchoFlag
);

_LONG_CALL_
extern void
UartLogCmdExecute(
    IN  PUART_LOG_CTL   pUartLogCtlExe
);



//=================================================


/* Minimum and maximum values a `signed long int' can hold.
   (Same as `int').  */
#ifndef __LONG_MAX__
#if defined (__alpha__) || (defined (__sparc__) && defined(__arch64__)) || defined (__sparcv9) || defined (__s390x__)
#define __LONG_MAX__ 9223372036854775807L
#else
#define __LONG_MAX__ 2147483647L
#endif /* __alpha__ || sparc64 */
#endif
#undef LONG_MIN
#define LONG_MIN (-LONG_MAX-1)
#undef LONG_MAX
#define LONG_MAX __LONG_MAX__

/* Maximum value an `unsigned long int' can hold.  (Minimum is 0).  */
#undef ULONG_MAX
#define ULONG_MAX (LONG_MAX * 2UL + 1)

#ifndef __LONG_LONG_MAX__
#define __LONG_LONG_MAX__ 9223372036854775807LL
#endif




//======================================================
//<Function>:  UartLogIrqHandleRam
//<Usage   >:  To deal with Uart-Log RX IRQ
//<Argus    >:  void
//<Return   >:  void
//<Notes    >:  NA
//======================================================
//MON_RAM_TEXT_SECTION
void
UartLogIrqHandleRam
(
    void * Data
)
{
    uint8_t      UartReceiveData = 0;
    //For Test
    BOOL    PullMode = _FALSE;

    uint32_t IrqEn = DiagGetIsrEnReg();

    DiagSetIsrEnReg(0);

    UartReceiveData = DiagGetChar(PullMode);
    if (UartReceiveData == 0) {
        goto exit;
    }

    //KB_ESC chk is for cmd history, it's a special case here.
    if (UartReceiveData == KB_ASCII_ESC) {
        //4 Esc detection is only valid in the first stage of boot sequence (few seconds)
        if (pUartLogCtl->ExecuteEsc != _TRUE)
        {
            pUartLogCtl->ExecuteEsc = _TRUE;
            (*pUartLogCtl).EscSTS = 0;
        }
        else
        {
            //4 the input commands are valid only when the task is ready to execute commands
            if ((pUartLogCtl->BootRdy == 1)
#ifdef CONFIG_KERNEL
                ||(pUartLogCtl->TaskRdy == 1)
#endif
            )
            {
                if ((*pUartLogCtl).EscSTS==0)
                {
                    (*pUartLogCtl).EscSTS = 1;
                }
            }
            else
            {
                (*pUartLogCtl).EscSTS = 0;
            }
        }
    }
    else if ((*pUartLogCtl).EscSTS==1){
        if (UartReceiveData != KB_ASCII_LBRKT){
            (*pUartLogCtl).EscSTS = 0;
        }
        else{
            (*pUartLogCtl).EscSTS = 2;
        }
    }

    else{
        if ((*pUartLogCtl).EscSTS==2){
            (*pUartLogCtl).EscSTS = 0;
#ifdef CONFIG_UART_LOG_HISTORY
            if ((UartReceiveData=='A')|| UartReceiveData=='B'){
                UartLogHistoryCmd(UartReceiveData,(UART_LOG_CTL *)pUartLogCtl,1);
            }
#endif
        }
        else{
            if (UartLogCmdChk(UartReceiveData,(UART_LOG_CTL *)pUartLogCtl,1)==2)
            {
                //4 check UartLog buffer to prevent from incorrect access
                if (pUartLogCtl->pTmpLogBuf != NULL)
                {
                    pUartLogCtl->ExecuteCmd = _TRUE;
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
    				if (pUartLogCtl->TaskRdy && up_sema_from_isr != NULL)
    					//RtlUpSemaFromISR((_Sema *)&pUartLogCtl->Sema);				
						up_sema_from_isr((_sema *)&pUartLogCtl->Sema);
#endif
                }
                else
                {
                    ArrayInitialize((uint8_t *)pUartLogCtl->pTmpLogBuf->UARTLogBuf, UART_LOG_CMD_BUFLEN, '\0');
                }
            }
        }
    }
exit:
    DiagSetIsrEnReg(IrqEn);

}



//MON_RAM_TEXT_SECTION
void
RtlConsolInitRam(
    IN  uint32_t     Boot,
    IN  uint32_t     TBLSz,
    IN  void    *pTBL
)
{
    UartLogBuf.BufCount = 0;
    ArrayInitialize(&UartLogBuf.UARTLogBuf[0],UART_LOG_CMD_BUFLEN,'\0');
    pUartLogCtl = &UartLogCtl;

    pUartLogCtl->NewIdx = 0;
    pUartLogCtl->SeeIdx = 0;
    pUartLogCtl->RevdNo = 0;
    pUartLogCtl->EscSTS = 0;
    pUartLogCtl->BootRdy = 0;
    pUartLogCtl->pTmpLogBuf = &UartLogBuf;
#ifdef CONFIG_UART_LOG_HISTORY
    pUartLogCtl->CRSTS = 0;
    pUartLogCtl->pHistoryBuf = &UartLogHistoryBuf[0];
#endif
    pUartLogCtl->pfINPUT = (void*)&DiagPrintf;
    pUartLogCtl->pCmdTbl = (PCOMMAND_TABLE) pTBL;
    pUartLogCtl->CmdTblSz = TBLSz;
#ifdef CONFIG_KERNEL
    pUartLogCtl->TaskRdy = 0;
#endif
    //executing boot sequence
    if (Boot == ROM_STAGE)
    {
        pUartLogCtl->ExecuteCmd = _FALSE;
        pUartLogCtl->ExecuteEsc = _FALSE;
    }
    else
    {
        pUartLogCtl->ExecuteCmd = _FALSE;
        pUartLogCtl->ExecuteEsc= _TRUE;//don't check Esc anymore
#if defined(CONFIG_KERNEL)
        /* Create a Semaphone */
        //RtlInitSema((_Sema*)&(pUartLogCtl->Sema), 0);
        rtw_init_sema((_sema*)&(pUartLogCtl->Sema), 0);
        pUartLogCtl->TaskRdy = 0;
#ifdef PLATFORM_FREERTOS
#define	LOGUART_STACK_SIZE	128 //USE_MIN_STACK_SIZE modify from 512 to 128
#if CONFIG_USE_TCM_HEAP
	{
		int ret = 0;
		void *stack_addr = tcm_heap_malloc(LOGUART_STACK_SIZE*sizeof(int));
		//void *stack_addr = rtw_malloc(stack_size*sizeof(int));
		if(stack_addr == NULL){
			DiagPrintf("Out of TCM heap in \"LOGUART_TASK\" ");
		}
		ret = xTaskGenericCreate(
				RtlConsolTaskRam,
				(const char *)"LOGUART_TASK",
				LOGUART_STACK_SIZE,
				NULL,
				tskIDLE_PRIORITY + 5 + PRIORITIE_OFFSET,
				NULL,
				stack_addr,
				NULL);
		if (pdTRUE != ret)
		{
			DiagPrintf("Create Log UART Task Err!!\n");
		}
	}
#else
	if (pdTRUE != xTaskCreate( RtlConsolTaskRam, (const signed char * const)"LOGUART_TASK", LOGUART_STACK_SIZE, NULL, tskIDLE_PRIORITY + 5 + PRIORITIE_OFFSET, NULL))
	{
		DiagPrintf("Create Log UART Task Err!!\n");
	}
#endif

#endif

#endif
    }

    CONSOLE_8195A();
}

extern uint8_t** GetArgv(const uint8_t *string);
#if SUPPORT_LOG_SERVICE
extern char log_buf[LOG_SERVICE_BUFLEN];
extern xSemaphoreHandle	log_rx_interrupt_sema;
#endif
//======================================================
void console_cmd_exec(PUART_LOG_CTL   pUartLogCtlExe)
{
    uint8_t  CmdCnt = 0;
    uint8_t  argc = 0;
    uint8_t  **argv;
    //uint32_t  CmdNum;
    PUART_LOG_BUF   pUartLogBuf = pUartLogCtlExe->pTmpLogBuf;
#if SUPPORT_LOG_SERVICE
    strncpy(log_buf, (const uint8_t*)&(*pUartLogBuf).UARTLogBuf[0], LOG_SERVICE_BUFLEN-1);
#endif
    argc = GetArgc((const uint8_t*)&((*pUartLogBuf).UARTLogBuf[0]));
    argv = GetArgv((const uint8_t*)&((*pUartLogBuf).UARTLogBuf[0]));

	if(argc > 0){
#if SUPPORT_LOG_SERVICE
//		if(log_handler(argv[0]) == NULL)
//			legency_interactive_handler(argc, argv);
              //RtlUpSema((_Sema *)&log_rx_interrupt_sema);
		rtw_up_sema((_sema *)&log_rx_interrupt_sema);
#endif
              ArrayInitialize(argv[0], sizeof(argv[0]) ,0);
	}else{
#if defined(configUSE_WAKELOCK_PMU) && (configUSE_WAKELOCK_PMU == 1)
		pmu_acquire_wakelock(BIT(PMU_LOGUART_DEVICE));
#endif
		CONSOLE_8195A(); // for null command
	}

    (*pUartLogBuf).BufCount = 0;
    ArrayInitialize(&(*pUartLogBuf).UARTLogBuf[0], UART_LOG_CMD_BUFLEN, '\0');
}
//======================================================
// overload original RtlConsolTaskRam
//MON_RAM_TEXT_SECTION
void
RtlConsolTaskRam(
    void *Data
)
{
#if SUPPORT_LOG_SERVICE
	log_service_init();
#endif
    //4 Set this for UartLog check cmd history
#ifdef CONFIG_KERNEL
	pUartLogCtl->TaskRdy = 1;
	up_sema_from_isr = rtw_up_sema_from_isr;
#endif
#ifndef CONFIG_KERNEL
    pUartLogCtl->BootRdy = 1;
#endif
    do{
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
		//RtlDownSema((_Sema *)&pUartLogCtl->Sema);
		rtw_down_sema((_sema *)&pUartLogCtl->Sema);
#endif
        if (pUartLogCtl->ExecuteCmd) {
			// Add command handler here
			console_cmd_exec((PUART_LOG_CTL)pUartLogCtl);
            //UartLogCmdExecute((PUART_LOG_CTL)pUartLogCtl);
            pUartLogCtl->ExecuteCmd = _FALSE;
        }
    }while(1);
}

//======================================================
#if BUFFERED_PRINTF
xTaskHandle print_task = NULL;
EventGroupHandle_t print_event = NULL;
char print_buffer[MAX_PRINTF_BUF_LEN];
int flush_idx = 0;
int used_length = 0;

int available_space(void)
{
    return MAX_PRINTF_BUF_LEN-used_length;
}

int buffered_printf(const char* fmt, ...)
{
    if((print_task==NULL) || (print_event==NULL) )
        return 0;
    char tmp_buffer[UART_LOG_CMD_BUFLEN+1];
    static int print_idx = 0;
    int cnt;

    if(xEventGroupGetBits(print_event)!=1)
            xEventGroupSetBits(print_event, 1);

    memset(tmp_buffer,0,UART_LOG_CMD_BUFLEN+1);
    VSprintf(tmp_buffer, fmt, ((const int *)&fmt)+1);
    cnt = _strlen(tmp_buffer);
    if(cnt < available_space()){
        if(print_idx >= flush_idx){
            if(MAX_PRINTF_BUF_LEN-print_idx >= cnt){
                memcpy(&print_buffer[print_idx], tmp_buffer, cnt);
            }else{
                memcpy(&print_buffer[print_idx], tmp_buffer, MAX_PRINTF_BUF_LEN-print_idx);
                memcpy(&print_buffer[0], &tmp_buffer[MAX_PRINTF_BUF_LEN-print_idx], cnt-(MAX_PRINTF_BUF_LEN-print_idx));
            }
        }else{  // space is flush_idx - print_idx, and available space is enough
            memcpy(&print_buffer[print_idx], tmp_buffer, cnt);
        }
        // protection needed
        taskENTER_CRITICAL();
        used_length+=cnt;
        taskEXIT_CRITICAL();
        print_idx+=cnt;
        if(print_idx>=MAX_PRINTF_BUF_LEN)
            print_idx -= MAX_PRINTF_BUF_LEN;
    }else{
        // skip
        cnt = 0;
    }

    return cnt;
}


void printing_task(void* arg)
{
    while(1){
        //wait event
        if(xEventGroupWaitBits(print_event, 1,  pdFALSE, pdFALSE, 100 ) == 1){
            while(used_length > 0){
                putchar(print_buffer[flush_idx]);
                flush_idx++;
                if(flush_idx >= MAX_PRINTF_BUF_LEN)
                    flush_idx-=MAX_PRINTF_BUF_LEN;
                taskENTER_CRITICAL();
                used_length--;
                taskEXIT_CRITICAL();
            }
            // clear event
            xEventGroupClearBits( print_event, 1);
        }
    }
}

void rtl_printf_init()
{
    if(print_event==NULL){
        print_event = xEventGroupCreate();
        if(print_event == NULL)
            printf("\n\rprint event init fail!\n");
    }
    if(print_task == NULL){
        if(xTaskCreate(printing_task, (const char *)"print_task", 512, NULL, tskIDLE_PRIORITY + 1, &print_task) != pdPASS)
            printf("\n\rprint task init fail!\n");
    }
}
#endif
//======================================================


__weak void console_init(void)
{

	    IRQ_HANDLE          UartIrqHandle;
	    
	    //4 Register Log Uart Callback function
	    UartIrqHandle.Data = NULL;//(uint32_t)&UartAdapter;
	    UartIrqHandle.IrqNum = UART_LOG_IRQ;
	    UartIrqHandle.IrqFun = (IRQ_FUN) UartLogIrqHandleRam;
	    UartIrqHandle.Priority = 6;

	    
	    //4 Register Isr handle
	    InterruptUnRegister(&UartIrqHandle); 
	    InterruptRegister(&UartIrqHandle); 
        


#if !TASK_SCHEDULER_DISABLED    
    RtlConsolInitRam((uint32_t)RAM_STAGE,(uint32_t)0,(void*)NULL);
#else
    RtlConsolInitRam((uint32_t)ROM_STAGE,(uint32_t)0,(void*)NULL);
#endif

#if BUFFERED_PRINTF
    rtl_printf_init();
#endif
}
