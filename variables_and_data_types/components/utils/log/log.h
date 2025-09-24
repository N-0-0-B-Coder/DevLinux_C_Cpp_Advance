#ifndef __LOG_H__
#define __LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>

typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
} Log_level;

Log_level current_log_level;

/**
 * @brief Set the current log level. Messages with a level lower than the current level will be ignored.
 * 
 * @param level [in] The log level to set
 */
void set_log_level(Log_level level);

/**
 * @brief Log a message with the debug log level.
 * 
 * @param TAG [in] Tag for the log message
 * @param format [in] Format string (like printf)
 */
void LOG_D(const char *TAG, const char *format, ...);
/**
 * @brief Log a message with the info log level.
 * 
 * @param TAG [in] Tag for the log message
 * @param format [in] Format string (like printf)
 */
void LOG_I(const char *TAG, const char *format, ...);

/**
 * @brief Log a message with the warning log level.
 * 
 * @param TAG [in] Tag for the log message
 * @param format [in] Format string (like printf)
 */
void LOG_W(const char *TAG, const char *format, ...);

/**
 * @brief Log a message with the error log level.
 * 
 * @param TAG [in] Tag for the log message
 * @param format [in] Format string (like printf)
 */
void LOG_E(const char *TAG, const char *format, ...);



#ifdef __cplusplus
}
#endif
#endif // __LOG_H__