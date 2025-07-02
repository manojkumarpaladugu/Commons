/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

#include "CommonTypes.h"
#include "Assert.h"

#include <cstdio>
#include <pw_log_tokenized/handler.h>
#include <pw_log_tokenized/metadata.h>

/**
 * @brief Implementation of the log message handler used as backend for pw_log_tokenized.handler
 * 
 * This function prints the encoded message to stdout. It is called by the pigweed logging.
 * 
 * @param[in] metadata The metadata associated with the log message (level, line, flag and module).
 * @param[in] encoded_message The encoded log message.
 * @param[in] size_bytes The size of the encoded message in bytes.
 *
 */
void pw_log_tokenized_HandleLog(uint32_t metadata,
                                const uint8_t encoded_message[],
                                size_t size_bytes)
{
    ASSERT(encoded_message != nullptr);
    pw::log_tokenized::Metadata log_metadata(metadata);
    fwrite(encoded_message, sizeof(uint8_t), size_bytes, stdout);
    fflush(stdout);
}