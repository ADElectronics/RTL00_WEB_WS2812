#ifndef _LEDFILTERS_H_
#define _LEDFILTERS_H_

#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "macro_common.h"
#include <autoconf.h>
#include <platform_opts.h>
#include <platform_stdlib.h>
#include "device_lock.h"
#include "ws2812.h"

#define LEDFILTERS_CFG_CHECKWORD	0x4C414D50 // "LAMP"
#define LEDFILTERS_MAX_STEPS		250 // 255 MAX !

#define DEF_STRIP_LEN				WS2812_LEDS_MAX
#define MAX_STRIP_LEN				WS2812_LEDS_MAX
#define MAX_STRIP_BRIGHT			255
#define MAX_STRIP_DELAY				500

#pragma region Rainbow
typedef struct
{
	uint8_t enabled;
	uint32_t valid;
	uint32_t hue_steps; // кол.во светодиодов, в которое вместить радугу
	uint8_t cycle_steps; // типа скорости
	uint8_t curr_hue;
} ctx_rainbow_t;
#pragma endregion

#pragma region Fade
typedef struct
{
	uint8_t enabled;
	uint32_t valid;
	uint32_t steps;
	uint32_t min;
	uint32_t max;
	uint32_t curr_val;
	int32_t curr_step;
} ctx_fade_t;
#pragma endregion

#pragma region Wave
typedef struct
{
	uint8_t enabled;
	uint32_t valid;
} ctx_wave_t;
#pragma endregion

#pragma region Constant
typedef struct
{
	uint8_t enabled;
	uint32_t valid;
} ctx_const_t;
#pragma endregion

typedef struct
{
	uint32_t check;
	ws2812_hsv_t *hsv_vals;
	uint32_t strip_len;
	uint32_t brightness;
	uint32_t delay;
} strip_handler_t;

int32_t ledFilter_Init(strip_handler_t *strip, ws2812_t *ws2812);

void ledFilter_InitRainbow(ctx_rainbow_t *ctx);
void ledFilter_Rainbow(ctx_rainbow_t *ctx, strip_handler_t *strip);
void ledFilter_InitFade(ctx_fade_t *ctx);
void ledFilter_Fade(ctx_fade_t *ctx, strip_handler_t *strip);
void ledFilter_InitWave(ctx_wave_t *ctx);
void ledFilter_Wave(ctx_wave_t *ctx, strip_handler_t *strip);

void ledFilter_SetDefualtValue(strip_handler_t *strip, uint8_t val);

#endif // _LEDFILTERS_H_
