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

class IConsumer
{
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~IConsumer() = default;

    /**
     * @brief Process a log message.
     *
     * This function is called to process a log message. The implementation
     * should handle the log message appropriately
     *
     * @param[in] message Pointer to the log message.
     * @param[in] length Length of the log message.
     * @param[in] level Log level of the message.
     */
    virtual void ProcessLog(const uint8_t* message, size_t length, int level) = 0;
};
