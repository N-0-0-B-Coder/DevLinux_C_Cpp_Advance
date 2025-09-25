#include "auto.h"

static const char *TAG = "AUTO_MODE";

static void delay_ms(uint32_t ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    struct timespec req = {0};
    req.tv_sec = ms / 1000U;
    req.tv_nsec = (ms % 1000U) * 1000000UL;
    nanosleep(&req, NULL);
#endif
}

static uint32_t get_time_s(void) {
#ifdef _WIN32
    return (uint32_t)(GetTickCount64() / 1000ULL);
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint32_t)ts.tv_sec;
#endif
}

static void apply_led_pattern(bool green_on, bool yellow_on, bool red_on) {
    if ((green_on ? led_on(LED_GREEN_PIN) : led_off(LED_GREEN_PIN)) != LED_ERROR_NONE) {
        LOG_E(TAG, "Failed to update GREEN LED");
    }
    if ((yellow_on ? led_on(LED_YELLOW_PIN) : led_off(LED_YELLOW_PIN)) != LED_ERROR_NONE) {
        LOG_E(TAG, "Failed to update YELLOW LED");
    }
    if ((red_on ? led_on(LED_RED_PIN) : led_off(LED_RED_PIN)) != LED_ERROR_NONE) {
        LOG_E(TAG, "Failed to update RED LED");
    }
}

static void update_leds(const system_state_t *state) {
    if (state->error_active) {
        apply_led_pattern(false, false, true);
    } else if (state->watering) {
        apply_led_pattern(false, true, false);
    } else if (state->moisture_alert) {
        apply_led_pattern(false, false, true);
    } else {
        apply_led_pattern(true, false, false);
    }
}

void auto_mode_run(temp_sensor_t *temp_sensor, moisture_sensor_t *moisture_sensor, pump_t *pump) {
    system_config_t *config = &g_system_config;
    system_state_t *state = &g_system_state;

    state->mode = MODE_AUTO;

    float temperature = 0.0f;
    float moisture = 0.0f;
    bool temperature_ok = (temp_sensor_read(temp_sensor, &temperature) == TEMPERATURE_ERROR_NONE);
    bool moisture_ok = (moisture_sensor_read(moisture_sensor, &moisture) == MOISTURE_ERROR_NONE);

    if (temperature_ok) {
        state->last_temperature_c = temperature;
        LOG_I(TAG, "Current Temperature: %.2f C", temperature);
    } else {
        LOG_E(TAG, "Failed to read Temperature");
    }

    if (moisture_ok) {
        state->last_moisture_percent = moisture;
        LOG_I(TAG, "Current Moisture: %.2f %%", moisture);
    } else {
        LOG_E(TAG, "Failed to read Moisture");
    }

    if (!temperature_ok || !moisture_ok) {
        state->error_active = true;
        update_leds(state);
        delay_ms(config->sensor_read_interval_ms);
        return;
    }

    state->error_active = false;
    state->moisture_alert = (moisture < config->moisture_min_percent);

    float pump_flow_rate = pump_get_flow_rate(pump);
    if (pump_flow_rate <= PUMP_MIN_FLOW_RATE) {
        LOG_W(TAG, "Pump flow rate low (%.2f L/min); skipping watering", pump_flow_rate);
        state->error_active = true;
        if (pump_get_state(pump) != PUMP_STATE_OFF) {
            if (pump_set_state(pump, PUMP_STATE_OFF) != PUMP_ERROR_NONE) {
                LOG_E(TAG, "Failed to turn pump off after low flow warning");
            }
        }
        state->watering = false;
        update_leds(state);
        delay_ms(config->sensor_read_interval_ms);
        return;
    }

    if (temperature > config->max_temperature_c) {
        LOG_W(TAG, "Temperature %.2f C above configured max %.2f C", temperature, config->max_temperature_c);
    }

    uint32_t now = get_time_s();

    if (state->pump_locked && (now - state->pump_locked_at_s >= config->pump_cooldown_s)) {
        state->pump_locked = false;
        LOG_I(TAG, "Pump cooldown complete; auto watering available");
    }

    if (state->watering) {
        bool duration_elapsed = (now - state->pump_started_at_s) >= config->max_watering_duration_s;
        bool moisture_recovered = (moisture >= config->moisture_max_percent);
        if (duration_elapsed || moisture_recovered) {
            if (pump_set_state(pump, PUMP_STATE_OFF) == PUMP_ERROR_NONE) {
                LOG_I(TAG, "Auto watering stopped (%s)", duration_elapsed ? "max duration reached" : "moisture restored");
                state->watering = false;
            } else {
                LOG_E(TAG, "Failed to stop pump after watering interval");
            }
            state->pump_locked = true;
            state->pump_locked_at_s = now;
        }
    }

    if (!state->watering) {
        if (!state->pump_locked && state->moisture_alert) {
            if (pump_set_state(pump, PUMP_STATE_ON) == PUMP_ERROR_NONE) {
                LOG_I(TAG, "Moisture %.2f%% below %.2f%% - Pump ON", moisture, config->moisture_min_percent);
                state->watering = true;
                state->pump_started_at_s = now;
            } else {
                LOG_E(TAG, "Failed to start pump for auto watering");
            }
        } else if (pump_get_state(pump) != PUMP_STATE_OFF) {
            if (pump_set_state(pump, PUMP_STATE_OFF) != PUMP_ERROR_NONE) {
                LOG_E(TAG, "Failed to turn pump off when not watering");
            }
        }
    }

    update_leds(state);
    delay_ms(config->sensor_read_interval_ms);
}
