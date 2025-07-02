/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "Assert.h"
#include "LogDispatcher.hpp"
#ifdef CONFIG_LIB_COMMONS_LOGGING_ASYNC
    #include "LogQueue.hpp"
#endif

#include <zephyr/kernel.h>

// ----------------------------------------------------------------------------
// Macro definitions
// ----------------------------------------------------------------------------

// Define thread stack size and priority
#define THREAD_STACK_SIZE 1024
#define THREAD_PRIORITY 5

// ----------------------------------------------------------------------------
// Variable definitions
// ----------------------------------------------------------------------------

// Thread stack
K_THREAD_STACK_DEFINE(gLogDispatcherThreadStack, THREAD_STACK_SIZE);

// Thread data structure
struct k_thread gLogDispatcherThreadData;

// List of registered consumers
IConsumer* LogDispatcher::mIConsumers[CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS];

// ----------------------------------------------------------------------------
// Private functions
// ----------------------------------------------------------------------------

#ifdef CONFIG_LIB_COMMONS_LOGGING_ASYNC
// Thread entry function
void LogDispatcher::Run(void* arg1, void* arg2, void* arg3)
{
    uint8_t messageBuffer[CONFIG_LIB_COMMONS_LOGGING_MAX_STRING_LENGTH + 1];
    while (1)
    {
        // if (LogQueue::IsEmpty())
        // {
        //     // No log messages available, yield to allow other threads to run
        //     k_yield();
        //     continue;
        // }

        size_t messageLength = 0;
        int level = 0;
        LogQueue::PullLog(reinterpret_cast<uint8_t*>(&messageBuffer), messageLength, level);
        if (messageLength > 0)
        {
            // Send the log message to all registered consumers
            LogDispatcher::SendLog(reinterpret_cast<const uint8_t*>(&messageBuffer), messageLength, level);
        }
    }
}
#endif

// ----------------------------------------------------------------------------
// Public functions
// ----------------------------------------------------------------------------

void LogDispatcher::Start()
{
#ifdef CONFIG_LIB_COMMONS_LOGGING_ASYNC
    // Create and start the thread
    k_thread_create(&gLogDispatcherThreadData, gLogDispatcherThreadStack, THREAD_STACK_SIZE,
                    LogDispatcher::Run, NULL, NULL, NULL,
                    THREAD_PRIORITY, 0, K_NO_WAIT);
#endif
}

void LogDispatcher::RegisterConsumer(IConsumer &consumer)
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

void LogDispatcher::SendLog(const uint8_t* message, size_t length, int level)
{
    ASSERT(message != NULL);
    ASSERT(length > 0);

    // Send the log message to all registered consumers
    for (size_t i = 0; i < CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS; ++i)
    {
        IConsumer* pConsumer = mIConsumers[i];
        if (pConsumer != nullptr)
        {
            pConsumer->ProcessLog(message, length, level);
        }
    }
}
