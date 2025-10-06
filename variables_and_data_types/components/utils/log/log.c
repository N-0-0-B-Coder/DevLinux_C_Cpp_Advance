#include "log.h"
#include "config.h"

static Log_level current_log_level = LOG_LEVEL;

void set_log_level(Log_level level) {
    current_log_level = level;
}

static void log_message(const char *acronym, const char *TAG, const char *format, va_list args) {
    const char *color;

    switch (acronym[0]) {
        case 'D': color = "\x1b[36m"; break; // Cyan
        case 'I': color = "\x1b[32m"; break; // Green
        case 'W': color = "\x1b[33m"; break; // Yellow
        default:  color = "\x1b[31m"; break; // Red
    }
    const char *reset = "\x1b[0m";

    printf("%s%s: [%s] ", color, acronym, TAG);
    vprintf(format, args);
    printf("%s\n", reset);
}

void LOG_D(const char *TAG, const char *format, ...) {
    if (current_log_level > LOG_LEVEL_DEBUG) return;

    va_list args;
    va_start(args, format);
    log_message("D", TAG, format, args);
    va_end(args);
}
void LOG_I(const char *TAG, const char *format, ...) {
    if (current_log_level > LOG_LEVEL_INFO) return;

    va_list args;
    va_start(args, format);
    log_message("I", TAG, format, args);
    va_end(args);
}
void LOG_W(const char *TAG, const char *format, ...) {
    if (current_log_level > LOG_LEVEL_WARN) return;

    va_list args;
    va_start(args, format);
    log_message("W", TAG, format, args);
    va_end(args);
}
void LOG_E(const char *TAG, const char *format, ...) {
    if (current_log_level > LOG_LEVEL_ERROR) return;
    
    va_list args;
    va_start(args, format);
    log_message("E", TAG, format, args);
    va_end(args);
}
