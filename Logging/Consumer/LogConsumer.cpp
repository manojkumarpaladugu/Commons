/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "CommonTypes.h"
#include "LogConsumer.hpp"
#if CONFIG_LIB_COMMONS_LOGGING_DEFERRED
    #include "LogQueue.hpp"
#endif

// ----------------------------------------------------------------------------
// Variable definitions
// ----------------------------------------------------------------------------

// List of registered consumers
LogToOutput* LogConsumer::mConsumers[CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS];

// ----------------------------------------------------------------------------
// Public functions
// ----------------------------------------------------------------------------

void LogConsumer::RegisterConsumer(LogToOutput &consumer)
{
    for (size_t i = 0; i < CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS; ++i)
    {
        if (mConsumers[i] == nullptr)
        {
            mConsumers[i] = &consumer;
            return; // Consumer registered successfully
        }
    }
}

void LogConsumer::SendLogMessage(const uint8_t* pMessage, size_t length, int level)
{
    UNUSED(level);

    // Send the log message to all registered consumers
    for (size_t i = 0; i < CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS; ++i)
    {
        LogToOutput* pConsumer = mConsumers[i];
        if (pConsumer != nullptr)
        {
            pConsumer->ProcessLogMessage(pMessage, length);
        }
    }
}
