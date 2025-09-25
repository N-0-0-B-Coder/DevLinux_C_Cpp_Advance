#ifndef _INIT_H_
#define _INIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "log/log.h"
#include "gpios/gpio.h"
#include "temperature/temperature.h"
#include "soil_moisture/moisture.h"
#include "pumps/pump.h"
#include "leds/led.h"
#include "buttons/button.h"

int init_system(temp_sensor_t *temp_sensor, moisture_sensor_t *moisture_sensor, pump_t *pump);

#ifdef __cplusplus
}
#endif
#endif // _INIT_H_