#include "humidity.h"

static const char *TAG = "HUMIDITY_SENSOR";
static float humidity_simulated_value = 100.0f;

void humidity_value_increase(void) {
    float random_increase_value = 2.0f + ((float)rand() / (float)RAND_MAX) * (10.0f - 2.0f);
    humidity_simulated_value += random_increase_value;
    if (humidity_simulated_value > 100.0f) {
        humidity_simulated_value = 100.0f; // Cap at 100 %
    }
}

humidity_err_code_t humidity_sensor_init(humidity_sensor_t *sensor, gpio_num_t data_pin) {
    if (sensor == NULL) {
        LOG_E(TAG, "Sensor pointer is NULL");
        return HUMIDITY_ERROR;
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
        return HUMIDITY_ERROR;
    }
    sensor->data_pin = data_pin;
    sensor->last_value = 0;
    LOG_I(TAG, "Humidity sensor initialized");
    return HUMIDITY_ERROR_NONE;
}

humidity_err_code_t humidity_sensor_read(humidity_sensor_t *sensor, float *humidity) {
    if (sensor == NULL || humidity == NULL) {
        LOG_E(TAG, "Invalid arguments");
        return HUMIDITY_ERROR;
    }

    // Simulate sensor value change
    float random_decrease_value = 0.5f + ((float)rand() / (float)RAND_MAX) * (5.0f - 0.5f);

    // Simulate reading from the sensor
    float current_sensor_value = humidity_simulated_value - random_decrease_value;
    sensor->last_value = current_sensor_value;
    *humidity = current_sensor_value;
    return HUMIDITY_ERROR_NONE;
}
