#ifndef _HUMIDITY_H_
#define _HUMIDITY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "gpios/gpio.h"
#include "config.h"
#include "log/log.h"

typedef enum {
    HUMIDITY_ERROR = -1,
    HUMIDITY_ERROR_NONE
} humidity_err_code_t;

typedef struct {
    gpio_num_t data_pin;      // GPIO pin connected to the sensor data line
    float last_value;   // Last read humidity value
} humidity_sensor_t;

/**
 * @brief Initialize the humidity sensor
 * 
 * @param sensor [in, out] Pointer to humidity_sensor_t structure
 * @param data_pin [in] GPIO pin connected to the sensor data line
 * @return humidity_err_code_t 
 */
humidity_err_code_t humidity_sensor_init(humidity_sensor_t *sensor, gpio_num_t data_pin);

/**
 * @brief Read humidity value from the sensor
 * 
 * @param sensor [in, out] Pointer to humidity_sensor_t structure
 * @param humidity [out] Pointer to store the read humidity value
 * @return humidity_err_code_t 
 */
humidity_err_code_t humidity_sensor_read(humidity_sensor_t *sensor, float *humidity);

void humidity_value_increase(void);

#ifdef __cplusplus
}
#endif
#endif // _HUMIDITY_H_