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

#include <errno.h>

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
     *
     * @return int Returns 0 on success, otherwise returns an error code.
     */
    static int PushLog(const uint8_t* pMessage, size_t messageLength, int level);

    /**
     * @brief Pull a log message from the log queue.
     *
     * This method retrieves a log message from the log queue.
     *
     * @param[out] pMessage A pointer to the retrieved log message.
     * @param[out] messageLength The length of the retrieved log message.
     * @param[out] level The log level of the retrieved message.
     *
     * @return int Returns 0 on success, otherwise returns an error code.
     */
    static int PullLog(uint8_t* &pMessage, size_t &messageLength, int &level);

private:

    static LogQueue_t          mLogQueue;                                                   // Queue to store log messages
    inline static const size_t cLogMessageBufferSize = CONFIG_COMMONS_LOGGING_BUFFER_SIZE;  // Size of the log message buffer
    static uint8_t             mMessageBuffer[cLogMessageBufferSize + 1];                   // Buffer to hold the log message
    static uint32_t            mSequenceNumber;                                             // Sequence number for log messages
};
