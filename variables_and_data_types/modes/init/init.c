#include "init.h"

static const char *TAG = "INIT_MODE";

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

int init_system(temp_sensor_t *temp_sensor, moisture_sensor_t *moisture_sensor, pump_t *pump) {
    LOG_I(TAG, "System initializing...");

    system_config_init(&g_system_config);
    system_state_init(&g_system_state, MODE_AUTO);

    // Initialize GPIOs for LEDs
    if (led_init(LED_GREEN_PIN) != LED_ERROR_NONE) goto error;
    if (led_init(LED_YELLOW_PIN) != LED_ERROR_NONE) goto error;
    if (led_init(LED_RED_PIN) != LED_ERROR_NONE) goto error;

    // Initialize Temperature Sensor
    if (temp_sensor_init(temp_sensor, TEMP_SENSOR_PIN) != TEMPERATURE_ERROR_NONE) goto error;

    // Initialize Moisture Sensor
    if (moisture_sensor_init(moisture_sensor, MOISTURE_SENSOR_PIN) != MOISTURE_ERROR_NONE) goto error;

    // Initialize Pumps
    if (pump_init(pump, 1, PUMP_PIN) != PUMP_ERROR_NONE) goto error;
    pump_set_flow_rate(pump, 1.5f); // Set flow rate to 1.5 L/min

    // Initialize GPIOs for Buttons
    if (button_init(BUTTON_TOGGLE_AUTO_PIN) != BUTTON_ERROR_NONE) goto error;
    if (button_init(BUTTON_MANUAL_ACTIVE_PIN) != BUTTON_ERROR_NONE) goto error;

    LOG_I(TAG, "System initialized successfully");

    // Set system to AUTO mode by default
    if (button_set_state(BUTTON_TOGGLE_AUTO_PIN, BUTTON_STATE_PRESSED) != BUTTON_ERROR_NONE) goto error;

    // Set initial LED states
    if (led_on(LED_GREEN_PIN) != LED_ERROR_NONE) goto error;
    if (led_off(LED_YELLOW_PIN) != LED_ERROR_NONE) goto error;
    if (led_off(LED_RED_PIN) != LED_ERROR_NONE) goto error;

    return 0;

error:
    LOG_E(TAG, "System initialization failed");
    return -1;
}