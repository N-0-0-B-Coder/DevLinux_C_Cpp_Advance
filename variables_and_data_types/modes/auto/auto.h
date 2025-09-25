#ifndef _AUTO_H_
#define _AUTO_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _WIN32
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

#include "config.h"
#include "log/log.h"
#include "gpios/gpio.h"
#include "temperature/temperature.h"
#include "humidity/humidity.h"
#include "pumps/pump.h"
#include "leds/led.h"
#include "buttons/button.h"

void auto_mode_run(temp_sensor_t *temp_sensor, humidity_sensor_t *humidity_sensor, pump_t *pump);


#ifdef __cplusplus
}
#endif
#endif // _AUTO_H_