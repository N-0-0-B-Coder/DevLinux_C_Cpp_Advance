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
    config->pump_cooldown_s = PUMP_COOLDOWN_S;
    config->sensor_read_interval_ms = SENSOR_READ_INTERVAL_MS;

    LOG_I(TAG, "System configuration initialized with default values");
}

void system_state_init(system_state_t *state, system_mode_t mode) {
    if (state == NULL) {
        return;
    }

    memset(state, 0, sizeof(*state));

    if (mode != MODE_AUTO && mode != MODE_MANUAL) {
        mode = MODE_AUTO; // Default to AUTO if invalid mode
    }
    else {
        state->mode = mode;
        if (mode == MODE_AUTO) {
            button_set_state(BUTTON_TOGGLE_AUTO_PIN, BUTTON_STATE_PRESSED);
            LOG_I(TAG, "Button for toggling AUTO/MANUAL mode set to AUTO");
        }
        else {
            button_set_state(BUTTON_TOGGLE_AUTO_PIN, BUTTON_STATE_RELEASED);
            LOG_I(TAG, "Button for toggling AUTO/MANUAL mode set to MANUAL");
        }
    }
    state->pump_locked = false;
    state->pump_started_at_s = 0U;
    state->pump_locked_at_s = 0U;
    state->current_status = NORMAL;
    state->last_temperature_c = 0.0f;
    state->last_moisture_percent = 0.0f;

    LOG_I(TAG, "System state initialized in %s mode", mode == MODE_AUTO ? "AUTO" : "MANUAL");
}

int init_system(temp_sensor_t *temp_sensor, moisture_sensor_t *moisture_sensor, pump_t *pump) {
    LOG_I(TAG, "System initializing...");

    // Initialize GPIOs for LEDs
    if (led_init(LED_GREEN_PIN) != LED_ERROR_NONE) goto error;
    if (led_init(LED_YELLOW_PIN) != LED_ERROR_NONE) goto error;
    if (led_init(LED_RED_PIN) != LED_ERROR_NONE) goto error;

    LOG_I(TAG, "LEDs initialized");

    // Initialize Temperature Sensor
    if (temp_sensor_init(temp_sensor, TEMP_SENSOR_PIN) != TEMPERATURE_ERROR_NONE) goto error;
    // Initialize Moisture Sensor
    if (moisture_sensor_init(moisture_sensor, MOISTURE_SENSOR_PIN) != MOISTURE_ERROR_NONE) goto error;

    LOG_I(TAG, "Sensors initialized");

    // Initialize Pumps
    if (pump_init(pump, 1, PUMP_PIN) != PUMP_ERROR_NONE) goto error;
    pump_set_flow_rate(pump, 1.5f); // Set flow rate to 1.5 L/min

    LOG_I(TAG, "Pump initialized");

    // Initialize GPIOs for Buttons
    if (button_init(BUTTON_TOGGLE_AUTO_PIN) != BUTTON_ERROR_NONE) goto error;
    LOG_I(TAG, "Button for toggling AUTO/MANUAL mode initialized");
    if (button_init(BUTTON_MANUAL_PUMP_PIN) != BUTTON_ERROR_NONE) goto error;
    LOG_I(TAG, "Button for manual pump control initialized");

    // Initialize System Config and State
    system_config_init(&g_system_config);
    system_state_init(&g_system_state, DEFAULT_MODE);

    LOG_I(TAG, "System initialized successfully");

    // Set initial LED states
    if (led_on(LED_GREEN_PIN) != LED_ERROR_NONE) goto error;
    if (led_off(LED_YELLOW_PIN) != LED_ERROR_NONE) goto error;
    if (led_off(LED_RED_PIN) != LED_ERROR_NONE) goto error;

    return 0;

error:
    LOG_E(TAG, "System initialization failed");
    return -1;
}