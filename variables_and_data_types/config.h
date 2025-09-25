#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Logging Configuration
#define LOG_LEVEL                   LOG_LEVEL_INFO

// Default Mode
#define DEFAULT_MODE                MODE_AUTO

// GPIO Pin Definitions
#define LED_GREEN_PIN               GPIO0
#define LED_YELLOW_PIN              GPIO1
#define LED_RED_PIN                 GPIO2
#define BUTTON_TOGGLE_AUTO_PIN      GPIO3
#define BUTTON_MANUAL_PUMP_PIN      GPIO4
#define TEMP_SENSOR_PIN             GPIO5
#define MOISTURE_SENSOR_PIN         GPIO6
#define PUMP_PIN                    GPIO7

// Sensor Configuration
#define SENSOR_READ_INTERVAL_MS     20000

// Pump Configuration
#define PUMP_COOLDOWN_S             60 // seconds
#define PUMP_MIN_FLOW_RATE          0.5f // liters per minute
#define PUMP_MAX_FLOW_RATE          5.0f // liters per minute

// Default Auto/Manual Mode
#define DEFAULT_MOISTURE_MIN_PERCENT        35.0f
#define DEFAULT_MOISTURE_MAX_PERCENT        65.0f
#define DEFAULT_MAX_TEMPERATURE_C           55.0f
#define DEFAULT_MAX_WATERING_DURATION_S     30
#define DEFAULT_MANUAL_WATERING_DURATION_S  20

typedef enum {
    MODE_AUTO = 0,
    MODE_MANUAL
} system_mode_t;

typedef enum {
    NORMAL,
    WATERING,
    MOISTURE_ALERT,
    TEMP_ALERT,
    ERROR_ACTIVE,
    ERROR_FLOW_LOW
} system_status_t;

typedef struct {
    float moisture_min_percent;
    float moisture_max_percent;
    float max_temperature_c;
    uint16_t max_watering_duration_s;
    uint16_t manual_watering_duration_s;
    uint16_t pump_cooldown_s;
    uint32_t sensor_read_interval_ms;
} system_config_t;

typedef struct {
    system_mode_t mode;
    float last_temperature_c;
    float last_moisture_percent;
    system_status_t current_status;
    bool pump_locked;
    uint32_t pump_started_at_s;
    uint32_t pump_locked_at_s;
} system_state_t;

extern system_config_t g_system_config;
extern system_state_t g_system_state;

#ifdef __cplusplus
}
#endif

#endif // __CONFIG_H__
