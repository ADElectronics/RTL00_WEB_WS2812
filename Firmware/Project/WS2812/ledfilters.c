#include "ledfilters.h"

extern uint32_t cfg_updated;

uint8_t sin_table[256] = {
	0x80, 0x83, 0x86, 0x89, 0x8C, 0x90, 0x93, 0x96,
	0x99, 0x9C, 0x9F, 0xA2, 0xA5, 0xA8, 0xAB, 0xAE,
	0xB1, 0xB3, 0xB6, 0xB9, 0xBC, 0xBF, 0xC1, 0xC4,
	0xC7, 0xC9, 0xCC, 0xCE, 0xD1, 0xD3, 0xD5, 0xD8,
	0xDA, 0xDC, 0xDE, 0xE0, 0xE2, 0xE4, 0xE6, 0xE8,
	0xEA, 0xEB, 0xED, 0xEF, 0xF0, 0xF1, 0xF3, 0xF4,
	0xF5, 0xF6, 0xF8, 0xF9, 0xFA, 0xFA, 0xFB, 0xFC,
	0xFD, 0xFD, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFD,
	0xFD, 0xFC, 0xFB, 0xFA, 0xFA, 0xF9, 0xF8, 0xF6,
	0xF5, 0xF4, 0xF3, 0xF1, 0xF0, 0xEF, 0xED, 0xEB,
	0xEA, 0xE8, 0xE6, 0xE4, 0xE2, 0xE0, 0xDE, 0xDC,
	0xDA, 0xD8, 0xD5, 0xD3, 0xD1, 0xCE, 0xCC, 0xC9,
	0xC7, 0xC4, 0xC1, 0xBF, 0xBC, 0xB9, 0xB6, 0xB3,
	0xB1, 0xAE, 0xAB, 0xA8, 0xA5, 0xA2, 0x9F, 0x9C,
	0x99, 0x96, 0x93, 0x90, 0x8C, 0x89, 0x86, 0x83,
	0x80, 0x7D, 0x7A, 0x77, 0x74, 0x70, 0x6D, 0x6A,
	0x67, 0x64, 0x61, 0x5E, 0x5B, 0x58, 0x55, 0x52,
	0x4F, 0x4D, 0x4A, 0x47, 0x44, 0x41, 0x3F, 0x3C,
	0x39, 0x37, 0x34, 0x32, 0x2F, 0x2D, 0x2B, 0x28,
	0x26, 0x24, 0x22, 0x20, 0x1E, 0x1C, 0x1A, 0x18,
	0x16, 0x15, 0x13, 0x11, 0x10, 0x0F, 0x0D, 0x0C,
	0x0B, 0x0A, 0x08, 0x07, 0x06, 0x06, 0x05, 0x04,
	0x03, 0x03, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03,
	0x03, 0x04, 0x05, 0x06, 0x06, 0x07, 0x08, 0x0A,
	0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x13, 0x15,
	0x16, 0x18, 0x1A, 0x1C, 0x1E, 0x20, 0x22, 0x24,
	0x26, 0x28, 0x2B, 0x2D, 0x2F, 0x32, 0x34, 0x37,
	0x39, 0x3C, 0x3F, 0x41, 0x44, 0x47, 0x4A, 0x4D,
	0x4F, 0x52, 0x55, 0x58, 0x5B, 0x5E, 0x61, 0x64,
	0x67, 0x6A, 0x6D, 0x70, 0x74, 0x77, 0x7A, 0x7D
};

