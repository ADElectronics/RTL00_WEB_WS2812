/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */
//#include "build_info.h"
#include "rtl8195a.h"
#ifdef PLATFORM_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#include "platform_stdlib.h"
// #include "rtl_lib.h"
#endif

#if defined (CONFIG_USB_EN) && defined(CONFIG_USB_HOST_ONLY)
	extern void _usb_init(void);
#endif

#if defined(CONFIG_SDIO_DEVICE_EN) && defined(CONFIG_SDIO_DEVICE_NORMAL)
extern void HalSdioInit(void);
#endif

#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
extern void init_rom_wlan_ram_map(void);
extern void wlan_network(void);
#endif

//3 Monitor App Function
extern void RtlConsolInitRam(uint32_t Boot, uint32_t TBLSz, void *pTBL);
#ifndef CONFIG_KERNEL
extern void RtlConsolTaskRom(void *Data);
#endif

#ifndef CONFIG_WITHOUT_MONITOR
extern COMMAND_TABLE    UartLogRamCmdTable[];
extern uint32_t GetRamCmdNum(void);
extern void UartLogIrqHandleRam(void * Data);
#endif

#ifdef CONFIG_APP_DEMO
#define MAIN_APP_DEFAULT_STACK_SIZE         2048
#define MAIN_APP_DEFAULT_PRIORITY           (tskIDLE_PRIORITY + 1)
#endif

#ifdef CONFIG_MBED_ENABLED
extern void __libc_fini_array (void);
extern void __libc_init_array (void);
extern  void SVC_Handler (void);
extern  void PendSV_Handler (void);
extern  void SysTick_Handler (void);
#endif

#ifndef CONFIG_WITHOUT_MONITOR
static 
void
ReRegisterPlatformLogUart(
    void
)
{
    IRQ_HANDLE          UartIrqHandle;
    
    //4 Register Log Uart Callback function
    UartIrqHandle.Data = (uint32_t)NULL;//(uint32_t)&UartAdapter;
    UartIrqHandle.IrqNum = UART_LOG_IRQ;
    UartIrqHandle.IrqFun = (IRQ_FUN) UartLogIrqHandleRam;
    UartIrqHandle.Priority = 5;

    
    //4 Register Isr handle
    InterruptUnRegister(&UartIrqHandle); 
    InterruptRegister(&UartIrqHandle); 
#if !TASK_SCHEDULER_DISABLED    
    RtlConsolInitRam((uint32_t)RAM_STAGE,(uint32_t)GetRamCmdNum(),(void*)&UartLogRamCmdTable);
#else
    //RtlConsolInit(ROM_STAGE,GetRomCmdNum(),(void*)&UartLogRomCmdTable);// executing boot seq., 
    //pUartLogCtl->TaskRdy = 1;
    RtlConsolInitRam((uint32_t)ROM_STAGE,(uint32_t)GetRamCmdNum(),(void*)&UartLogRamCmdTable);
#endif
}
#endif  // end of "#ifndef CONFIG_WITHOUT_MONITOR"


void ShowRamBuildInfo(void)
{
    /*
    DBG_8195A("=========================================================\n\n");
    //DBG_8195A("Build Time: "UTS_VERSION"\n");
    DBG_8195A("Build Time: "RTL8195AFW_COMPILE_TIME"\n");
    DBG_8195A("Build Author: "RTL8195AFW_COMPILE_BY"\n");    
    DBG_8195A("Build Host: "RTL8195AFW_COMPILE_HOST"\n");    
    DBG_8195A("Build ToolChain Version: "RTL195AFW_COMPILER"\n\n");    
    DBG_8195A("=========================================================\n");
    */
}

#if 1 //def CONFIG_APP_DEMO
#include "rtl8195a.h"
//#include "device.h"
//#include "gpio_api.h"   // mbed
typedef struct _UART_LOG_BUF_ {
        uint8_t  BufCount;                           //record the input cmd char number.
        uint8_t  UARTLogBuf[127];   //record the input command.
} UART_LOG_BUF, *PUART_LOG_BUF;

//MON_RAM_BSS_SECTION
typedef struct _UART_LOG_CTL_ {
        uint8_t  NewIdx;		//+0
        uint8_t  SeeIdx;		//+1
        uint8_t  RevdNo;		//+2
        uint8_t  EscSTS;		//+3
        uint8_t  ExecuteCmd;	//+4
        uint8_t  ExecuteEsc; //+5
        uint8_t  BootRdy;	//+6
        uint8_t  Resvd;		//+7
        PUART_LOG_BUF   pTmpLogBuf;
        void *pfINPUT;
        PCOMMAND_TABLE  pCmdTbl;
        uint32_t CmdTblSz;

        uint32_t  CRSTS;

        uint8_t  (*pHistoryBuf)[127];

		uint32_t	TaskRdy;
		uint32_t	Sema;
} UART_LOG_CTL, *PUART_LOG_CTL;

