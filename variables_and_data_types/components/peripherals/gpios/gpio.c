#include "gpio.h"

static const char *TAG = "GPIO";

gpio_t gpio_table[8] = {0};

gpio_err_t gpio_init(gpio_num_t gpio, gpio_cfg_t *gpio_cfg) {

    if (gpio_table == NULL) {
        return GPIO_ERROR_NO_TABLE;
    }

    if (gpio_cfg == NULL) {
        return GPIO_ERROR_CFG_NULL;
    }

    if (gpio >= GPIO_MAX) {
        return GPIO_ERROR_INVALID_PIN;
    }

    if (gpio_table[gpio].is_initialized) {
        LOG_W(TAG, "GPIO%d already initialized", gpio);
        return GPIO_ERROR_NONE;
    }

    // Default state is low
    gpio_table[gpio].is_initialized = 1;
    gpio_table[gpio].cfg = *gpio_cfg;
    gpio_table[gpio].gpio = gpio;
    gpio_table[gpio].state = GPIO_STATE_LOW;

    LOG_D(TAG, "Initialized GPIO%d", gpio);
    return GPIO_ERROR_NONE;
}

gpio_err_t gpio_set(gpio_num_t gpio, gpio_state_t state) {
    if (gpio_table == NULL) {
        return GPIO_ERROR_NO_TABLE;
    }

    if (gpio >= GPIO_MAX) {
        return GPIO_ERROR_INVALID_PIN;
    }

    if (gpio_table[gpio].is_initialized == 0) {
        return GPIO_ERROR_NOT_INITIALIZED;
    }

    gpio_table[gpio].state = state;

    LOG_D(TAG, "Set GPIO%d to %s", gpio, state == GPIO_STATE_HIGH ? "HIGH" : "LOW");
    return GPIO_ERROR_NONE;
}

gpio_state_t gpio_read(gpio_num_t gpio) {
    if (gpio_table == NULL || gpio >= GPIO_MAX || gpio_table[gpio].is_initialized == 0) {
        LOG_E(TAG, "GPIO ERROR: Invalid read on GPIO%d", gpio);
        return GPIO_STATE_ERROR;
    }
    
    LOG_D(TAG, "Read GPIO%d state: %s", gpio, gpio_table[gpio].state == GPIO_STATE_HIGH ? "HIGH" : "LOW");
    return gpio_table[gpio].state;
}

