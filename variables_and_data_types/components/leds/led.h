#ifndef _LED_H_
#define _LED_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "gpios/gpio.h"
#include "log/log.h"

#ifdef _WIN32
#include <windows.h>
#else
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif
#include <time.h>
#endif

#define LED_ACTIVE_STATE GPIO_STATE_HIGH
#define LED_INACTIVE_STATE GPIO_STATE_LOW

typedef enum {
    LED_ERROR = -1,
    LED_ERROR_NONE
}led_err_code_t;

/**
 * @brief Initialize the LED on the specified pin
 * 
 * @param led_pin [in] The GPIO pin number where the LED is connected
 * 
 * @return err_code_t 0 if successful, error code otherwise
 */
led_err_code_t led_init(uint8_t led_pin);

/**
 * @brief Turn the LED on
 * 
 * @param led_pin [in] The GPIO pin number where the LED is connected
 */
led_err_code_t led_on(uint8_t led_pin);

/**
 * @brief Turn the LED off
 * 
 * @param led_pin [in] The GPIO pin number where the LED is connected
 */
led_err_code_t led_off(uint8_t led_pin);

/**
 * @brief Check if the LED is currently on
 * 
 * @param led_pin [in] The GPIO pin number where the LED is connected
 * @return true if the LED is on, false otherwise
 */
bool is_led_on(uint8_t led_pin);

/**
 * @brief Toggle the LED state
 * 
 * @param led_pin [in] The GPIO pin number where the LED is connected
 */
led_err_code_t led_toggle(uint8_t led_pin);

/**
 * @brief Blink the LED a specified number of times with a given interval
 * 
 * @param led_pin [in] The GPIO pin number where the LED is connected
 * @param interval_ms [in] The interval in milliseconds between toggles
 * @param times [in] The number of times to blink the LED
 * 
 * @return err_code_t 0 if successful, error code otherwise
 */
led_err_code_t led_blink(uint8_t led_pin, uint16_t interval_ms, uint8_t times);

#ifdef __cplusplus
}
#endif

#endif // _LED_H_