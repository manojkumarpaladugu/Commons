# Logging

The Logging library which is part of the large collection of Commons module
provides an interface for the application to print string messages on whatever
the output (eg: UART, JTAG, Memory, etc...) it needs.

It uses [Google's pigweed](https://pigweed.dev/) library, specifically pw_log
and pw_tokenizer for implementing the backend functionality.

## Interface

Logging levels are used to filter and manage the vast amount of information
that a running program can produce.

* LOG_LEVEL_OMIT: For logs that need not be outputted.
* LOG_LEVEL_DEBUG: Messages at this level are intended for developers during the
                   development phase.
* LOG_LEVEL_INFO: Messages at this level describe the progress of the application
                  at a high level.
* LOG_LEVEL_WARN: Messages at this level are "heads-up" for something that
                  might need attention.
* LOG_LEVEL_ERROR: Messages at this level signifies a serious problem that has
                   occurred and prevents a specific operation or part of the
                   application from functioning correctly.
* LOG_LEVEL_CRITICAL: This is the highest level of severity, indicating a
                      severe error that could lead to application instability,
                      data loss, or the application crashing entirely.

To use logging, the following macros need to be defined first.
Then include the 'Logging.h' header file in source files.

* LOG_MODULE_NAME: Defines the name of the module from which the logging
                   messages are coming. `Default is 'MODULE'`.
* MODULE_LOG_LEVEL: Defines the minimum log level for which logs from this
                    source file are outputted. `Default is 'LOG_LEVEL_DEBUG'`.
* LOG_FORMAT(level, module, file, line, message) - Defines the format of log
        strings from this source file.
        `Default is 'level " " module "|" file ":" line " - " message "\n"'`.

The macros `LOG_MODULE_NAME` and `MODULE_LOG_LEVEL` can be defined per module
or the entire application through CMake file.

```cmake
target_compile_definitions(<module or app>
    <PRIVATE or PUBLIC>
        LOG_MODULE_NAME="MY_MODULE"
        MODULE_LOG_LEVEL=LOG_LEVEL_DEBUG
)
```

Otherwise, they can be defined in source file before including the Logging.h.

```c
// filename: Main.cpp
#define LOG_MODULE_NAME "main"
#define MODULE_LOG_LEVEL LOG_LEVEL_DEBUG
#define LOG_FORMAT(level, module, file, line, message) level " " module "|" file ":" line " - " message "\n"

// Must be included only after defining the above macros
#include "Logging.h"
```

For example, the following code snippet shows the usage of different logging macros.

```c
// filename: Main.cpp
int main(void)
{
    LOG_DEBUG("This is a debug message");
    LOG_INFO("This is an info message");
    LOG_WARN("This is a warning message");
    LOG_ERROR("This is an error message");
    LOG_CRITICAL("This is a critical message");
    ASSERT(false);
    return 0;
}
```

## Configuration

This describes the configuration options for the Common Logging Library,
typically set via a CMake or a Kconfig like system. These options allow you to
customize the behavior and features of the logging facility within your
application or system.

| Option Name | Type | Default | Dependencies | Description |
|---|---|---|---|---|
| `CONFIG_LIB_COMMONS_LOGGING` | `bool` | `n` | None | Enables or disables the entire common logging library. |
| `CONFIG_LIB_COMMONS_LOGGING_TOKENIZED` | `bool` | `n` | `CONFIG_LIB_COMMONS_LOGGING` | Enables string tokenization mode for logging messages. When enabled, log messages are converted into numerical tokens, which can reduce memory footprint and improve logging performance, especially in resource-constrained environments. |
| `CONFIG_LIB_COMMONS_LOGGING_ASYNC` | `bool` | `n` | `CONFIG_LIB_COMMONS_LOGGING` | Enables asynchronous logging. This option utilizes an internal queue to buffer log messages, allowing the logging operations to be non-blocking for the main application thread. A consumer thread pulls messages from the internal queue and forwards to all the registered consumers. |
| `CONFIG_LIB_COMMONS_LOGGING_BUFFER_SIZE` | `int` | `128` | None | Sets the maximum size of the internal buffer used for storing logging messages. This is particularly relevant when asynchronous logging is enabled. The value must be between 64 and 256 characters. |
| `CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS` | `int` | `1` | None | Defines the maximum number of consumer entities (e.g., threads or tasks) that can simultaneously process and output log messages to the different outputs (eg: Stdout, UART and Memory). |
| `CONFIG_LIB_COMMONS_LOGGING_BASE64_ENCODING` | `bool` | `n` | `CONFIG_LIB_COMMONS_LOGGING_TOKENIZED` | Enables Base64 encoding for tokenized log messages. This is useful for ensuring that tokenized (potentially binary) log data can be safely transmitted or stored in systems that primarily handle text-based data. This option only takes effect if `CONFIG_LIB_COMMONS_LOGGING_TOKENIZED` is also enabled. |

Set THIRD_PARTY_DIR variable to the path where third party libraries needs to
be stored.

```cmake
set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty")
```

Enable logging functionality.

```cmake
set(CONFIG_LIB_COMMONS_LOGGING ON)
```

### Producer

#### Basic Backend

Disable tokenized backend to directly output plaintext log messages.

```cmake
set(CONFIG_LIB_COMMONS_LOGGING_TOKENIZED OFF)
```

#### Tokenized Backend

Otherwise, enable tokenized backend to replace strings with 32-bit tokens.This
conserves space in final binary and reduces load on data channels.

```cmake
set(CONFIG_LIB_COMMONS_LOGGING_TOKENIZED ON)
```

Add below linker sections to your linker script. Because pw_tokenizer stores the
mapping of strings with 32-bit tokens in the below linker sections.

Please see <THIRD_PARTY_DIR>/pigweed/pw_tokenizer/pw_tokenizer_linker_sections.ld.

```linker
.pw_tokenizer.info 0x0 (INFO) :
{
    KEEP(*(.pw_tokenizer.info))
}

.pw_tokenizer.entries 0x0 (INFO) :
{
    KEEP(*(.pw_tokenizer.entries.*))
    KEEP(*(.rodata.*_pw_tokenizer_string_entry_*))
}
```

### Consumer

Define maximum buffer size to store log messages.

```cmake
set(CONFIG_LIB_COMMONS_LOGGING_BUFFER_SIZE 128)
```

Define maximum number of consumers possible to register for receiving log messages.

```cmake
set(CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS 1)
```

The script 'serial_detokenizer.py' requires the data stream to be in base64
encoding to be able to output the detokenized logs on serial console. So, the
project must have built with below option enabled.

```cmake
set(CONFIG_LIB_COMMONS_LOGGING_BASE64_ENCODING ON)
```

Create a consumer to process the log messages and send to required output
(eg: UART, JTAG, Memory, etc...)

```c
#include "LogToOutput.hpp"

enum LogConsumerId
{
    cLogToUartId = 0,     ///< Log consumer for UART output
    cMaxLogConsumerId     ///< Maximum number of log consumers
};
COMPILE_ASSERT(cMaxLogConsumerId == CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS, "cMaxLogConsumerId exceeds CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS");

class LogToUart final : public LogToOutput
{
public:

    /**
     * @brief Initialize the log consumer for UART output.
     */
    void Initialize() override
    {

    }

    /**
     * @brief Process a log message and output it to UART
     *
     * @param[in] pMessage Pointer to the log message.
     * @param[in] length Length of the log message.
     */
    void ProcessLogMessage(const uint8_t* pMessage, size_t length) override
    {
        const uint8_t* pLogMessage = pMessage;
        size_t messageLength = length;

    #if CONFIG_LIB_COMMONS_LOGGING_BASE64_ENCODING
        size_t base64MessageLength = 0;
        const char* pBase64Message = ConvertToBase64(pLogMessage, messageLength, base64MessageLength);
        if( pBase64Message != nullptr)
        {
            pLogMessage = reinterpret_cast<const uint8_t*>(pBase64Message);
            messageLength = base64MessageLength;
        }
    #endif

        // Output the log message to UART
    }
};
```

Register the new consumer with logging core for receiving log messages.

```c
static LogToUart logToUart;
LogCore::RegisterConsumer(cLogToUartId, logToUart);
```

### Asynchronous

Handling log messages is a low priority task. So, Zephyr based builds can
enable below setting to push the log messages into a queue first and later
send them to consumer(s) in thread context.

```cmake
set(CONFIG_LIB_COMMONS_LOGGING_ASYNC ON)
```

Create a queue and start the logging core to start sending the log messages
to consumer(s).

```c
#include "LogCore.hpp"

#if CONFIG_LIB_COMMONS_LOGGING_ASYNC
    // Allocate a static buffer to store log messages
    static uint8_t logBuffer[1024];
    LogCore::InitializeQueue(logBuffer, sizeof(logBuffer));

    // Start the log core to process the queue
    LogCore::Start();
#endif
```

### Redirect Zephyr logs to Commons logging

Configure Zephyr logging subsystem to redirect it's logs to custom logging framework.

```kconfig
CONFIG_LOG=y
CONFIG_LOG_PRINTK=y
CONFIG_LOG_CUSTOM_HEADER=y
```

Define a header file (zephyr_custom_log.h) to redirect the logs from zephyr
logging macros to Commons logging macros.

```c
#pragma once

#define MODULE_NAME "Zephyr"

#include <zephyr/logging/log_core.h>
#include <zephyr/sys/__assert.h>

#include "Logging.h"

#undef LOG_DBG
#undef LOG_INF
#undef LOG_WRN
#undef LOG_ERR

#define Z_COMMONS_LOG(_level, customLogMacro, fmt, ...) \
    do {                                                \
        if (!Z_LOG_CONST_LEVEL_CHECK(_level)) {         \
            break;                                      \
        }                                               \
        customLogMacro(fmt, ##__VA_ARGS__);             \
    } while(false)

#define LOG_DBG(fmt, ...) \
    Z_COMMONS_LOG(LOG_LEVEL_DBG, LOG_DEBUG, fmt, ##__VA_ARGS__)

#define LOG_INF(fmt, ...) \
    Z_COMMONS_LOG(LOG_LEVEL_INF, LOG_INFO, fmt, ##__VA_ARGS__)

#define LOG_WRN(fmt, ...) \
    Z_COMMONS_LOG(LOG_LEVEL_WRN, LOG_WARN, fmt, ##__VA_ARGS__)

#define LOG_ERR(fmt, ...) \
    Z_COMMONS_LOG(LOG_LEVEL_ERR, LOG_ERROR, fmt, ##__VA_ARGS__)
```

In CMake, include the path to zephyr_custom_log.h

```cmake
zephyr_include_directories(/path/to/customlogheader)
```

## Detokenize Logs

Create and activate a python virtual environment

```bash
python -m venv ~/.venv
source ~/.venv/bin/activate
```

Install the dependencies

```bash
pip install -e <THIRD_PARTY_DIR>/pigweed/pw_tokenizer/py
```

Generate token database from an ELF file

```bash
python3 <THIRD_PARTY_DIR>/pigweed/pw_tokenizer/py/pw_tokenizer/database.py create -d token_database.csv -t csv <ELF file>
```

Live serial detokenization,

```bash
python3 <THIRD_PARTY_DIR>/pigweed/pw_tokenizer/py/pw_tokenizer/serial_detokenizer.py -b <SERIAL-BAUD-RATE> -d <SERIAL-PORT> token_database.csv
```
