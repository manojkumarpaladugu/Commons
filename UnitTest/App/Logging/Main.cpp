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
#include "LogCore.hpp"
#include "LogToStdOut.hpp"

// ----------------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------------

int main(void)
{
    // Register the consumer
    static LogToStdOut logToStdOut;
    LogCore::RegisterConsumer(cLogToStdOutId, logToStdOut);

    LOG_DEBUG("This is a debug message");
    LOG_INFO("This is an info message");
    LOG_WARN("This is a warning message");
    LOG_ERROR("This is an error message");
    LOG_CRITICAL("This is a critical message");

    ASSERT(false);

    return 0;
}
