#include "led.h"

static const char *TAG = "LED";

led_err_code_t led_init(uint8_t led_pin) {
    gpio_err_t ret;
    gpio_cfg_t led_cfg = {
        .mode = GPIO_OUTPUT,
        .output_type = GPIO_PUSH_PULL,
        .speed = GPIO_HIGH_SPEED,
        .pull_ud = GPIO_NO_PUPD,
        .reversed = 0
    };
    ret = gpio_init(led_pin, &led_cfg);
    if (ret != GPIO_ERROR_NONE) {
        LOG_E(TAG, "Failed to initialize LED on pin %d: %d", led_pin, ret);
        return LED_ERROR;
    }
    LOG_I(TAG, "LED initialized on pin %d", led_pin);
    delay_ms(50);
    return LED_ERROR_NONE;
}

led_err_code_t led_on(uint8_t led_pin) {
    gpio_err_t ret;
    ret = gpio_set(led_pin, LED_ACTIVE_STATE);

    if (ret != GPIO_ERROR_NONE) {
        LOG_E(TAG, "Failed to turn ON LED on pin %d: %d", led_pin, ret);
        return LED_ERROR;
    }
    LOG_I(TAG, "LED on pin %d turned ON", led_pin);
    delay_ms(50);
    return LED_ERROR_NONE;
}

led_err_code_t led_off(uint8_t led_pin) {
    gpio_err_t ret;
    ret = gpio_set(led_pin, LED_INACTIVE_STATE);

    if (ret != GPIO_ERROR_NONE) {
        LOG_E(TAG, "Failed to turn OFF LED on pin %d: %d", led_pin, ret);
        return LED_ERROR;
    }
    LOG_I(TAG, "LED on pin %d turned OFF", led_pin);
    delay_ms(50);
    return LED_ERROR_NONE;
}

bool is_led_on(uint8_t led_pin) {
    gpio_state_t state;
    state = gpio_read(led_pin);
    if (state == GPIO_STATE_ERROR) {
        LOG_E(TAG, "Failed to read LED state on pin %d", led_pin);
        return false;
    }
    delay_ms(50);
    return state;
}

led_err_code_t led_toggle(uint8_t led_pin) {
    bool ret;
    led_err_code_t led_ret;
    ret = is_led_on(led_pin);
    if (ret) {
        led_ret = led_off(led_pin);
    } else {
        led_ret = led_on(led_pin);
    }
    if (led_ret != LED_ERROR_NONE) {
        LOG_E(TAG, "Failed to toggle LED on pin %d", led_pin);
        return LED_ERROR;
    }
    LOG_I(TAG, "LED on pin %d toggled to %s", led_pin, ret ? "ON" : "OFF");
    delay_ms(50);
    return LED_ERROR_NONE;
}

led_err_code_t led_blink(uint8_t led_pin, uint16_t interval_ms, uint8_t times) {
    for (uint8_t i = 0; i < times; i++) {
        if (led_toggle(led_pin) != LED_ERROR_NONE) {
            return LED_ERROR;
        }
        struct timespec req = {0};
        req.tv_sec = interval_ms / 1000;
        req.tv_nsec = (interval_ms % 1000) * 1000000L;
        nanosleep(&req, (struct timespec *)NULL);
    }
    delay_ms(50);
    return LED_ERROR_NONE;
}