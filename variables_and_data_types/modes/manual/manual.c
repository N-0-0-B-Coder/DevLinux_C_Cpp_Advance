#include "manual.h"

static const char *TAG = "MANUAL_MODE";

static void apply_led_pattern(bool green_on, bool yellow_on, bool red_on) {
    if ((green_on ? led_on(LED_GREEN_PIN) : led_off(LED_GREEN_PIN)) == LED_ERROR_NONE) {
        LOG_I(TAG, "GREEN LED %s", green_on ? "ON" : "OFF");
    }
    else {
        LOG_E(TAG, "Failed to update GREEN LED");
    }
    if ((yellow_on ? led_on(LED_YELLOW_PIN) : led_off(LED_YELLOW_PIN)) == LED_ERROR_NONE) {
        LOG_I(TAG, "YELLOW LED %s", yellow_on ? "ON" : "OFF");
    }
    else {
        LOG_E(TAG, "Failed to update YELLOW LED");
    }
    if ((red_on ? led_on(LED_RED_PIN) : led_off(LED_RED_PIN)) == LED_ERROR_NONE) {
        LOG_I(TAG, "RED LED %s", red_on ? "ON" : "OFF");
    }
    else {
        LOG_E(TAG, "Failed to update RED LED");
    }
    if (green_on && yellow_on) {
        if (led_blink(LED_YELLOW_PIN, 500, 3) == LED_ERROR_NONE) {
            LOG_I(TAG, "YELLOW LED BLINK");
        }
        else {
            LOG_E(TAG, "Failed to blink YELLOW LED");
        }
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
        case MOISTURE_ALERT:
            apply_led_pattern(true, true, false);
            break;
        default:
            apply_led_pattern(true, false, false);
            break;
    }
}

void manual_mode_run(pump_t *pump) {
    system_config_t *config = &g_system_config;
    system_state_t *state = &g_system_state;
    uint32_t now = get_time_s();

    state->mode = MODE_MANUAL;

    if (state->pump_locked && (now - state->pump_locked_at_s >= config->pump_cooldown_s)) {
        state->pump_locked = false;
        LOG_I(TAG, "Pump cooldown period ended; manual watering available");
    }

    if (state->current_status == WATERING) {
        if (button_get_state(BUTTON_MANUAL_PUMP_PIN) == BUTTON_STATE_RELEASED) {
            LOG_I(TAG, "Manual watering button released; stopping pump");
        } else {
            if ((now - state->pump_started_at_s) >= config->manual_watering_duration_s) {
                LOG_I(TAG, "Manual watering duration elapsed; stopping pump");
            }
            else {
                LOG_I(TAG, "Manual watering in progress...");
                if (pump_set_state(pump, PUMP_STATE_ON) == PUMP_ERROR_NONE) {
                    // Pump is already ON; continue watering
                } else {
                    LOG_E(TAG, "Failed to maintain pump ON state during manual watering");
                }
                return; // Continue watering; do not proceed to stop the pump
            }
        } 
        // Stop pump immediately after manual mode trigger
        if (pump_set_state(pump, PUMP_STATE_OFF) == PUMP_ERROR_NONE) {
            LOG_I(TAG, "Manual watering cycle finished");
            state->current_status = NORMAL;
        } else {
            LOG_E(TAG, "Failed to stop pump after manual watering");
            state->current_status = ERROR_ACTIVE;
            update_leds(state);
            return;
        }
        state->current_status = NORMAL;
        state->pump_started_at_s = 0;
        state->pump_locked = true;
        state->pump_locked_at_s = now;
        update_leds(state);
    } else {
        if ((state->current_status == NORMAL) && (button_get_state(BUTTON_MANUAL_PUMP_PIN) == BUTTON_STATE_PRESSED)) {
            if (!state->pump_locked) {
                if (pump_set_state(pump, PUMP_STATE_ON) == PUMP_ERROR_NONE) {
                    LOG_I(TAG, "Manual watering started");
                    state->current_status = WATERING;
                    state->pump_started_at_s = now;
                } else {
                    LOG_E(TAG, "Failed to start pump for manual watering");
                }
            } else {
                LOG_W(TAG, "Manual watering requested but pump is cooling down");
            }
        } else {
            if (pump_get_state(pump) != PUMP_STATE_OFF) {
                if (pump_set_state(pump, PUMP_STATE_OFF) != PUMP_ERROR_NONE) {
                    LOG_E(TAG, "Failed to turn pump off while idle in manual mode");
                }
            }
            state->current_status = NORMAL;
        }
    }
}
