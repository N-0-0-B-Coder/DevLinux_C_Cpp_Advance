#include "moisture.h"

static const char *TAG = "MOISTURE_SENSOR";
static float moisture_simulated_value = 100.0f;

void moisture_value_increase(void) {
    float random_increase_value = 2.0f + ((float)rand() / (float)RAND_MAX) * (15.0f - 2.0f);
    moisture_simulated_value += random_increase_value;
    if (moisture_simulated_value > 100.0f) {
        moisture_simulated_value = 100.0f; // Cap at 100 %
    }
    delay_ms(50);
}

moisture_err_code_t moisture_sensor_init(moisture_sensor_t *sensor, gpio_num_t data_pin) {
    if (sensor == NULL) {
        LOG_E(TAG, "Sensor pointer is NULL");
        return MOISTURE_ERROR;
    }
    gpio_cfg_t sensor_cfg = {
        .mode = GPIO_INPUT,
        .output_type = GPIO_PUSH_PULL,
        .pull_ud = GPIO_PULL_UP,
        .speed = GPIO_LOW_SPEED,
        .reversed = 0
    };
    if (gpio_init(data_pin, &sensor_cfg) != GPIO_ERROR_NONE) {
        LOG_E(TAG, "Failed to initialize GPIO");
        return MOISTURE_ERROR;
    }
    sensor->data_pin = data_pin;
    sensor->last_value = 0;
    LOG_I(TAG, "Moisture sensor initialized on GPIO pin %d", data_pin);
    delay_ms(50);
    return MOISTURE_ERROR_NONE;
}

moisture_err_code_t moisture_sensor_read(moisture_sensor_t *sensor, float *moisture) {
    if (sensor == NULL || moisture == NULL) {
        LOG_E(TAG, "Invalid arguments");
        return MOISTURE_ERROR;
    }

    // Simulate sensor value change
    float random_decrease_value = 0.5f + ((float)rand() / (float)RAND_MAX) * (15.0f - 0.5f);

    // Simulate reading from the sensor
    moisture_simulated_value -= random_decrease_value;
    sensor->last_value = moisture_simulated_value;
    *moisture = moisture_simulated_value;
    delay_ms(50);
    return MOISTURE_ERROR_NONE;
}
