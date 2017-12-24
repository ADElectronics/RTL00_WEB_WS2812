#ifndef _WS2812_H_
#define _WS2812_H_

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include <spi_api.h>
#include <spi_ex_api.h>
#include <autoconf.h>
#include <platform_stdlib.h>
#include "semphr.h"
#include "event_groups.h"
#include "macro_common.h"

#define WS2812_LEDS_MAX         228
#define WS2812_RESET_LEN        (50 / 2)
#define WS2812_DMABUF_LEN(x)    ((x) * 3 * 4 + WS2812_RESET_LEN)

#define WS2812_SPI_FREQ			3400000 // и делённое на 4 (4 бита SPI за 1 бит WS8212) ~~ в итоге 800кГц
#define WS2812_SPI_MOSI			PC_2 // SPI0
#define WS2812_SPI_MISO			PC_3
#define WS2812_SPI_SCLK			PC_1
#define WS2812_SPI_CS			PC_0

// Events to signal completion of DMA transfer
#define BIT_START				(1 << 0)
#define BIT_DONE				(1 << 1)

// посылается 2 бита протокола WS2812 за один байт SPI, один бит WS2812 за 4 бита SPI.
#define WS2812_BITS_00			0x88
#define WS2812_BITS_01          0x8e
#define WS2812_BITS_10          0xe8
#define WS2812_BITS_11          0xee

typedef struct 
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} ws2812_rgb_t;

typedef struct 
{
    uint8_t hue;
    uint8_t sat;
    uint8_t value;
} ws2812_hsv_t;

typedef struct 
{
	spi_t spi_master;
	EventGroupHandle_t *events;
	SemaphoreHandle_t *mutex;
	uint8_t *dma_buff;
	size_t buff_len;
	uint16_t strip_len;
} ws2812_t;

ws2812_t *ws2812_Init(uint16_t len);
int32_t ws2812_SetLen(ws2812_t *cfg, uint16_t len);
//int32_t WS2812_DeInit(WS2812_t *cfg);
int32_t ws2812_Update(ws2812_t *cfg, ws2812_hsv_t hsv[], uint32_t len, uint16_t delay);

#endif // _WS2812_H_
