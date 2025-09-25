#include "auto.h"

static const char *TAG = "AUTO_MODE";

float temperature = 0.0f;
float humidity = 0.0f;

// Timing Variables in seconds
uint16_t pump_start_time = 0;
uint16_t pump_end_time = 0;
uint16_t pump_duration = 0;
uint16_t pump_cooldown = 120;

bool pump_lock = false;
float pump_flow_rate = 0.0f;

void delay_ms(unsigned int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    struct timespec req = {0};
    req.tv_sec = ms / 1000;
    req.tv_nsec = (ms % 1000) * 1000000L;
    nanosleep(&req, NULL);
#endif
}

uint16_t get_time_s(void) {
#ifdef _WIN32
    return (uint16_t)(GetTickCount64() / 1000);  // Windows: ms since system start
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts); // monotonic clock, not affected by system time changes
    return (uint16_t)ts.tv_sec;
#endif
}

void auto_mode_run(temp_sensor_t *temp_sensor, humidity_sensor_t *humidity_sensor, pump_t *pump) {
    // Get pump flow rate
    pump_flow_rate = pump_get_flow_rate(pump);
    if (pump_flow_rate <= 0.0f) {
        LOG_W(TAG, "Pump flow rate is %.2f L/min; skipping auto mode cycle", pump_flow_rate);
        return;
    }
    pump_duration = (uint16_t)((5.0f / pump_flow_rate) * 60); // duration to pump based on flow rate in seconds

    // Read Temperature
    if (temp_sensor_read(temp_sensor, &temperature) == TEMPERATURE_ERROR_NONE) {
        LOG_I(TAG, "Current Temperature: %.2f C", temperature);
    } else {
        LOG_E(TAG, "Failed to read Temperature");
    }

    // Read Humidity
    if (humidity_sensor_read(humidity_sensor, &humidity) == HUMIDITY_ERROR_NONE) {
        LOG_I(TAG, "Current Humidity: %.2f %%", humidity);
    } else {
        LOG_E(TAG, "Failed to read Humidity");
    }

    pump_end_time = get_time_s();
    if (pump->state == PUMP_STATE_ON && (pump_end_time - pump_start_time >= pump_duration)) {
        pump_set_state(pump, PUMP_STATE_OFF);
        LOG_I(TAG, "Pump AUTO OFF after interval");
        pump_lock = true;
        pump_start_time = get_time_s(); // Reset start time for cooldown
    }

    // Handle pump lock and cooldown
    if (pump_lock) {
        if (pump_end_time - pump_start_time >= pump_cooldown) {
            pump_lock = false;
            LOG_I(TAG, "Pump cooldown period ended, can activate again");
        }
    }

    if (temperature > 60.0f || humidity < 30.0f) {
        if (pump_lock) {
            LOG_I(TAG, "Moisture or Temperature levels critical but pump is in cooldown");
            led_blink(LED_RED_PIN, 200, 3);
        } else {
            pump_set_state(pump, PUMP_STATE_ON);
            LOG_I(TAG, "Temperature: %.2f C, Humidity: %.2f %% - Pump ON", temperature, humidity);
            pump_start_time = get_time_s();
        }
    } else if (temperature <= 30.0f && humidity >= 70.0f) {
        pump_set_state(pump, PUMP_STATE_OFF);
        LOG_I(TAG, "Temperature: %.2f C, Humidity: %.2f %% - Pump OFF", temperature, humidity);
        pump_lock = true;
        pump_start_time = get_time_s(); // Reset start time for cooldown
    }

    // Wait before next reading
    delay_ms(SENSOR_READ_INTERVAL_MS);
}