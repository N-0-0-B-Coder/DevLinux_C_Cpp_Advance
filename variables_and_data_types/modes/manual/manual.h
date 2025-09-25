#ifndef _MANUAL_H_
#define _MANUAL_H_

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif

#include <time.h>

#include "config.h"
#include "buttons/button.h"
#include "leds/led.h"
#include "log/log.h"
#include "pumps/pump.h"

void manual_mode_run(pump_t *pump);

#ifdef __cplusplus
}
#endif

#endif // _MANUAL_H_
