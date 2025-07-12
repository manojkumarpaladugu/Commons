/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

#define LOG_MODULE_NAME "MAIN"
#define MODULE_LOG_LEVEL LOG_LEVEL_DEBUG

// Must be included after the logging module name and logging level definitions
#include "Logging.h"

int main(void)
{
    LOG_INFO("Hello world!");
    return 0;
}