#pragma region Базовые функции по работе с фильтрами
int32_t ledFilter_Init(strip_handler_t *strip, ws2812_t *ws2812)
{
    if(strip->check != LEDFILTERS_CFG_CHECKWORD)
	{
        memset(strip, 0xff, sizeof(strip_handler_t));
        strip->check = LEDFILTERS_CFG_CHECKWORD;
        strip->strip_len = DEF_STRIP_LEN;
        strip->delay = 10; // общая скорость
        strip->brightness = MAX_STRIP_BRIGHT;
		strip->enable = 1;
		strip->try_enable = 0;
        cfg_updated = 1;
    }

    if(strip->strip_len > MAX_STRIP_LEN)
	{
        strip->strip_len = MAX_STRIP_LEN;
        cfg_updated = 1;
    }

    if(strip->delay > MAX_STRIP_DELAY)
	{
        strip->delay = MAX_STRIP_DELAY;
        cfg_updated = 1;
    }

    if(strip->brightness > MAX_STRIP_BRIGHT)
	{
        strip->brightness = MAX_STRIP_BRIGHT;
        cfg_updated = 1;
    }

    strip->hsv_vals = malloc(sizeof(ws2812_hsv_t) * strip->strip_len);
	if (strip->hsv_vals == NULL)
	{
		printf("[%s] malloc() failed\n", __func__);
		return -1;
	}

	memset(strip->hsv_vals, 0x0, sizeof(ws2812_hsv_t) * strip->strip_len);

	ws2812_SetLen(ws2812, strip->strip_len);
	
	return 1;
}

void ledFilter_SetDefualtValue(strip_handler_t *strip, uint8_t val)
{
	uint32_t i;
	for (i = 0; i < strip->strip_len; i++)
	{
		strip->hsv_vals[i].value = val;
	}
}
#pragma endregion

#pragma region Rainbow
void ledFilter_InitRainbow(ctx_rainbow_t *ctx)
{
	if (ctx->valid != LEDFILTERS_CFG_CHECKWORD)
	{
		ctx->valid = LEDFILTERS_CFG_CHECKWORD;
		ctx->hue_steps = WS2812_LEDS_MAX / 2; // Во сколько светодиодов вместить всю радугу
		ctx->cycle_steps = 1;
		ctx->enabled = 1;
		cfg_updated = 1;
	}

	ctx->curr_hue = 0;
}

void ledFilter_Rainbow(ctx_rainbow_t *ctx, strip_handler_t *strip)
{
	uint32_t i, j;
	ws2812_hsv_t tmp_hsv;
	uint8_t tmp_hue;

	if (ctx->enabled == 0 || strip->enable == 0) return;

	tmp_hue = ctx->curr_hue;
	tmp_hsv.sat = 255;

	for (i = 0, j = ctx->hue_steps; i < strip->strip_len; i++)
	{
		if (i == j)
		{
			j += ctx->hue_steps;
			tmp_hue = ctx->curr_hue;
		}

		tmp_hsv.hue = tmp_hue;
		tmp_hsv.value = strip->hsv_vals[i].value;
		strip->hsv_vals[i] = tmp_hsv;
		tmp_hue += 255/ ctx->hue_steps;
		//tmp_hue %= 256;
	}

	ctx->curr_hue += ctx->cycle_steps;
	ctx->curr_hue %= 256;
}
#pragma endregion

#pragma region Fade
void ledFilter_InitFade(ctx_fade_t *ctx)
{
	if (ctx->valid != LEDFILTERS_CFG_CHECKWORD)
	{
		ctx->valid = LEDFILTERS_CFG_CHECKWORD;
		ctx->min = 0;
		ctx->max = 255;
		ctx->steps = LEDFILTERS_MAX_STEPS;
		ctx->enabled = 0;
		cfg_updated = 1;
	}

	if (ctx->steps == 0)
	{
		ctx->enabled = 0;
	}

	ctx->curr_val = 0;
	ctx->curr_step = 0;
}

