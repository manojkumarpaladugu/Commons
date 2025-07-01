/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

#pragma once

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "IConsumer.hpp"

// ----------------------------------------------------------------------------
// Class definition
// ----------------------------------------------------------------------------

class LogDispatcher
{
public:
    /**
     * @brief Start the dispatcher service.
     */
    static void Start();

    /**
     * @brief Register a consumer to receive log messages.
     * 
     * @param[in] consumer Reference to the consumer object that will handle log messages.
     */
    static void RegisterConsumer(IConsumer &consumer);

    /**
     * @brief Send log message to all the registered consumers.
     *
     * This function is used to send log messages to the registered consumers.
     *
     * @param[in] message Pointer to the log message.
     * @param[in] length Length of the log message.
     * @param[in] level Log level of the message.
     */
    static void SendLog(const uint8_t* message, size_t length, int level);

private:
#ifdef CONFIG_LIB_COMMONS_LOGGING_ASYNC
    /**
     * @brief Thread entry function for the log dispatcher.
     * This function will run in a loop, pulling log messages from the queue
     * and dipatching them to the appropriate output (e.g., stdout, UART).
     *
     * @param arg1 Unused argument.
     * @param arg2 Unused argument.
     * @param arg3 Unused argument.
     */
    static void Run(void* arg1, void* arg2, void* arg3);
#endif

    static IConsumer* mIConsumers[CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS];           // Array of registered consumers
};
