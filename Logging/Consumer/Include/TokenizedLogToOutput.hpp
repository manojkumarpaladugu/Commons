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
#include "Assert.h"

#include <pw_tokenizer/base64.h>

// ----------------------------------------------------------------------------
// Class definition
// ----------------------------------------------------------------------------

class TokenizedLogToOutput : public LogToOutput
{
protected:

    /**
     * @brief Converts the raw log message to a Base64 encoded string.
     *
     * @param[in] pRawMessage Pointer to the raw log message data.
     * @param[in] rawMessageLength Length of the raw log message data.
     * @param[in] base64MessageLength Reference to store the length of the Base64 encoded message.
     *
     * @return Pointer to the Base64 encoded message buffer, or nullptr if encoding fails.
     */
    const char* ConvertToBase64(const uint8_t* pRawMessage, size_t rawMessageLength, size_t &base64MessageLength)
    {
        ASSERT(pRawMessage != nullptr);
        ASSERT(rawMessageLength > 0);

        const size_t cBase64Size = pw::tokenizer::Base64EncodedBufferSize(rawMessageLength);
        if (cBase64Size > mBase64BufferSize)
        {
            return nullptr;
        }

        base64MessageLength = pw::tokenizer::PrefixedBase64Encode(pw::span(pRawMessage, rawMessageLength),
                                                                  pw::span(mBase64Buffer));
        ASSERT(base64MessageLength == (cBase64Size - 1));

        return mBase64Buffer;
    }

    static constexpr size_t mBase64BufferSize = pw::tokenizer::Base64EncodedBufferSize(CONFIG_LIB_COMMONS_LOGGING_BUFFER_SIZE) + 1;
    char mBase64Buffer[mBase64BufferSize];
};
