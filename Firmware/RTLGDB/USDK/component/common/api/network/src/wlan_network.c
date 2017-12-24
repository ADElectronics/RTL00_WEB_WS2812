/*
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h" 

#include "main.h"
#include "main_test.h"
#if CONFIG_WLAN
#include "wifi_conf.h"
#include "wlan_intf.h"
#include "wifi_constants.h"
#endif
#include "lwip_netconf.h"
#include <platform/platform_stdlib.h>
//#include "wifi_interactive_ext.h"

#ifndef CONFIG_INIT_NET
#define CONFIG_INIT_NET             1
#endif
#ifndef CONFIG_INTERACTIVE_MODE
#define CONFIG_INTERACTIVE_MODE     1
#endif

#define STACKSIZE (512 + 768)

xSemaphoreHandle uart_rx_interrupt_sema = NULL;

void init_thread(void *param)
{

#if CONFIG_INIT_NET
#if CONFIG_LWIP_LAYER
	/* Initilaize the LwIP stack */
	// DBG_8195A("\nLwIP Init\n");
	LwIP_Init();
#endif
#endif
#if CONFIG_WIFI_IND_USE_THREAD
	wifi_manager_init();
#endif
#if CONFIG_WLAN
	// DBG_8195A("\nWiFi_on(RTW_MODE_STA)\n");
	wifi_on(RTW_MODE_STA);
#if CONFIG_AUTO_RECONNECT
	//setup reconnection flag
//	u8 mode;
//	if(wifi_get_autoreconnect(&mode) > 0 && mode != 1)
	wifi_set_autoreconnect(1);
#endif
//	printf("\n\r%s(%d), Available heap %d\n\r", __FUNCTION__, __LINE__, xPortGetFreeHeapSize());
#endif

#if CONFIG_INTERACTIVE_MODE
 	/* Initial uart rx swmaphore*/
	vSemaphoreCreateBinary(uart_rx_interrupt_sema);
	xSemaphoreTake(uart_rx_interrupt_sema, 1/portTICK_RATE_MS);
	start_interactive_mode();
#endif	

	/* Kill init thread after all init tasks done */
	vTaskDelete(NULL);
}

void wlan_network()
{
#if 0
	{
		void *stack_addr = tcm_heap_malloc(STACKSIZE*sizeof(int));
		if(stack_addr == NULL){
			printf("%s: Out of TCM heap!\n", __FUNCTION__);
		}
		if (xTaskGenericCreate(
				init_thread,
				(const char *)"init",
				STACKSIZE,
				NULL,
				tskIDLE_PRIORITY + 3 + PRIORITIE_OFFSET,
				NULL,
				stack_addr,
				NULL) != pdTRUE)
			printf("%s: xTaskCreate(init_thread) failed\n", __FUNCTION__);
	}
#else
	if(xTaskCreate(init_thread, ((const char*)"init"), STACKSIZE, NULL, tskIDLE_PRIORITY + 3 + PRIORITIE_OFFSET, NULL) != pdPASS) // +3
		printf("%s: xTaskCreate(init_thread) failed\n", __FUNCTION__);
#endif
}
