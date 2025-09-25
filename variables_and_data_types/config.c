#include "config.h"

#include <string.h>

system_config_t g_system_config;
system_state_t g_system_state;

void system_config_init(system_config_t *config) {
    if (config == NULL) {
        return;
    }

    config->moisture_min_percent = DEFAULT_MOISTURE_MIN_PERCENT;
    config->moisture_max_percent = DEFAULT_MOISTURE_MAX_PERCENT;
    config->max_temperature_c = DEFAULT_MAX_TEMPERATURE_C;
    config->max_watering_duration_s = DEFAULT_MAX_WATERING_DURATION_S;
    config->manual_watering_duration_s = DEFAULT_MANUAL_WATERING_DURATION_S;
    config->pump_cooldown_s = PUMP_COOLDOWN;
    config->sensor_read_interval_ms = SENSOR_READ_INTERVAL_MS;
}

void system_state_init(system_state_t *state, system_mode_t default_mode) {
    if (state == NULL) {
        return;
    }

    memset(state, 0, sizeof(*state));
    state->mode = default_mode;
    state->pump_started_at_s = 0U;
    state->pump_locked_at_s = 0U;
}
