/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

#pragma once

// Define custom log levels
#define LOG_LEVEL_NONE          0
#define LOG_LEVEL_DEBUG         1
#define LOG_LEVEL_INFO          2
#define LOG_LEVEL_WARN          3
#define LOG_LEVEL_ERROR         4
#define LOG_LEVEL_CRITICAL      5

// String representation of log levels
#define LOG_LEVEL_DEBUG_STR     "DEBUG"
#define LOG_LEVEL_INFO_STR      "INFO"
#define LOG_LEVEL_WARN_STR      "WARN"
#define LOG_LEVEL_ERROR_STR     "ERROR"
#define LOG_LEVEL_CRITICAL_STR  "CRITICAL"

// Set default log module name if not defined by application
#ifndef LOG_MODULE_NAME
#define LOG_MODULE_NAME         "MODULE"
#endif

// Set default log level if not defined by application
#ifndef MODULE_LOG_LEVEL
#define MODULE_LOG_LEVEL        LOG_LEVEL_DEBUG
#endif

// Set default log message format if not defined by application
#ifndef LOG_FORMAT
#define LOG_FORMAT(level, module, file, line, message) level " " module "|" file ":" line " - " message "\n"
#endif

// Must be included after the module name, log level and log format definitions
#include "PigweedLogging.h"

#define LOG(level, fmt, ...)               \
    do {                                   \
        COMPILE_ASSERT(                    \
            (level == LOG_LEVEL_NONE)  ||  \
            (level == LOG_LEVEL_DEBUG) ||  \
            (level == LOG_LEVEL_INFO)  ||  \
            (level == LOG_LEVEL_WARN)  ||  \
            (level == LOG_LEVEL_ERROR) ||  \
            (level == LOG_LEVEL_CRITICAL), \
            "Invalid log level: " #level); \
        switch(level)                      \
        {                                  \
            case LOG_LEVEL_NONE:           \
                break;                     \
            case LOG_LEVEL_DEBUG:          \
                LOG_MESSAGE(level, LOG_LEVEL_DEBUG_STR, fmt, ##__VA_ARGS__); \
                break;                     \
            case LOG_LEVEL_INFO:           \
                LOG_MESSAGE(level, LOG_LEVEL_INFO_STR, fmt, ##__VA_ARGS__);  \
                break;                     \
            case LOG_LEVEL_WARN:           \
                LOG_MESSAGE(level, LOG_LEVEL_WARN_STR, fmt, ##__VA_ARGS__);  \
                break;                     \
            case LOG_LEVEL_ERROR:          \
                LOG_MESSAGE(level, LOG_LEVEL_ERROR_STR, fmt, ##__VA_ARGS__); \
                break;                     \
            case LOG_LEVEL_CRITICAL:       \
                LOG_MESSAGE(level, LOG_LEVEL_CRITICAL_STR, fmt, ##__VA_ARGS__); \
                break;                     \
            default:                       \
                break;                     \
        }                                  \
    } while (false)

// Interface macros for logging at different levels
#define LOG_DEBUG(fmt, ...)     LOG(LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)      LOG(LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)      LOG(LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)     LOG(LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...)  LOG(LOG_LEVEL_CRITICAL, fmt, ##__VA_ARGS__)