extern volatile UART_LOG_CTL *pUartLogCtl;

_WEAK int main(void)
{
	HalPinCtrlRtl8195A(JTAG, 0, 1);

	DiagPrintf("\r\nRTL Console ROM: Start - press key 'Up', Help '?'\r\n");
	while(pUartLogCtl->ExecuteEsc != 1);
	pUartLogCtl->RevdNo = 0;
	pUartLogCtl->BootRdy = 1;
    DiagPrintf("\r<RTL871xAx>");
    while(1) {
    	while(pUartLogCtl->ExecuteCmd != 1 );
    	UartLogCmdExecute(pUartLogCtl);
        DiagPrintf("\r<RTL871xAx>");
        pUartLogCtl->ExecuteCmd = 0;
    }
    
    return 0;
}
#else
//default main
_WEAK int main(void)
{
    // Init SDIO
#if defined(CONFIG_SDIO_DEVICE_EN) && defined(CONFIG_SDIO_DEVICE_NORMAL)
    HalSdioInit();
#endif

#ifndef CONFIG_WITHOUT_MONITOR
    ReRegisterPlatformLogUart();
#endif
                
#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
	wlan_network();
#else

#if defined (CONFIG_USB_EN) && defined(CONFIG_USB_HOST_ONLY)
	_usb_init();
#endif

#endif  // end of else of "#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)"

	//3 4)Enable Schedule
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
    #ifdef PLATFORM_FREERTOS
		vTaskStartScheduler();
    #endif
#else
		RtlConsolTaskRom(NULL);
#endif
    return 0;
}
#endif // end of #if CONFIG_APP_DEMO

__weak void __low_level_init(void)   
{
	// weak function
}

#if defined ( __ICCARM__ )
#pragma section="SDRAM.bss"
#pragma section="SDRAM.bss"
#endif
// The Main App entry point
void _AppStart(void)
{
#ifdef CONFIG_MBED_ENABLED
    InterruptForOSInit((void*)SVC_Handler,
                       (void*)PendSV_Handler,
                       (void*)SysTick_Handler);
    __asm (
        "ldr   r0, =SystemInit\n"
        "blx   r0\n"
        "ldr   r0, =_start\n"
        "bx    r0\n"
    );

    for(;;);
#else
    // It's Not Mbed BSP
#ifdef CONFIG_KERNEL
#endif

    // Disable debug info log of spiflash
    DBG_INFO_MSG_OFF(_DBG_SPI_FLASH_);
        
#ifdef CONFIG_APP_DEMO
#ifdef PLATFORM_FREERTOS
    xTaskCreate( (TaskFunction_t)main, "MAIN_APP__TASK", (MAIN_APP_DEFAULT_STACK_SIZE/4), (void *)NULL, MAIN_APP_DEFAULT_PRIORITY, NULL);
    vTaskStartScheduler();
#endif

#else
	
	__low_level_init();		
#if defined ( __ICCARM__ )
	// __iar_data_init3 replaced by __iar_cstart_call_ctors, just do c++ constructor,
	__iar_cstart_call_ctors(NULL);
#ifdef CONFIG_SDR_EN
	// clear SDRAM bss
	uint8_t* __sdram_bss_start__		= (uint8_t*)__section_begin("SDRAM.bss");
	uint8_t* __sdram_bss_end__			= (uint8_t*)__section_end("SDRAM.bss");
	//DiagPrintf("clean sdram bss %8x to %8x\n\r", __sdram_bss_start__, __sdram_bss_end__);
	if((int)__sdram_bss_end__-(int)__sdram_bss_start__ > 0)
		memset(__sdram_bss_start__, 0, (int)__sdram_bss_end__-(int)__sdram_bss_start__);
#endif
#elif defined ( __GNUC__ )
#ifdef CONFIG_SDR_EN
	// clear SDRAM bss	
	extern uint8_t __sdram_bss_start__[];
	extern uint8_t __sdram_bss_end__[];
	//DiagPrintf("clean sdram bss %8x to %8x\n\r", __sdram_bss_start__, __sdram_bss_end__);
	if((int)__sdram_bss_end__-(int)__sdram_bss_start__ > 0)
		memset(__sdram_bss_start__, 0, (int)__sdram_bss_end__-(int)__sdram_bss_start__);
#endif
#else
	#error !!!!!!NOT Support this compiler!!!!!!
#endif
	// force SP align to 8 byte not 4 byte (initial SP is 4 byte align)
	__asm( 
		  "mov r0, sp\n"
		  "bic r0, r0, #7\n" 
		  "mov sp, r0\n"
	);
	
    main();
#if defined ( __ICCARM__ )	
	// for compile issue, If user never call this function, Liking fail 
	__iar_data_init3();
#endif
#endif // end of #if CONFIG_APP_DEMO
    
#endif  // end of else of "#ifdef CONFIG_MBED_ENABLED"
}
