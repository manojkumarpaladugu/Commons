/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#define LOG_FORMAT(level, module, file, line, message) "<" module "> - " message "\n"

#include "Logging.h"
#include "Assert.h"
#include "LogCore.hpp"

#include <inttypes.h>

// ----------------------------------------------------------------------------
// Public function definitions
// ----------------------------------------------------------------------------

void Assert_HandleAssert(const char* pFile, int line, uintptr_t caller)
{
    LOG_CRITICAL("ASSERTION at %s:%d PC=0x%" PRIxPTR " ", pFile, line, caller);

    LogCore::EnablePanicMode();

    while(true){};
}
