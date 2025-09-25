#include "auto.h"

static const char *TAG = "AUTO_MODE";

float temperature = 0.0f;
float moisture = 0.0f;

// Timing Variables in seconds
uint16_t pump_start_time = 0;
uint16_t pump_end_time = 0;
uint16_t pump_duration = 0;
uint16_t pump_cooldown = PUMP_COOLDOWN;

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

void auto_mode_run(temp_sensor_t *temp_sensor, moisture_sensor_t *moisture_sensor, pump_t *pump) {
    // Get pump flow rate
    pump_flow_rate = pump_get_flow_rate(pump);
    if (pump_flow_rate <= PUMP_MIN_FLOW_RATE) {
        LOG_W(TAG, "Pump flow rate low, please check the pump");
        if (led_on(LED_RED_PIN)) {
            LOG_E(TAG, "Failed to turn on RED LED");
        }
        return;
    }
    else {
        if (is_led_on(LED_RED_PIN)) {
            if (led_off(LED_RED_PIN)) {
                LOG_E(TAG, "Failed to turn off RED LED");
                return;
            }
        }
    }

    // Calculate pump duration based on flow rate (in seconds)
    pump_duration = (uint16_t)((PUMP_MAX_FLOW_RATE / pump_flow_rate) * 60);

    // Read Temperature
    if (temp_sensor_read(temp_sensor, &temperature) == TEMPERATURE_ERROR_NONE) {
        LOG_I(TAG, "Current Temperature: %.2f C", temperature);
    } else {
        LOG_E(TAG, "Failed to read Temperature");
    }

    // Read Moisture
    if (moisture_sensor_read(moisture_sensor, &moisture) == MOISTURE_ERROR_NONE) {
        LOG_I(TAG, "Current Moisture: %.2f %%", moisture);
    } else {
        LOG_E(TAG, "Failed to read Moisture");
    }

    pump_end_time = get_time_s();
    if (pump->state == PUMP_STATE_ON && (pump_end_time - pump_start_time >= pump_duration)) {
        pump_set_state(pump, PUMP_STATE_OFF);
        led_off(LED_YELLOW_PIN);
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

    if (temperature > 60.0f || moisture < 30.0f) {
        if (pump_lock) {
            LOG_I(TAG, "Moisture or Temperature levels critical but pump is in cooldown");
            led_blink(LED_RED_PIN, 200, 3);
        } else {
            pump_set_state(pump, PUMP_STATE_ON);
            LOG_I(TAG, "Temperature: %.2f C, Moisture: %.2f %% - Pump ON", temperature, moisture);
            pump_start_time = get_time_s();
            led_on(LED_YELLOW_PIN);
        }
    } else if (temperature <= 30.0f && moisture >= 70.0f) {
        pump_state_t pump_state = pump_get_state(pump);
        if (pump_state == PUMP_STATE_ON) {
            pump_set_state(pump, PUMP_STATE_OFF);
            led_off(LED_YELLOW_PIN);
            LOG_I(TAG, "Temperature and Moisture optimal - Pump OFF");
            pump_lock = true;
            pump_start_time = get_time_s(); // Reset start time for cooldown
        }
    }

    // Wait before next reading
    delay_ms(SENSOR_READ_INTERVAL_MS);
}