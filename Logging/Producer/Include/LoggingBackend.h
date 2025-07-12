/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

#pragma once

#include "CommonTypes.h"

#include <pw_log/levels.h>

// Pigweed uses static_assert in their headers. So, Redefine the static_assert to prevent errors when this header is included in C files.
#ifndef __cplusplus
#ifndef static_assert
#define static_assert(...)          COMPILE_ASSERT(__VA_ARGS__)
#endif
#endif

// Define a mapping from custom log levels to Pigweed log levels
#define MAP_CUSTOM_LOG_LEVEL_TO_PW(level)              \
    ((level) == LOG_LEVEL_DEBUG ? PW_LOG_LEVEL_DEBUG : \
    (level) == LOG_LEVEL_INFO ? PW_LOG_LEVEL_INFO :    \
    (level) == LOG_LEVEL_WARN ? PW_LOG_LEVEL_WARN :    \
    (level) == LOG_LEVEL_ERROR ? PW_LOG_LEVEL_ERROR :  \
    (level) == LOG_LEVEL_CRITICAL ? PW_LOG_LEVEL_CRITICAL : PW_LOG_LEVEL_DEBUG)

// Convert the line number to string
#define LINE_STRING                 STRINGIZE(__LINE__)

// Provide module name and log level for the Pigweed logging system
#define PW_LOG_MODULE_NAME          LOG_MODULE_NAME
#define PW_LOG_LEVEL                MAP_CUSTOM_LOG_LEVEL_TO_PW(MODULE_LOG_LEVEL)

// Macro to pass the formatted log message to the Pigweed logging system
#define LOG_MESSAGE(level, level_string, fmt, ...) \
    PW_LOG(MAP_CUSTOM_LOG_LEVEL_TO_PW(level), PW_LOG_LEVEL, PW_LOG_MODULE_NAME, PW_LOG_FLAGS, LOG_FORMAT(level_string, PW_LOG_MODULE_NAME, __FILE_NAME__, LINE_STRING, fmt), ##__VA_ARGS__)

// The PW_LOG_TOKENIZED_FORMAT_STRING macro is used by pigweed to append the module name to the tokenized message.
// We re-define it to use the string received from the logging macros, without appending the anything to it.
#define PW_LOG_TOKENIZED_FORMAT_STRING(module, string) string

// Must be included after the PW_LOG_ macro definitions
#include <pw_log/log.h>
