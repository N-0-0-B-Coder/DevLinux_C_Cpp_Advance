#include "init.h"

static const char *TAG = "INIT_MODE";

int init_system(temp_sensor_t *temp_sensor, humidity_sensor_t *humidity_sensor, pump_t *pump) {
    LOG_I(TAG, "System initializing...");

    // Initialize GPIOs for LEDs
    if (led_init(LED_GREEN_PIN) != LED_ERROR_NONE) goto error;
    if (led_init(LED_YELLOW_PIN) != LED_ERROR_NONE) goto error;
    if (led_init(LED_RED_PIN) != LED_ERROR_NONE) goto error;

    // Initialize Temperature Sensor
    if (temp_sensor_init(temp_sensor, TEMP_SENSOR_PIN) != TEMPERATURE_ERROR_NONE) goto error;

    // Initialize Humidity Sensor
    if (humidity_sensor_init(humidity_sensor, HUMIDITY_SENSOR_PIN) != HUMIDITY_ERROR_NONE) goto error;

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