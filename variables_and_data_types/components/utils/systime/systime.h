#ifndef _SYSTIME_H_
#define _SYSTIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif

#include <time.h>
#include <stdint.h>

/**
 * @brief Delay execution for a specified number of milliseconds
 * 
 * @param ms [in] Number of milliseconds to delay
 */
void delay_ms(uint32_t ms);

/**
 * @brief Get the current system time in seconds since the epoch
 * 
 * @return uint32_t Current time in seconds
 */
uint32_t get_time_s(void);

#ifdef __cplusplus
}
#endif
#endif // _SYSTIME_H_