#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define LOG_LEVEL                   LOG_LEVEL_DEBUG

#define LED_GREEN_PIN               GPIO0
#define LED_YELLOW_PIN              GPIO1
#define LED_RED_PIN                 GPIO2
#define BUTTON_TOGGLE_AUTO_PIN      GPIO3
#define BUTTON_MANUAL_ACTIVE_PIN    GPIO4
#define TEMP_SENSOR_PIN             GPIO5
#define HUMIDITY_SENSOR_PIN         GPIO6
#define PUMP_PIN                    GPIO7

#define SENSOR_READ_INTERVAL_MS      60000

#ifdef __cplusplus
}
#endif

#endif // __CONFIG_H__
