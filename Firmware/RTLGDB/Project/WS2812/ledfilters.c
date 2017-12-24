#include "ledfilters.h"

extern uint32_t cfg_updated;

#pragma region Базовые функции по работе с фильтрами
int32_t ledFilter_Init(strip_handler_t *strip, ws2812_t *ws2812)
{
    if(strip->check != LEDFILTERS_CFG_CHECKWORD)
	{
        memset(strip, 0xff, sizeof(strip_handler_t));
        strip->check = LEDFILTERS_CFG_CHECKWORD;
        strip->strip_len = DEF_STRIP_LEN;
        strip->delay = 10;
        strip->brightness = MAX_STRIP_BRIGHT;

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

	if (ctx->enabled == 0) return;

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
		tmp_hue %= 256;
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
		ctx->valid = 1;
		ctx->min = 0;
		ctx->max = 255;
		ctx->steps = LEDFILTERS_MAX_STEPS;
		ctx->enabled = 1;
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

	if (ctx->enabled == 0) return;

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

}

void ledFilter_Wave(ctx_wave_t *ctx, strip_handler_t *strip)
{

}
#pragma endregion

#pragma region Constant
void ledFilter_InitConstant(ctx_const_t *ctx)
{

}

void ledFilter_Constant(ctx_const_t *ctx, strip_handler_t *strip)
{

}
#pragma endregion

