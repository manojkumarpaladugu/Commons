/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

#pragma once

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "CommonTypes.h"

// ----------------------------------------------------------------------------
// Datatype definitions
// ----------------------------------------------------------------------------

enum LogConsumerId
{
    cLogToStdOutId = 0,     ///< Log consumer for stdout
    cMaxLogConsumerId       ///< Maximum number of log consumers
};
COMPILE_ASSERT(cMaxLogConsumerId == CONFIG_COMMONS_LOGGING_MAX_CONSUMERS, "cMaxLogConsumerId exceeds CONFIG_COMMONS_LOGGING_MAX_CONSUMERS");
