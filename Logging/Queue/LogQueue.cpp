/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "LogQueue.hpp"
#include "Assert.h"

#include <algorithm>

// ----------------------------------------------------------------------------
// Macro definitions
// ----------------------------------------------------------------------------

#define LOG_METADATA_SIGNATURE 0xDEADBEEF

// ----------------------------------------------------------------------------
// Datatype definitions
// ----------------------------------------------------------------------------

typedef struct __attribute__((packed)) LogMetadata
{
    uint32_t    signature;          // Signature for identifying valid log message
    uint32_t    sequenceNumber;     // Sequence number for the log message
    uint32_t    length;             // Length of the log message
    uint8_t     level;              // Log level
} LogMetadata_t;

// ----------------------------------------------------------------------------
// Variable definitions
// ----------------------------------------------------------------------------

LogQueue_t LogQueue::mLogQueue;
uint8_t LogQueue::mMessageBuffer[cLogMessageBufferSize + 1];
uint32_t LogQueue::mSequenceNumber = 0;

// ----------------------------------------------------------------------------
// Public functions
// ----------------------------------------------------------------------------

void LogQueue::Initialize(void* pBuffer, size_t size)
{
    ASSERT(pBuffer != NULL);
    ASSERT(size > sizeof(LogMetadata_t));

    mLogQueue.pBuffer = pBuffer;
    mLogQueue.size = size;
    mLogQueue.head = 0;
    mLogQueue.tail = 0;
}

int LogQueue::PushLog(const uint8_t* pMessage, size_t messageLength, int level)
{
    ASSERT(pMessage != NULL);
    ASSERT(messageLength > 0);

    uint8_t* pQueueBuffer = static_cast<uint8_t*>(mLogQueue.pBuffer);
    size_t queueSize = mLogQueue.size;
    size_t head = mLogQueue.head;
    size_t &tail = mLogQueue.tail;

    ASSERT(pQueueBuffer != NULL);
    ASSERT(queueSize > sizeof(LogMetadata_t));

    size_t totalMessageLength = std::min(messageLength + sizeof(LogMetadata_t), queueSize - 1);
    if (totalMessageLength > queueSize)
    {
        // Message is too large to fit in the buffer even when empty
        return -EMSGSIZE;
    }

    // Check if enough space is available in the log buffer
    size_t availableSpace = 0;
    if (tail >= head)
    {
        // Normal case: If tail is ahead of head, available space is total space - used space
        availableSpace = queueSize - (tail - head);
    }
    else
    {
        // Wrap around case: If tail is behind head, available space is from tail to head
        availableSpace = head - tail;
    }

    if (totalMessageLength > availableSpace)
    {
    #if CONFIG_COMMONS_LOGGING_OVERFLOW
        // Not enough space, drop oldest messages
        mLogQueue.head = tail;
    #else
        return -ENOBUFS;
    #endif
    }

    // Create metadata for the log message
    uint32_t messageLengthToCopy = static_cast<uint32_t>(totalMessageLength - sizeof(LogMetadata_t));
    LogMetadata_t metadata = { .signature      = LOG_METADATA_SIGNATURE,
                               .sequenceNumber = mSequenceNumber++ % UINT32_MAX,
                               .length         = messageLengthToCopy,
                               .level          = static_cast<uint8_t>(level) };

    // Copy the metadata to the log buffer
    for (size_t i = 0; i < sizeof(LogMetadata_t); ++i)
    {
        static_cast<uint8_t*>(pQueueBuffer)[tail] = reinterpret_cast<uint8_t*>(&metadata)[i];
        tail = (tail + 1) % queueSize;      // Wrap around if needed
    }

    // Copy the log message to the log buffer
    for (size_t i = 0; i < messageLengthToCopy; ++i)
    {
        static_cast<uint8_t*>(pQueueBuffer)[tail] = pMessage[i];
        tail = (tail + 1) % queueSize;      // Wrap around if needed
    }

    return 0;
}

int LogQueue::PullLog(uint8_t* &pMessage, size_t &messageLength, int &level)
{
    uint8_t* pQueueBuffer = static_cast<uint8_t*>(mLogQueue.pBuffer);
    size_t queueSize = mLogQueue.size;
    size_t &head = mLogQueue.head;
    size_t tail = mLogQueue.tail;

    ASSERT(pQueueBuffer != NULL);
    ASSERT(queueSize > sizeof(LogMetadata_t));

    // Check if the buffer has data to read
    if (head == tail)
    {
        return -ENODATA; // No data available
    }

    size_t availableData = 0;
    if (head <= tail)
    {
        // Normal case: If head is behind tail, available data is from head to tail
        availableData = tail - head;
    }
    else
    {
        // Wrap around case: If head is ahead of tail, available data is total space - free space
        availableData = queueSize - (head - tail);
    }

    if (availableData < sizeof(LogMetadata_t))
    {
        return -EBADMSG; // Not enough data to read metadata
    }

    // Read the metadata from the queue buffer
    LogMetadata_t metadata;
    for (size_t i = 0; i < sizeof(LogMetadata_t); ++i)
    {
        reinterpret_cast<uint8_t*>(&metadata)[i] = static_cast<uint8_t*>(pQueueBuffer)[head];
        head = (head + 1) % queueSize;      // Wrap around if needed
    }

    if (metadata.signature != LOG_METADATA_SIGNATURE)
    {
        return -EBADMSG; // Invalid log message signature
    }

    level = metadata.level;
    messageLength = std::min(metadata.length, cLogMessageBufferSize);

    // Read the log message from the queue buffer
    for (size_t i = 0; i < messageLength; ++i)
    {
        mMessageBuffer[i] = static_cast<uint8_t*>(pQueueBuffer)[head];
        head = (head + 1) % queueSize;      // Wrap around if needed
    }

    // Set the output pointer to the message buffer
    pMessage = mMessageBuffer;

    return 0;
}
