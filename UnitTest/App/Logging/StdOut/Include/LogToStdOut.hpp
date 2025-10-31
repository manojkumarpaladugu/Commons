/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

#pragma once

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "LogConsumerId.h"
#include "LogToOutput.hpp"

// ----------------------------------------------------------------------------
// Class definition
// ----------------------------------------------------------------------------

class LogToStdOut final: public LogToOutput
{
public:

    /**
     * @brief Initialization.
     */
    void Initialize() override;

    /**
     * @brief Process a log message and output it to standard output.
     *
     * @param[in] pMessage Pointer to the log message.
     * @param[in] length Length of the log message.
     */
    void ProcessLogMessage(const uint8_t* pMessage, size_t length) override;
};
