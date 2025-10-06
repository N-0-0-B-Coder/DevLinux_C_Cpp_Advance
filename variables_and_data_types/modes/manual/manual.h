#ifndef _MANUAL_H_
#define _MANUAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "systime/systime.h"

#include "config.h"
#include "buttons/button.h"
#include "leds/led.h"
#include "log/log.h"
#include "pumps/pump.h"

/**
 * @brief Run the manual mode logic
 * 
 * @param pump [in, out] Pointer to pump structure
 */
void manual_mode_run(pump_t *pump);

#ifdef __cplusplus
}
#endif

#endif // _MANUAL_H_
