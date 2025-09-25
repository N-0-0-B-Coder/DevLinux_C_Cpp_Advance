#include "manual.h"

static const char *TAG = "MANUAL_MODE";

static void delay_ms(unsigned int ms) {
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

void manual_mode_run(pump_t *pump) {
    system_config_t *config = &g_system_config;
    system_state_t *state = &g_system_state;
    uint32_t now = get_time_s();

    state->mode = MODE_MANUAL;
    state->error_active = false;

    if (state->pump_locked && (now - state->pump_locked_at_s >= config->pump_cooldown_s)) {
        state->pump_locked = false;
        LOG_I(TAG, "Pump cooldown period ended; manual watering available");
    }

    if (state->watering) {
        if ((now - state->pump_started_at_s) >= config->manual_watering_duration_s) {
            if (pump_set_state(pump, PUMP_STATE_OFF) == PUMP_ERROR_NONE) {
                LOG_I(TAG, "Manual watering cycle finished");
                state->watering = false;
            } else {
                LOG_E(TAG, "Failed to stop pump after manual watering");
            }
            state->pump_locked = true;
            state->pump_locked_at_s = now;
        }
    } else {
        if (button_get_state(BUTTON_MANUAL_ACTIVE_PIN) == BUTTON_STATE_PRESSED) {
            if (!state->pump_locked) {
                if (pump_set_state(pump, PUMP_STATE_ON) == PUMP_ERROR_NONE) {
                    LOG_I(TAG, "Manual watering started");
                    state->watering = true;
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
            state->watering = false;
        }
    }

    if (state->watering) {
        apply_led_pattern(false, true, false);
    } else if (state->pump_locked) {
        apply_led_pattern(false, false, true);
    } else {
        apply_led_pattern(true, false, false);
    }

    state->moisture_alert = false;
    delay_ms(100);
}
