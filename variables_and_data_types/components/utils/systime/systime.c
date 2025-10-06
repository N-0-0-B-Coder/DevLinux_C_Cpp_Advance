#include "systime.h"

void delay_ms(uint32_t ms) {
    struct timespec req = {0};

    req.tv_sec = ms / 1000U;
    req.tv_nsec = (ms % 1000U) * 1000000UL;
    nanosleep(&req, NULL);
}

uint32_t get_time_s(void) {
    struct timespec ts;
    
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint32_t)ts.tv_sec;
}