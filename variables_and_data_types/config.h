#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Logging Configuration
#define LOG_LEVEL                   LOG_LEVEL_DEBUG

// GPIO Pin Definitions
#define LED_GREEN_PIN               GPIO0
#define LED_YELLOW_PIN              GPIO1
#define LED_RED_PIN                 GPIO2
#define BUTTON_TOGGLE_AUTO_PIN      GPIO3
#define BUTTON_MANUAL_ACTIVE_PIN    GPIO4
#define TEMP_SENSOR_PIN             GPIO5
#define MOISTURE_SENSOR_PIN         GPIO6
#define PUMP_PIN                    GPIO7

// Sensor Configuration
#define SENSOR_READ_INTERVAL_MS     60000

// Pump Configuration
#define PUMP_COOLDOWN               120 // seconds
#define PUMP_MIN_FLOW_RATE          0.5f // liters per minute
#define PUMP_MAX_FLOW_RATE          5.0f // liters per minute

#ifdef __cplusplus
}
#endif

#endif // __CONFIG_H__
