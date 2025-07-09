/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

#pragma once

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "LogToOutput.hpp"

// ----------------------------------------------------------------------------
// Class definition
// ----------------------------------------------------------------------------

class LogConsumer
{
public:

    /**
     * @brief Register a consumer to receive log messages.
     *
     * @param[in] consumer Reference to the consumer object that will handle log messages.
     */
    static void RegisterConsumer(LogToOutput &consumer);

    /**
     * @brief Send log message to all the registered consumers.
     *
     * This function is used to send log messages to the registered consumers.
     *
     * @param[in] pMessage Pointer to the log message.
     * @param[in] length Length of the log message.
     * @param[in] level Log level of the message.
     */
    static void SendLogMessage(const uint8_t* pMessage, size_t length, int level);

private:

    static LogToOutput* mConsumers[CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS];           // Array of registered consumers
};
