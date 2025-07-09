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
// Class definition
// ----------------------------------------------------------------------------

class LogToOutput
{
public:

    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~LogToOutput() = default;

    /**
     * @brief Initialize the log consumer.
     */
    virtual void Initialize() = 0;

    /**
     * @brief Process a log message.
     *
     * This function is called to process a log message. The implementation
     * should handle the log message appropriately
     *
     * @param[in] pMessage Pointer to the log message.
     * @param[in] length Length of the log message.
     */
    virtual void ProcessLogMessage(const uint8_t* pMessage, size_t length) = 0;

    void SetId(uint8_t id)
    {
        mId = id;
    }

private:

    uint8_t     mId;    // Unique identifier for the consumer
};
