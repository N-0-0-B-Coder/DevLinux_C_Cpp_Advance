#include "auto.h"

static const char *TAG = "AUTO_MODE";

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

    // Blink yellow LED if both green and yellow are on
    if (green_on && yellow_on) {
        if (led_blink(LED_YELLOW_PIN, 500, 3) == LED_ERROR_NONE) {
            LOG_I(TAG, "YELLOW LED BLINK");
        }
        else {
            LOG_E(TAG, "Failed to blink YELLOW LED");
        }
    }
    else {
        LOG_I(TAG, "LED: \033[0m\033[0m[\033[1;32m%s|\033[1;33m%s|\033[1;31m%s]", green_on ? "ON\033[0m" : "\033[0mOFF", yellow_on ? "ON\033[0m" : "\033[0mOFF", red_on ? "ON\033[0m" : "\033[0mOFF");
    }
}

static void update_leds(const system_state_t *state) {
    switch (state->current_status) {
        case ERROR_FLOW_LOW:
        case ERROR_ACTIVE:
            apply_led_pattern(false, false, true);
            break;
        case WATERING:
            apply_led_pattern(false, true, false);
            break;
        case TEMP_ALERT:
        case MOISTURE_ALERT:
            apply_led_pattern(true, true, false);
            break;
        default:
            apply_led_pattern(true, false, false);
            break;
    }
}

