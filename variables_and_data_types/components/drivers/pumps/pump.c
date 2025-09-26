#include "pump.h"
#include "temperature/temperature.h"
#include "soil_moisture/moisture.h"

static const char *TAG = "PUMP";

pump_err_code_t pump_init(pump_t *pump, uint8_t id, gpio_num_t control_pin) {
    gpio_err_t ret;
    if (pump == NULL) {
        LOG_E(TAG, "Pump pointer is NULL");
        return PUMP_ERROR_NULL_ARG;
    }
    pump->id = id;
    pump->control_pin = control_pin;
    pump->state = PUMP_STATE_OFF;
    pump->flow_rate = 0.0f;

    gpio_cfg_t pump_cfg = {
        .mode = GPIO_OUTPUT,
        .output_type = GPIO_PUSH_PULL,
        .speed = GPIO_LOW_SPEED,
        .pull_ud = GPIO_NO_PUPD,
        .reversed = 0
    };

    ret = gpio_init(control_pin, &pump_cfg);
    if (ret != GPIO_ERROR_NONE) {
        LOG_E(TAG, "Failed to initialize pump on pin %d: %d", control_pin, ret);
        return PUMP_ERROR;
    }

    LOG_I(TAG, "Pump %d initialized", id);
    delay_ms(50);
    return PUMP_ERROR_NONE;
}

pump_err_code_t pump_set_state(pump_t *pump, pump_state_t state) {
    if (pump == NULL) {
        LOG_E(TAG, "Pump pointer is NULL");
        return PUMP_ERROR_NULL_ARG;
    }
    pump->state = state;

    LOG_I(TAG, "Pump %d state set to %d", pump->id, state);

    if (state == PUMP_STATE_ON) {
        gpio_set(pump->control_pin, GPIO_STATE_HIGH);
        temp_value_decrease();
        moisture_value_increase();
    } else if (state == PUMP_STATE_OFF) {
        gpio_set(pump->control_pin, GPIO_STATE_LOW);
    } else {
        LOG_E(TAG, "Invalid pump state %d for pump %d", state, pump->id);
        return PUMP_ERROR;
    }

    delay_ms(50);
    return PUMP_ERROR_NONE;
}

pump_state_t pump_get_state(const pump_t *pump) {
    if (pump == NULL) {
        LOG_E(TAG, "Pump pointer is NULL");
        return PUMP_STATE_ERROR;
    }
    delay_ms(50);
    return pump->state;
}

pump_err_code_t pump_set_flow_rate(pump_t *pump, float flow_rate) {
    if (pump == NULL) {
        LOG_E(TAG, "Pump pointer is NULL");
        return PUMP_ERROR_NULL_ARG;
    }
    pump->flow_rate = flow_rate;
    LOG_I(TAG, "Pump %d flow rate set to %.2f L/min", pump->id, flow_rate);
    delay_ms(50);
    return PUMP_ERROR_NONE;
}

float pump_get_flow_rate(const pump_t *pump) {
    if (pump == NULL) {
        LOG_E(TAG, "Pump pointer is NULL");
        return (-1.0f);
    }
    delay_ms(50);
    return pump->flow_rate;
}
