#ifndef _LEDEFFECTSSERVER_H_
#define _LEDEFFECTSSERVER_H_

#include "ledfilters.h"


// Публичные конфинги фильтров
extern strip_handler_t strip;
extern ctx_rainbow_t filt_rainbow;
extern ctx_fade_t filt_fade;
extern ctx_const_t filt_const;
extern ctx_wave_t filt_wave;

void ledEffectsServer_Init();
void ledEffectsServer_Task();

#endif // _LEDEFFECTSSERVER_H_