void auto_mode_run(temp_sensor_t *temp_sensor, moisture_sensor_t *moisture_sensor, pump_t *pump) {
    system_config_t *config = &g_system_config;
    system_state_t *state = &g_system_state;

    state->mode = MODE_AUTO;

    float temperature = 0.0f;
    float moisture = 0.0f;

    // When calling the read functions, the temperature and moisture values will be simulated to change
    bool temperature_ok = (temp_sensor_read(temp_sensor, &temperature) == TEMPERATURE_ERROR_NONE);
    bool moisture_ok = (moisture_sensor_read(moisture_sensor, &moisture) == MOISTURE_ERROR_NONE);

    if (temperature_ok) {
        state->last_temperature_c = temperature;
        LOG_I(TAG, "Current Temperature: %.2f C", temperature);
    } else {
        LOG_E(TAG, "Failed to read Temperature");
        state->current_status = ERROR_ACTIVE;
        goto mode_end;
    }

    if (moisture_ok) {
        state->last_moisture_percent = moisture;
        LOG_I(TAG, "Current Moisture: %.2f %%", moisture);
    } else {
        LOG_E(TAG, "Failed to read Moisture");
        state->current_status = ERROR_ACTIVE;
        goto mode_end;
    }

    if (!temperature_ok || !moisture_ok) {
        LOG_I(TAG, "Sensor error detected");
        state->current_status = ERROR_ACTIVE;
        goto mode_end;
    }

    if (moisture < config->moisture_min_percent) {
        if (state->current_status == WATERING) {
            // Continue watering
        } else {
            state->current_status = MOISTURE_ALERT;
        }
    }
    if (temperature > config->max_temperature_c) {
        if (state->current_status == WATERING) {
            // Continue watering
        } else {
            state->current_status = TEMP_ALERT;
        }
    }

    float pump_flow_rate = pump_get_flow_rate(pump);
    if (pump_flow_rate <= PUMP_MIN_FLOW_RATE) {
        LOG_W(TAG, "Pump flow rate low (%.2f L/min); skipping watering", pump_flow_rate);
        state->current_status = ERROR_FLOW_LOW;
        if (pump_get_state(pump) != PUMP_STATE_OFF) {
            if (pump_set_state(pump, PUMP_STATE_OFF) != PUMP_ERROR_NONE) {
                LOG_E(TAG, "Failed to turn pump off after low flow warning");
                state->current_status = ERROR_ACTIVE;
            }
        }
        goto mode_end;
    }

    uint32_t now = get_time_s();

    if (state->pump_locked && (now - state->pump_locked_at_s >= config->pump_cooldown_s)) {
        state->pump_locked = false;
        LOG_I(TAG, "Pump cooldown complete, auto watering available");
    }

    // Handle watering state
    if (state->current_status == WATERING) {
        bool duration_elapsed = (now - state->pump_started_at_s) >= config->max_watering_duration_s;
        bool moisture_recovered = moisture >= DEFAULT_MOISTURE_GOOD_PERCENT;
        bool moisture_too_high = (moisture > config->moisture_max_percent);
        bool temperature_recovered = (temperature <= config->max_temperature_c);

        if (moisture_too_high) {
            LOG_W(TAG, "Moisture %.2f%% above %.2f%%", moisture, config->moisture_max_percent);
            state->current_status = NORMAL;
            if (pump_set_state(pump, PUMP_STATE_OFF) == PUMP_ERROR_NONE) {
                LOG_I(TAG, "Auto watering stopped (moisture too high)");
            } else {
                LOG_E(TAG, "Failed to stop pump after auto watering");
                state->current_status = ERROR_ACTIVE;
            }
        } else if (duration_elapsed) {
            LOG_I(TAG, "Auto watering stopped (max duration reached)");
            if (pump_set_state(pump, PUMP_STATE_OFF) == PUMP_ERROR_NONE) {
                state->current_status = NORMAL;
            } else {
                LOG_E(TAG, "Failed to stop pump after auto watering");
                state->current_status = ERROR_ACTIVE;
            }
            state->pump_locked = true;
            state->pump_locked_at_s = now;
        } else if (moisture_recovered && temperature_recovered) {
            LOG_I(TAG, "Auto watering stopped (conditions recovered)");
            if (pump_set_state(pump, PUMP_STATE_OFF) == PUMP_ERROR_NONE) {
                state->current_status = NORMAL;
            } else {
                LOG_E(TAG, "Failed to stop pump after auto watering");
                state->current_status = ERROR_ACTIVE;
            }
            state->pump_locked = true;
            state->pump_locked_at_s = now;
        } else {
            LOG_I(TAG, "Auto watering in progress...");
            if (pump_set_state(pump, PUMP_STATE_ON) == PUMP_ERROR_NONE) {
                // Need to call set_state to simulate increased humidity and decreased temperature
            } else {
                LOG_E(TAG, "Failed to maintain pump ON state during watering");
                state->current_status = ERROR_ACTIVE;
            }
        }
        goto mode_end;
    }

    // Handle non-watering states
    if (state->current_status != WATERING) {
        if (!state->pump_locked && (state->current_status == MOISTURE_ALERT || state->current_status == TEMP_ALERT)) {
            if (state->current_status == MOISTURE_ALERT) {
                LOG_W(TAG, "Moisture %.2f%% below %.2f%% - Pump ON", moisture, config->moisture_min_percent);
            } else if (state->current_status == TEMP_ALERT) {
                LOG_W(TAG, "Temperature %.2f C above %.2f C - Pump ON", temperature, config->max_temperature_c);
            }
            if (pump_set_state(pump, PUMP_STATE_ON) == PUMP_ERROR_NONE) {
                state->current_status = WATERING;
                state->pump_started_at_s = now;
            } else {
                LOG_E(TAG, "Failed to start pump for auto watering");
            }
        } else if (state->pump_locked && (state->current_status == MOISTURE_ALERT || state->current_status == TEMP_ALERT)) {
            LOG_W(TAG, "Pump is in cooldown, cannot auto water now");
        } else if (pump_get_state(pump) != PUMP_STATE_OFF) {
            if (pump_set_state(pump, PUMP_STATE_OFF) != PUMP_ERROR_NONE) {
                LOG_E(TAG, "Failed to turn pump off when not watering");
            }
        }
        goto mode_end;
    }

mode_end:
    update_leds(state);
    delay_ms(config->sensor_read_interval_ms);
}