void ledFilter_Fade(ctx_fade_t *ctx, strip_handler_t *strip)
{
	uint32_t i;

	if (ctx->enabled == 0 || strip->enable == 0) return;

	if (ctx->curr_val == 0)
	{
		for (i = 0; i < strip->strip_len; i++)
		{
			if (strip->hsv_vals[i].value > ctx->min)
			{
				if (strip->hsv_vals[i].value > (255 / ctx->steps))
					strip->hsv_vals[i].value -= (255 / ctx->steps);
				else
				{
					strip->hsv_vals[i].value = 0;
					ctx->curr_step = ctx->steps;
				}
			}
			else
			{
				ctx->curr_step = ctx->steps;
			}			
		}
	}
	else
	{
		for (i = 0; i < strip->strip_len; i++)
		{
			if (strip->hsv_vals[i].value <= ctx->max)
			{
				if (strip->hsv_vals[i].value + (255 / ctx->steps) > ctx->max)
				{
					strip->hsv_vals[i].value = ctx->max;
					ctx->curr_step = ctx->steps;
				}					
				else
					strip->hsv_vals[i].value += (255 / ctx->steps);
			}
			else
			{
				ctx->curr_step = ctx->steps;
			}
		}
	}
	ctx->curr_step++;

	if (ctx->curr_step >= ctx->steps)
	{
		if (ctx->curr_val) ctx->curr_val = 0;
		else ctx->curr_val = 1;
		ctx->curr_step = 0;
	}
}
#pragma endregion

#pragma region Wave
void ledFilter_InitWave(ctx_wave_t *ctx)
{
	if (ctx->valid != LEDFILTERS_CFG_CHECKWORD)
	{
		ctx->valid = LEDFILTERS_CFG_CHECKWORD;
		ctx->enabled = 0;
		ctx->wave_steps = 20;
		ctx->angle = 0;
		ctx->step = 1;
		cfg_updated = 1;
	}

	//for (uint16_t i = 0; i < 255; i++)
	//	sin_table[i] = (uint16_t)(sin((double)(((double)i + 2.0) * M_PI)/ 255.0) * UINT8_MAX);
}

void ledFilter_Wave(ctx_wave_t *ctx, strip_handler_t *strip)
{
	uint32_t i, j;
	uint8_t tmp_angle = 0;
	if (ctx->enabled == 0 || strip->enable == 0) return;

	tmp_angle = ctx->angle;
	for (i = 0, j = ctx->wave_steps; i < strip->strip_len; i++)
	{
		if (i == j)
		{
			j += ctx->wave_steps;
			tmp_angle = ctx->angle;
		}
		strip->hsv_vals[i].value = sin_table[tmp_angle];
		tmp_angle += 255 / ctx->wave_steps;
		//tmp_angle %= 256;
	}

	ctx->angle += ctx->step;
}
#pragma endregion

#pragma region Constant
void ledFilter_InitConstant(ctx_const_t *ctx)
{
	if (ctx->valid != LEDFILTERS_CFG_CHECKWORD)
	{
		ctx->valid = LEDFILTERS_CFG_CHECKWORD;
		ctx->hue = 128;
		ctx->sat = 255;
		ctx->value = 255;
		ctx->enabled = 0;
		ctx->update = 0;
		cfg_updated = 1;
	}
}

void ledFilter_Constant(ctx_const_t *ctx, strip_handler_t *strip)
{
	uint32_t i;
	if (strip->try_enable)
	{
		for (i = 0; i < strip->strip_len; i++)
		{
			if (strip->hsv_vals[i].value < strip->brightness)
				strip->hsv_vals[i].value++;
			else
			{
				strip->enable = 1;
				strip->try_enable = 0;
			}
		}

		return;
	}
	else if (strip->enable == 0)
	{
		for (i = 0; i < strip->strip_len; i++)
		{
			if (strip->hsv_vals[i].value > 0)
				strip->hsv_vals[i].value--;
		}

		return;
	}
	else if (ctx->enabled == 0) return;

	if (ctx->update > 0)
	{
		for (i = 0; i < strip->strip_len; i++)
		{
			strip->hsv_vals[i].hue = ctx->hue;
			strip->hsv_vals[i].sat = ctx->sat;
			strip->hsv_vals[i].value = ctx->value;
		}

		ctx->update = 0;
	}
}
#pragma endregion

