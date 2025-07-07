/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

#pragma once

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------------
// Macro definitions
// ----------------------------------------------------------------------------

/**
 * @brief Assert handler function
 *
 * @param[in] file The name of the file where the assertion failed.
 * @param[in] line The line number where the assertion failed.
 * @param[in] caller The address of the caller function.
 */
void Assert_HandleAssert(const char* pFile, int line, uintptr_t caller);

/// @brief Assert macro
#define ASSERT(condition)   \
    do {                    \
        if (!(condition))   \
        {                   \
            Assert_HandleAssert(__FILE_NAME__, __LINE__, (uintptr_t)__builtin_return_address(0)); \
        }                   \
    } while (false);

#ifdef __cplusplus
}
#endif
