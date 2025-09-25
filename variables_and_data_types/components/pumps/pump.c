#include "pump.h"
#include "temperature/temperature.h"
#include "humidity/humidity.h"

static const char *TAG = "PUMP";

pump_err_code_t pump_init(pump_t *pump, uint8_t id, gpio_num_t control_pin) {
    if (pump == NULL) {
        LOG_E(TAG, "Pump pointer is NULL");
        return PUMP_ERROR_NULL_ARG;
    }
    pump->id = id;
    pump->control_pin = control_pin;
    pump->state = PUMP_STATE_OFF;
    pump->flow_rate = 0.0f;
    LOG_I(TAG, "Pump %d initialized", id);
    return PUMP_ERROR_NONE;
}

pump_err_code_t pump_set_state(pump_t *pump, pump_state_t state) {
    if (pump == NULL) {
        LOG_E(TAG, "Pump pointer is NULL");
        return PUMP_ERROR_NULL_ARG;
    }
    pump->state = state;
    LOG_I(TAG, "Pump %d state set to %d", pump->id, state);
    temp_value_decrease();
    humidity_value_increase();
    return PUMP_ERROR_NONE;
}

pump_state_t pump_get_state(const pump_t *pump) {
    if (pump == NULL) {
        LOG_E(TAG, "Pump pointer is NULL");
        return PUMP_STATE_ERROR;
    }
    return pump->state;
}

pump_err_code_t pump_set_flow_rate(pump_t *pump, float flow_rate) {
    if (pump == NULL) {
        LOG_E(TAG, "Pump pointer is NULL");
        return PUMP_ERROR_NULL_ARG;
    }
    pump->flow_rate = flow_rate;
    LOG_I(TAG, "Pump %d flow rate set to %.2f L/min", pump->id, flow_rate);
    return PUMP_ERROR_NONE;
}

float pump_get_flow_rate(const pump_t *pump) {
    if (pump == NULL) {
        LOG_E(TAG, "Pump pointer is NULL");
        return (-1.0f);
    }
    return pump->flow_rate;
}
