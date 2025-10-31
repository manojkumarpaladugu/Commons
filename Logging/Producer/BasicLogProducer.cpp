/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

#include "CommonTypes.h"
#include "Assert.h"
#include "LogCore.hpp"

#include <cstdio>
#include <pw_log_string/handler.h>

/**
 * @brief Implementation of the log message handler used as backend for pw_log_string.handler.
 *
 * This function prints the log message to stdout. It is called by the pigweed logging.
 *
 * @param[in] level The log level of the message.
 * @param[in] flags The flags associated with the log message.
 * @param[in] module_name The name of the module generating the log message.
 * @param[in] file_name The name of the file where the log message is generated.
 * @param[in] line_number The line number in the file where the log message is generated.
 * @param[in] message The log message.
 * @param[in] args The variable argument list.
 */
void pw_log_string_HandleMessageVaList(int level,
                                       unsigned int flags,
                                       const char* module_name,
                                       const char* file_name,
                                       int line_number,
                                       const char* message,
                                       va_list args)
{
    UNUSED(level);
    UNUSED(flags);
    UNUSED(module_name);
    UNUSED(file_name);
    UNUSED(line_number);
    ASSERT(message != NULL);

    // Format the log message into the buffer
    constexpr size_t cBufferSize = CONFIG_COMMONS_LOGGING_BUFFER_SIZE + 1;
    uint8_t formattedMessage[cBufferSize];
    size_t formattedMessageLength = vsnprintf(reinterpret_cast<char*>(formattedMessage), cBufferSize, message, args);
    ASSERT(formattedMessageLength > 0 && formattedMessageLength < cBufferSize);

    // Send the formatted log message
    LogCore::HandleLogMessage(formattedMessage, formattedMessageLength, level);
}
