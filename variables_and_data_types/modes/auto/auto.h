#ifndef _AUTO_H_
#define _AUTO_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include <time.h>

#include "config.h"
#include "log/log.h"
#include "gpios/gpio.h"
#include "temperature/temperature.h"
#include "soil_moisture/moisture.h"
#include "pumps/pump.h"
#include "leds/led.h"
#include "buttons/button.h"

void auto_mode_run(temp_sensor_t *temp_sensor, moisture_sensor_t *moisture_sensor, pump_t *pump);


#ifdef __cplusplus
}
#endif
#endif // _AUTO_H_