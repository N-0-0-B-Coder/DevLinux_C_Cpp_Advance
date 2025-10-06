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
#include "buttons/button.h"
#include "temperature/temperature.h"
#include "soil_moisture/moisture.h"
#include "pumps/pump.h"
#include "leds/led.h"
#include "buttons/button.h"

/**
 * @brief Initialize the entire system including sensors, pump, and GPIOs
 * 
 * @param temp_sensor [in, out] Pointer to temperature sensor structure
 * @param moisture_sensor [in, out] Pointer to moisture sensor structure
 * @param pump [in, out] Pointer to pump structure
 * 
 * @return int 0 if successful, error code otherwise
 */
int init_system(temp_sensor_t *temp_sensor, moisture_sensor_t *moisture_sensor, pump_t *pump);

#ifdef __cplusplus
}
#endif
#endif // _INIT_H_