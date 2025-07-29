/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "LogCore.hpp"
#if CONFIG_LIB_COMMONS_LOGGING_DEFERRED
    #include "LogQueue.hpp"
#endif
#include "LogConsumer.hpp"

// ----------------------------------------------------------------------------
// Macro definitions
// ----------------------------------------------------------------------------

#if CONFIG_LIB_COMMONS_LOGGING_DEFERRED
    // Define thread stack size and priority
    #define LOG_THREAD_STACK_SIZE   (1024)
    #define LOG_THREAD_PRIORITY     (5)
#endif

// ----------------------------------------------------------------------------
// Variable definitions
// ----------------------------------------------------------------------------

#if CONFIG_LIB_COMMONS_LOGGING_DEFERRED
    // Thread stack
    K_THREAD_STACK_DEFINE(gLogThreadStack, LOG_THREAD_STACK_SIZE);

    // Thread data structure
    struct k_thread gLogThreadData;

    struct k_sem LogCore::mDataReadySem;
#endif

// ----------------------------------------------------------------------------
// Public functions
// ----------------------------------------------------------------------------

void LogCore::RegisterConsumer(uint8_t id, LogToOutput &consumer)
{
    consumer.SetId(id);
    consumer.Initialize();
    LogConsumer::RegisterConsumer(consumer);
}

#if CONFIG_LIB_COMMONS_LOGGING_DEFERRED
void LogCore::InitializeQueue(void* pBuffer, size_t bufferSize)
{
    LogQueue::Initialize(pBuffer, bufferSize);

    // Create and start the thread
    k_thread_create(&gLogThreadData, gLogThreadStack, LOG_THREAD_STACK_SIZE,
                    LogCore::LogThreadEntry, NULL, NULL, NULL,
                    LOG_THREAD_PRIORITY, 0, K_NO_WAIT);

    // Initialize the binary semaphore for data ready signal
    k_sem_init(&mDataReadySem, 0, 1);
}
#endif

void LogCore::EnablePanicMode()
{
    mPanicModeEnabled = true;

#if CONFIG_LIB_COMMONS_LOGGING_DEFERRED
    // In panic mode, flush all the queued log messages immediately.
    Flushlogs();
#endif
}

void LogCore::HandleLogMessage(const uint8_t* pMessage, size_t length, int level)
{
    bool deferredLogging = false;

#if CONFIG_LIB_COMMONS_LOGGING_DEFERRED
    deferredLogging = true;
#endif

    if (!deferredLogging || mPanicModeEnabled)
    {
        // In immediate mode, we send the log message immediately without queuing
        LogConsumer::SendLogMessage(pMessage, length, level);
    }
#if CONFIG_LIB_COMMONS_LOGGING_DEFERRED
    else
    {
        // In deferred mode, we can queue the log message and process later
        LogQueue::PushLog(pMessage, length, level);
        mLogThresholdCounter++;

        if (mLogThresholdCounter >= CONFIG_LIB_COMMONS_LOGGING_THRESHOLD)
        {
            // If the threshold is reached, signal the log thread to process the logs
            mLogThresholdCounter = 0;
            k_sem_give(&mDataReadySem);
        }
    }
#endif
}

// ----------------------------------------------------------------------------
// Private functions
// ----------------------------------------------------------------------------

#if CONFIG_LIB_COMMONS_LOGGING_DEFERRED
void LogCore::LogThreadEntry(void* arg1, void* arg2, void* arg3)
{
    while (1)
    {
        // Wait for data ready signal before processing logs
        k_sem_take(&mDataReadySem, K_FOREVER);

        Flushlogs();
    }
}

void LogCore::Flushlogs()
{
    uint8_t* pMessage = nullptr;
    size_t messageLength = 0;
    int level = 0;

    do
    {
        LogQueue::PullLog(pMessage, messageLength, level);
        if (pMessage)
        {
            // Send the log message to all registered consumers
            LogConsumer::SendLogMessage(pMessage, messageLength, level);
        }
    } while (pMessage);
}
#endif
