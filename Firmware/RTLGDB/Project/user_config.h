#ifndef _user_config_h_
#define _user_config_h_

#define SYS_VERSION "1.0.1"
#include "sdk_ver.h"

#define USE_WEB				80 	// включить в трансялцию порт Web, если =0 - по умолчанию выключен
//#define WEBSOCKET_ENA		0 // включить WEBSOCKET
//#define USE_SNTP			0 	// включить в трансялцию драйвер SNTP, если =0 - по умолчанию выключен, = 1 - по умолчанию включен.
//#define USE_NETBIOS			0 	// включить в трансялцию драйвер NETBIOS, если =0 - по умолчанию выключен.

#define WEB_DEBUG_FUNCTIONS 1 // =1 - включить в WEB отладочные функции, =0 отключить (остается только конфигурация WiFi)

#ifdef _MSC_VER // IntelliSense
#define __attribute__(packed)
//typedef int8_t err_t;
#endif

#endif // _user_config_h_


