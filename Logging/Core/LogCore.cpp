/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "LogCore.hpp"
#if CONFIG_LIB_COMMONS_LOGGING_ASYNC
    #include "LogQueue.hpp"
    #include "LogThread.hpp"
#endif
#include "LogConsumer.hpp"

// ----------------------------------------------------------------------------
// Public functions
// ----------------------------------------------------------------------------

void LogCore::RegisterConsumer(uint8_t id, LogToOutput &consumer)
{
    consumer.SetId(id);
    consumer.Initialize();
    LogConsumer::RegisterConsumer(consumer);
}

#if CONFIG_LIB_COMMONS_LOGGING_ASYNC
void LogCore::InitializeQueue(void* pBuffer, size_t bufferSize)
{
    LogQueue::Initialize(pBuffer, bufferSize);
    LogThread::CreateThread(LogCore::DispatchLogMessage);
}
#endif

void LogCore::EnablePanicMode()
{
    mPanicModeEnabled = true;

    // Flush all the queued log messages immediately
#if CONFIG_LIB_COMMONS_LOGGING_ASYNC
    LogCore::Flushlogs();
#endif
}

void LogCore::HandleLogMessage(const uint8_t* pMessage, size_t length, int level)
{
    bool synchronousLogging = true;

#if CONFIG_LIB_COMMONS_LOGGING_ASYNC
    synchronousLogging = false;
#endif

    if (synchronousLogging || mPanicModeEnabled)
    {
        // In panic mode, we send the log message immediately without queuing
        LogConsumer::SendLogMessage(pMessage, length, level);
    }
    else
    {
    #if CONFIG_LIB_COMMONS_LOGGING_ASYNC
        // In normal mode, we can queue the log message for asynchronous processing
        LogQueue::PushLog(pMessage, length, level);
    #endif
    }
}

// ----------------------------------------------------------------------------
// Private functions
// ----------------------------------------------------------------------------

#if CONFIG_LIB_COMMONS_LOGGING_ASYNC
bool LogCore::DispatchLogMessage()
{
    bool messageDispatched = false;
    uint8_t* pMessage = nullptr;
    size_t messageLength = 0;
    int level = 0;

    LogQueue::PullLog(pMessage, messageLength, level);
    if (pMessage)
    {
        // Send the log message to all registered consumers
        LogConsumer::SendLogMessage(pMessage, messageLength, level);
        messageDispatched = true;
    }
    else
    {
        // No more messages to send
        messageDispatched = false;
    }

    return messageDispatched;
}

void LogCore::Flushlogs()
{
    bool messageDispatched = false;
    do
    {
        messageDispatched = LogCore::DispatchLogMessage();
    } while (messageDispatched);
}
#endif
