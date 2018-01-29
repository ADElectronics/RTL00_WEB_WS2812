#include "ledeffectsserver.h"
#include "ws2812.h"
#include <flash_api.h>

volatile uint32_t cfg_updated = 0;
ws2812_t *ws2812_cfg = NULL;
strip_handler_t strip; 
SemaphoreHandle_t cfg_sema = NULL;

ctx_rainbow_t filt_rainbow;
ctx_fade_t filt_fade;
ctx_const_t filt_const;
ctx_wave_t filt_wave;

void ledEffectsServer_Init()
{
	ws2812_cfg = ws2812_Init(WS2812_LEDS_MAX);
	if (ws2812_cfg == NULL)
	{
		printf("[%s] ws2812_Init() failed\n", __func__);
		return;
	}

	ledFilter_Init(&strip, ws2812_cfg);

	ledFilter_InitRainbow(&filt_rainbow);
	ledFilter_InitFade(&filt_fade);
	ledFilter_InitConstant(&filt_const);
	ledFilter_InitWave(&filt_wave);

	ledFilter_SetDefualtValue(&strip, MAX_STRIP_BRIGHT);
}

void ledEffectsServer_Task()
{
	cfg_sema = xSemaphoreCreateMutex();

	while (1)
	{
		if (xSemaphoreTake(cfg_sema, 5 * configTICK_RATE_HZ))
		{
			ledFilter_Rainbow(&filt_rainbow, &strip);
			ledFilter_Constant(&filt_const, &strip);
			ledFilter_Wave(&filt_wave, &strip);
			ledFilter_Fade(&filt_fade, &strip);
			

			ws2812_Update(ws2812_cfg, strip.hsv_vals, strip.strip_len, strip.delay);
			xSemaphoreGive(cfg_sema);
		}
		WDGRefresh();
	}
}
/*

void ledEffectsServer_LoadConfigFromFlash()
{
	flash_t flash;

	printf("[%s] reading config from flash\n", __func__);
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_stream_read(&flash, LED_SETTINGS_SECTOR, sizeof(strip_cfg), (uint8_t *)&strip_cfg);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
}

void ledEffectsServer_SaveConfigToFlash()
{
	flash_t flash;

	printf("[%s] saving config to flash\n", __func__);

	cfg_updated = 0;

	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_erase_sector(&flash, LED_SETTINGS_SECTOR);
	flash_stream_write(&flash, LED_SETTINGS_SECTOR, sizeof(strip_cfg), (uint8_t *)&strip_cfg);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
}
*/
/*
struct blinken_cfg *blinken_get_config(void)
{
blinken_cfg_t *cfg = NULL;

if(strip_cfg.magic == BLINKEN_CFG_MAGIC)
{
cfg = malloc(sizeof(*cfg));
if(cfg != NULL)
{
memmove(cfg, &strip_cfg, sizeof(*cfg));
}
}

return cfg;
}


int blinken_set_config(blinken_cfg_t *cfg)
{
int result;
BaseType_t status;

result = 0;
if(cfg == NULL || cfg->magic != BLINKEN_CFG_MAGIC)
{
result = -1;
goto error;
}

status = xSemaphoreTake(cfg_sema, 15 * configTICK_RATE_HZ);
if(status != pdTRUE)
{
printf("[%s] Timeout waiting for config sema.\n", __func__);
result = -1;
goto error;
}

result = init_handler(&handler, cfg, ws2812_cfg, true);
if(result == 0)
{
memmove(&strip_cfg, cfg, sizeof(strip_cfg));
save_config();
}

xSemaphoreGive(cfg_sema);

error:
return result;
}
*/


