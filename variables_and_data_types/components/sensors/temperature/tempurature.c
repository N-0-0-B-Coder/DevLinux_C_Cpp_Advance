#include "temperature.h"

static const char *TAG = "TEMPERATURE_SENSOR";
static float temperature_simulated_value = 25.0f;

void temp_value_decrease(float pump_rate) {
    float random_decrease_value = (2.5f + ((float)rand() / (float)RAND_MAX) * (15.0f - 2.5f)) * (pump_rate/5.0f);
    temperature_simulated_value -= random_decrease_value;
    if (temperature_simulated_value < 25.0f) {
        temperature_simulated_value = 25.0f; // Cap at 25 C
    }
    delay_ms(50);
}

temp_sensor_status_t temp_sensor_init(temp_sensor_t *sensor, gpio_num_t data_pin) {
    if (sensor == NULL) {
        LOG_E(TAG, "Sensor structure is NULL");
        return TEMPERATURE_ERROR;
    }

    gpio_cfg_t sensor_cfg = {
        .mode = GPIO_INPUT,
        .output_type = GPIO_PUSH_PULL,
        .pull_ud = GPIO_PULL_UP,
        .speed = GPIO_LOW_SPEED,
        .reversed = 0
    };
    if (gpio_init(data_pin, &sensor_cfg) != GPIO_ERROR_NONE) {
        LOG_E(TAG,"Failed to initialize GPIO pin %d", data_pin);
        return TEMPERATURE_ERROR;
    }

    sensor->data_pin = data_pin;
    sensor->last_value = 0.0f;

    LOG_I(TAG, "Temperature sensor initialized on GPIO pin %d", data_pin);
    delay_ms(50);
    return TEMPERATURE_ERROR_NONE;
}

temp_sensor_status_t temp_sensor_read(temp_sensor_t *sensor, float *temperature) {
    if (sensor == NULL || temperature == NULL) {
        LOG_E(TAG, "Invalid arguments");
        return TEMPERATURE_ERROR;
    }
    // Simulate sensor value change
    float random_increase_value = 0.5f + ((float)rand() / (float)RAND_MAX) * (7.0f - 0.5f);
    // Simulate reading from the sensor
    temperature_simulated_value += random_increase_value;
    if (temperature_simulated_value > 60.0f) {
        temperature_simulated_value = 60.0f; // Cap at 60 C
    }
    sensor->last_value = temperature_simulated_value;
    *temperature = temperature_simulated_value;

    delay_ms(50);
    return TEMPERATURE_ERROR_NONE;
}
