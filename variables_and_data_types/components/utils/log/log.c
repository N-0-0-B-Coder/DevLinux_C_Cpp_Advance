#include "log.h"
#include "config.h"

Log_level current_log_level = LOG_LEVEL;

void set_log_level(Log_level level) {
    current_log_level = level;
}

static void log_message(const char *TAG, const char *format, va_list args) {
    printf("[%s] ", TAG);
    vprintf(format, args);
    printf("\n");
}

void LOG_I(const char *TAG, const char *format, ...) {
    if (current_log_level > LOG_LEVEL_INFO) return;
    va_list args;
    va_start(args, format);
    log_message(TAG, format, args);
    va_end(args);
}
void LOG_W(const char *TAG, const char *format, ...) {
    if (current_log_level > LOG_LEVEL_WARN) return;
    va_list args;
    va_start(args, format);
    log_message(TAG, format, args);
    va_end(args);
}
void LOG_E(const char *TAG, const char *format, ...) {
    if (current_log_level > LOG_LEVEL_ERROR) return;
    va_list args;
    va_start(args, format);
    log_message(TAG, format, args);
    va_end(args);
}
void LOG_D(const char *TAG, const char *format, ...) {
    if (current_log_level > LOG_LEVEL_DEBUG) return;
    va_list args;
    va_start(args, format);
    log_message(TAG, format, args);
    va_end(args);
}
