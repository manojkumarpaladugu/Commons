/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

#pragma once

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include <cstdint>
#include <cstddef>

// ----------------------------------------------------------------------------
// Datatype definitions
// ----------------------------------------------------------------------------

typedef struct
{
    void*   pBuffer;        // Pointer to the log buffer
    size_t  size;           // Size of the log buffer
    size_t  head;           // Head index for the log buffer
    size_t  tail;           // Tail index for the log buffer
} LogQueue_t;

// ----------------------------------------------------------------------------
// Class definition
// ----------------------------------------------------------------------------

class LogQueue
{
public:
    /**
     * @brief Initialize the log queue with a buffer.
     *
     * This method initializes the log queue with a buffer that will be used to store log messages.
     *
     * @param[in] pBuffer A pointer to the log buffer.
     * @param[in] size The size of the log buffer.
     */
    static void Initialize(void* pBuffer, size_t size);

    /**
     * @brief Push a log message to the log queue.
     *
     * This method is used to send a log message to the log queue.
     *
     * @param[in] pMessage A pointer to the log message.
     * @param[in] messageLength The length of the log message.
     * @param[in] level The log level of the message.
     */
    static void PushLog(const uint8_t* pMessage, size_t messageLength, int level);

    /**
     * @brief Pull a log message from the log queue.
     *
     * This method retrieves a log message from the log queue.
     *
     * @param[in] pMessage A pointer to the buffer where the log message will be retrieved.
     * @param[out] messageLength The length of the retrieved log message.
     * @param[out] level The log level of the retrieved message.
     */
    static void PullLog(uint8_t* pMessage, size_t &messageLength, int &level);

private:
    static LogQueue_t     mLogQueue;           // Queue to store log messages
};