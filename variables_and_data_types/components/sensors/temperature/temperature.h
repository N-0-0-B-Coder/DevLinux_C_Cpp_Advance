#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "gpios/gpio.h"
#include "config.h"
#include "systime/systime.h"
#include "log/log.h"

typedef enum {
    TEMPERATURE_ERROR = -1,
    TEMPERATURE_ERROR_NONE
} temp_sensor_status_t;

typedef struct {
    gpio_num_t data_pin;      // GPIO pin connected to the sensor data line
    float last_value;         // Last read temperature value
} temp_sensor_t;

/**
 * @brief Initialize the temperature sensor
 * 
 * @param sensor [in,out] Pointer to the temperature sensor structure
 * @param data_pin [in] GPIO pin connected to the sensor data line
 * @return temp_sensor_status_t 
 */
temp_sensor_status_t temp_sensor_init(temp_sensor_t *sensor, gpio_num_t data_pin);

/**
 * @brief Read temperature from the sensor
 * 
 * @param sensor [in, out] Pointer to the temperature sensor structure
 * @param temperature [out] Pointer to store the read temperature value
 * @return temp_sensor_status_t 
 */
temp_sensor_status_t temp_sensor_read(temp_sensor_t *sensor, float *temperature);

void temp_value_decrease(void);

#ifdef __cplusplus
}
#endif
#endif // _TEMPERATURE_H_