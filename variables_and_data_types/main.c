#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "log/log.h"
#include "gpios/gpio.h"
#include "temperature/temperature.h"
#include "humidity/humidity.h"
#include "pumps/pump.h"
#include "leds/led.h"
#include "buttons/button.h"

#include "auto/auto.h"
#include "manual/manual.h"

static const char *TAG = "MAIN";

temp_sensor_t temp_sensor;
humidity_sensor_t humidity_sensor;
pump_t pump;
bool auto_mode_noti = false;
bool manual_mode_noti = false;

int main(void) {

    // Initialize System
    if (init_system(&temp_sensor, &humidity_sensor, &pump) != 0) {
        return -1;
    }

    while (1) {
        // Check Button States
        if (button_get_state(BUTTON_TOGGLE_AUTO_PIN) == BUTTON_STATE_PRESSED) {
            if (!auto_mode_noti) {
                auto_mode_noti = true;
                manual_mode_noti = false;
                LOG_I(TAG, "Auto mode toggled on");
            }

            auto_mode_run(&temp_sensor, &humidity_sensor, &pump);
        }
        else if (button_get_state(BUTTON_TOGGLE_AUTO_PIN) == BUTTON_STATE_RELEASED) {
            if (!manual_mode_noti) {
                manual_mode_noti = true;
                auto_mode_noti = false;
                LOG_I(TAG, "Manual mode toggled on, stopping pumps");
            }
            pump_set_state(&pump, PUMP_STATE_OFF);
        }
        
    }
    return 0;
}
