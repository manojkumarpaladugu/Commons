/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "LogToOutput.hpp"

// ----------------------------------------------------------------------------
// Class definition
// ----------------------------------------------------------------------------

class LogCore
{
public:
    /**
     * @brief Registers a consumer to receive log messages.
     *
     * @param[in] id Unique identifier for the consumer.
     * @param[in] consumer Reference to the consumer that will handle log messages.
     */
    static void RegisterConsumer(uint8_t id, LogToOutput &consumer);

#if CONFIG_LIB_COMMONS_LOGGING_ASYNC
    /**
     * @brief Initializes the log queue and start the log thread.
     *
     * @param[in] pBuffer Pointer to the buffer used for the log queue.
     * @param[in] bufferSize Size of the buffer in bytes.
     */
    static void InitializeQueue(void* pBuffer, size_t bufferSize);
#endif

    /**
     * @brief Enables panic mode for the logging system.
     */
    static void EnablePanicMode();

    /**
     * @brief Handles a log message by sending it to the appropriate consumer or queue.
     *
     * @param[in] pMessage Pointer to the log message.
     * @param[in] length Length of the log message.
     * @param[in] level Log level of the message.
     */
    static void HandleLogMessage(const uint8_t* pMessage, size_t length, int level);

private:

#if CONFIG_LIB_COMMONS_LOGGING_ASYNC
    /**
     * @brief Dispatches one log message at a time to registered consumers.
     *
     * This function is a thread entry point to process and send
     * all pending log messages to the registered consumers.
     *
     * @return true if message was dispatched, false otherwise.
     */
    static bool DispatchLogMessage();

    /**
     * @brief Flushes all queued log messages immediately.
     *
     * This function is called when panic mode is enabled to ensure that all
     * pending log messages are sent out without delay.
     */
    static void Flushlogs();
#endif

    inline static bool mPanicModeEnabled = false;        // Flag to indicate if panic mode is enabled
};
