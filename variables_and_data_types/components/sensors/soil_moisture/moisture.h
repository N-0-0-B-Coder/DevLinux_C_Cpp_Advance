#ifndef _MOISTURE_H_
#define _MOISTURE_H_

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
    MOISTURE_ERROR = -1,
    MOISTURE_ERROR_NONE
} moisture_err_code_t;

typedef struct {
    gpio_num_t data_pin;      // GPIO pin connected to the sensor data line
    float last_value;   // Last read moisture value
} moisture_sensor_t;

/**
 * @brief Initialize the moisture sensor
 * 
 * @param sensor [in, out] Pointer to moisture_sensor_t structure
 * @param data_pin [in] GPIO pin connected to the sensor data line
 * 
 * @return moisture_err_code_t 0 if successful, error code otherwise
 */
moisture_err_code_t moisture_sensor_init(moisture_sensor_t *sensor, gpio_num_t data_pin);

/**
 * @brief Read moisture value from the sensor
 * 
 * @param sensor [in, out] Pointer to moisture_sensor_t structure
 * @param moisture [out] Pointer to store the read moisture value
 * 
 * @return moisture_err_code_t 0 if successful, error code otherwise 
 */
moisture_err_code_t moisture_sensor_read(moisture_sensor_t *sensor, float *moisture);

/**
 * @brief Simulate increase in moisture value based on pump rate
 * 
 * @param pump_rate [in] The rate at which the pump is adding moisture
 */
void moisture_value_increase(float pump_rate);

#ifdef __cplusplus
}
#endif
#endif // _MOISTURE_H_