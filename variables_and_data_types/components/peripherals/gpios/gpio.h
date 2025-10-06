#ifndef _GPIO_H_
#define _GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "log/log.h"

/**
 * @brief GPIO Number Enumeration
 * 
 */
typedef enum {
	GPIO0 = 0,
	GPIO1,
	GPIO2,
	GPIO3,
	GPIO4,
	GPIO5,
	GPIO6,
	GPIO7,


	GPIO_MAX
} gpio_num_t;

/**
 * @brief GPIO Configuration Structure
 * 
 */
typedef enum {
	GPIO_INPUT = 0,
	GPIO_OUTPUT,
	GPIO_ALTERNATE,
	GPIO_ANALOG
} gpio_mode_t;

/**
 * @brief GPIO Output Type Enumeration
 * 
 */
typedef enum {
	GPIO_PUSH_PULL = 0,
	GPIO_OPEN_DRAIN
} gpio_output_type_t;

/**
 * @brief GPIO Speed Enumeration
 * 
 */
typedef enum {
	GPIO_LOW_SPEED = 0,
	GPIO_MEDIUM_SPEED,
	GPIO_HIGH_SPEED,
	GPIO_VERY_HIGH_SPEED
} gpio_speed_t;

/**
 * @brief GPIO Pull-Up/Pull-Down Enumeration
 * 
 */
typedef enum {
	GPIO_NO_PUPD = 0,
	GPIO_PULL_UP,
	GPIO_PULL_DOWN
} gpio_pull_ud_t;

/**
 * @brief GPIO Error Enumeration
 * 
 */
typedef enum {
	GPIO_ERROR_NO_TABLE = -5,
	GPIO_ERROR_CFG_NULL,
	GPIO_ERROR_INVALID_PIN,
	GPIO_ERROR_NOT_INITIALIZED,
	GPIO_ERROR_UNKNOWN,
	GPIO_ERROR_NONE
} gpio_err_t;

/**
 * @brief GPIO State Enumeration
 * 
 */
typedef enum {
	GPIO_STATE_ERROR = -1,
	GPIO_STATE_LOW,
	GPIO_STATE_HIGH
} gpio_state_t;

/**
 * @brief GPIO Configuration Structure
 * 
 */
typedef struct {
        uint8_t mode:2;
        uint8_t output_type:1;
        uint8_t speed:2;
        uint8_t pull_ud:2;
        uint8_t reversed:1;
} gpio_cfg_t;

/**
 * @brief GPIO Pin Structure
 * 
 */
typedef struct {
	uint8_t is_initialized;
	gpio_num_t gpio;
	gpio_state_t state;
	gpio_cfg_t cfg;
} gpio_t;

extern gpio_t gpio_table[8];

/**
 * @brief GPIO Function Prototypes
 * 
 * @param gpio [in] GPIO number
 * @param gpio_cfg [in] Pointer to GPIO configuration structure
 * 
 * @return gpio_err_t 0 on success, negative error code on failure
 */
gpio_err_t gpio_init(gpio_num_t gpio, gpio_cfg_t *gpio_cfg);

/**
 * @brief Set the state of a GPIO pin
 * 
 * @param gpio [in] GPIO number
 * @param state [in] Desired state (GPIO_LOW or GPIO_HIGH)
 * 
 * @return gpio_err_t 0 on success, negative error code on failure
 */
gpio_err_t gpio_set(gpio_num_t gpio, gpio_state_t state);

/**
 * @brief Read the state of a GPIO pin
 * 
 * @param gpio [in] GPIO number
 * 
 * @return gpio_state_t GPIO_STATE_ERROR If error. Otherwise current state of the GPIO pin (GPIO_STATE_LOW or GPIO_STATE_HIGH)
 */
gpio_state_t gpio_read(gpio_num_t gpio);

#ifdef __cplusplus
}
#endif

#endif //_GPIO_H_
