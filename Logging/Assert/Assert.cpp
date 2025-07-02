/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "Assert.h"
#include "Logging.h"

#include <inttypes.h>

// ----------------------------------------------------------------------------
// Public function definitions
// ----------------------------------------------------------------------------

void Assert_HandleAssert(const char* file, int line, uintptr_t caller)
{
    LOG_CRITICAL("ASSERTION at %s:%d PC=0x%" PRIxPTR " ", file, line, caller);

    while(true){};
}
