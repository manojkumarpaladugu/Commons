/*
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdbool.h>

/// @brief Compile-time assertion
#if defined (__cplusplus)
    #define COMPILE_ASSERT(expr, str)   static_assert((expr), str)
#else
    #define COMPILE_ASSERT(expr, str)   _Static_assert((expr), str)
#endif

/// @brief Stringize
#define STRINGIZE(x) _STRINGIZE(x)                      ///< Macro for converting the argument value to string. Require indirection to stringize the value instead of the identifier.
#define _STRINGIZE(x) #x                                ///< Macro for converting the argument value to string. Calling this directly will stringize the identifer, not the value.

/// @brief To mark a variable as unused. This is useful to avoid compiler warnings about unused variables.
#define UNUSED(expr) do { (void)(expr); } while (0)

#ifndef ASSERT
#define ASSERT(condition) do { if (!(condition)) { while (1); } } while (0)
#endif
