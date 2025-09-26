#ifndef _PUMP_H_
#define _PUMP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "gpios/gpio.h"
#include "config.h"
#include "systime/systime.h"
#include "log/log.h"

typedef enum {
    PUMP_STATE_ERROR = -1,
    PUMP_STATE_OFF,
    PUMP_STATE_ON
} pump_state_t;

typedef enum {
    PUMP_ERROR_NULL_ARG = -1,
    PUMP_ERROR_NONE
}pump_err_code_t;

typedef struct {
    uint8_t id;
    gpio_num_t control_pin;
    pump_state_t state;
    float flow_rate; // in liters per minute
} pump_t;

/**
 * @brief Initialize the pump
 * 
 * @param pump [in, out] Pointer to pump structure
 * @param id [in] Pump ID
 * @param control_pin [in] GPIO pin used to control the pump
 * @return pump_err_code_t 
 */
pump_err_code_t pump_init(pump_t *pump, uint8_t id, gpio_num_t control_pin);

/**
 * @brief Set the pump state
 * 
 * @param pump [in, out] Pointer to pump structure
 * @param state [in] Desired pump state
 * @return pump_err_code_t 
 */
pump_err_code_t pump_set_state(pump_t *pump, pump_state_t state);

/**
 * @brief Get the current pump state
 * 
 * @param pump [in] Pointer to pump structure
 * @return pump_state_t Current pump state
 */
pump_state_t pump_get_state(const pump_t *pump);

/**
 * @brief Set the pump flow rate
 * 
 * @param pump [in, out] Pointer to pump structure
 * @param flow_rate [in] Desired flow rate in liters per minute
 * @return pump_err_code_t 
 */
pump_err_code_t pump_set_flow_rate(pump_t *pump, float flow_rate);

/**
 * @brief Get the current pump flow rate
 * 
 * @param pump [in] Pointer to pump structure
 * @return float Current flow rate in liters per minute
 */
float pump_get_flow_rate(const pump_t *pump);

#ifdef __cplusplus
}
#endif
#endif // _PUMP_H_