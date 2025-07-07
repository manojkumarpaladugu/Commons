/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "Assert.h"
#include "LogConsumer.hpp"
#ifdef CONFIG_LIB_COMMONS_LOGGING_ASYNC
    #include "LogQueue.hpp"
#endif

// ----------------------------------------------------------------------------
// Variable definitions
// ----------------------------------------------------------------------------

// List of registered consumers
IConsumer* LogConsumer::mIConsumers[CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS];

// ----------------------------------------------------------------------------
// Public functions
// ----------------------------------------------------------------------------

void LogConsumer::RegisterConsumer(IConsumer &consumer)
{
    for (size_t i = 0; i < CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS; ++i)
    {
        if (mIConsumers[i] == nullptr)
        {
            mIConsumers[i] = &consumer;
            return; // Consumer registered successfully
        }
    }
}

void LogConsumer::SendLogMessage(const uint8_t* pMessage, size_t length, int level)
{
    // Send the log message to all registered consumers
    for (size_t i = 0; i < CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS; ++i)
    {
        IConsumer* pConsumer = mIConsumers[i];
        if (pConsumer != nullptr)
        {
            pConsumer->ProcessLogMessage(pMessage, length);
        }
    }
}
