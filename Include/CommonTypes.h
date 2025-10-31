/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

#pragma once

#include <stdbool.h>

/// @brief Compile-time assertion
#if defined (__cplusplus)
    #define COMPILE_ASSERT(expr, str)   static_assert((expr), str)
#else
    #define COMPILE_ASSERT(expr, str)   _Static_assert((expr), str)
#endif

/// @brief Convert the argument value to string
#define _TO_STRING(x)  #x
#define TO_STRING(x)    _TO_STRING(x)

/// @brief To mark a variable as unused. This is useful to avoid compiler warnings about unused variables.
#define UNUSED(expr) do { (void)(expr); } while (0)
