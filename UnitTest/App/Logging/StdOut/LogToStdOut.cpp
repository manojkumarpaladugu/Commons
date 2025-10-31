/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "Assert.h"
#include "LogToStdOut.hpp"

#include <cstdio>

// ----------------------------------------------------------------------------
// Public functions
// ----------------------------------------------------------------------------

void LogToStdOut::Initialize()
{
    // Initialization if needed.
}

void LogToStdOut::ProcessLogMessage(const uint8_t* pMessage, size_t length)
{
    ASSERT(pMessage != nullptr);
    ASSERT(length > 0);

    const uint8_t* pLogMessage = pMessage;
    size_t messageLength = length;

#if CONFIG_COMMONS_LOGGING_BASE64_ENCODING
    size_t base64MessageLength = 0;
    const char* pBase64Message = ConvertToBase64(pLogMessage, messageLength, base64MessageLength);
    if( pBase64Message != nullptr)
    {
        pLogMessage = reinterpret_cast<const uint8_t*>(pBase64Message);
        messageLength = base64MessageLength;
    }
#endif

    printf("%.*s\n", (int)messageLength, pLogMessage);
}
