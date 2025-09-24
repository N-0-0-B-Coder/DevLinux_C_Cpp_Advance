#ifndef _BUTTON_H_
#define _BUTTON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "gpios/gpio.h"
#include "log/log.h"

typedef enum {
    BUTTON_STATE_RELEASED = 0,
    BUTTON_STATE_PRESSED
} button_state_t;

typedef enum {
    BUTTON_ERROR_FAIL = -3,
    BUTTON_ERROR_INIT_FAIL,
    BUTTON_ERROR_READ_FAIL,
    BUTTON_ERROR_NONE
} button_err_t;

/**
 * @brief Initialize a button
 * 
 * @param button_pin [in] GPIO pin number where the button is connected
 * 
 * @return button_err_t 0 on success, error code on failure
 */
button_err_t button_init(uint8_t button_pin);

/**
 * @brief Get the current state of the button
 * 
 * @param button_pin [in] GPIO pin number where the button is connected
 * 
 * @return button_state_t Current state of the button (pressed or released)
 */
button_state_t button_get_state(uint8_t button_pin);

/**
 * @brief Set the state of the button (for simulation/testing purposes)
 * 
 * @param button_pin [in] GPIO pin number where the button is connected
 * @param state [in] Desired state to set (pressed or released)
 * 
 * @return button_err_t 0 on success, error code on failure
 */
button_err_t button_set_state(uint8_t button_pin, button_state_t state);

#ifdef __cplusplus
}
#endif

#endif // _BUTTON_H_