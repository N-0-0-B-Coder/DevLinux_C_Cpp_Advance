#include "log.h"
#include "config.h"

Log_level current_log_level = LOG_LEVEL;

void set_log_level(Log_level level) {
    current_log_level = level;
}

static void log_message(const char *TAG, const char *format, ...) {
    printf("[%s] ", TAG);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void LOG_I(const char *TAG, const char *format, ...) {
    if (current_log_level > LOG_LEVEL_INFO) return;
    log_message(TAG, format);
}
void LOG_W(const char *TAG, const char *format, ...) {
    if (current_log_level > LOG_LEVEL_WARN) return;
    log_message(TAG, format);
}
void LOG_E(const char *TAG, const char *format, ...) {
    if (current_log_level > LOG_LEVEL_ERROR) return;
    log_message(TAG, format);
}
void LOG_D(const char *TAG, const char *format, ...) {
    if (current_log_level > LOG_LEVEL_DEBUG) return;
    log_message(TAG, format);
}