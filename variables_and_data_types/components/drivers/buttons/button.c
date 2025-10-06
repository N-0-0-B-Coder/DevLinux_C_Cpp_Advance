#include "button.h"

static const char *TAG = "BUTTON";

button_err_t button_init(uint8_t button_pin) {
    gpio_err_t ret;

    gpio_cfg_t button_cfg = {
        .mode = GPIO_INPUT,
        .output_type = GPIO_PUSH_PULL,
        .speed = GPIO_HIGH_SPEED,
        .pull_ud = GPIO_NO_PUPD,
        .reversed = 0
    };

    ret = gpio_init(button_pin, &button_cfg);
    if (ret != GPIO_ERROR_NONE) {
        LOG_E(TAG, "Failed to initialize button on pin %d", button_pin);
        return BUTTON_ERROR_INIT_FAIL;
    }

    LOG_I(TAG, "Button initialized on pin %d", button_pin);
    delay_ms(50);
    return BUTTON_ERROR_NONE;
}

button_state_t button_get_state(uint8_t button_pin) {
    gpio_state_t gpio_state = gpio_read(button_pin);
    if (gpio_state == GPIO_STATE_ERROR) {
        LOG_E(TAG, "Error reading button state on pin %d", button_pin);
        return BUTTON_STATE_RELEASED; // Default to released on error
    }

    delay_ms(50);
    return gpio_state == GPIO_STATE_HIGH ? BUTTON_STATE_PRESSED : BUTTON_STATE_RELEASED;
}

button_err_t button_set_state(uint8_t button_pin, button_state_t state) {
    gpio_err_t ret;
    ret = gpio_set(button_pin, state == BUTTON_STATE_PRESSED ? GPIO_STATE_HIGH : GPIO_STATE_LOW);
    if (ret != GPIO_ERROR_NONE) {
        LOG_E(TAG, "Failed to set button state on pin %d", button_pin);
        return BUTTON_ERROR_FAIL;
    }
    
    LOG_I(TAG, "Button state set on pin %d to %s", button_pin, state == BUTTON_STATE_PRESSED ? "PRESSED" : "RELEASED");
    delay_ms(50);
    return BUTTON_ERROR_NONE;
}