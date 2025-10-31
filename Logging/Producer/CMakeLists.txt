#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

if(NOT DEFINED CONFIG_COMMONS_LOGGING_BUFFER_SIZE)
    message(FATAL_ERROR "CONFIG_COMMONS_LOGGING_BUFFER_SIZE is not defined.\
                         Please set the logging buffer size.")
endif()

target_compile_definitions(${COMMONS_LOGGING_LIBRARY_NAME}
    PUBLIC
        CONFIG_COMMONS_LOGGING_BUFFER_SIZE=${CONFIG_COMMONS_LOGGING_BUFFER_SIZE}
)

set(LOG_PRODUCER_SRC_LIST)
set(LOG_PRODUCER_LINK_LIBS pw_log)

# Configure pigweed's backend before fetching pigweed library
if (CONFIG_COMMONS_LOGGING_TOKENIZED)
    target_compile_definitions(${COMMONS_LOGGING_LIBRARY_NAME}
        PUBLIC
            CONFIG_COMMONS_LOGGING_TOKENIZED=1
    )

    set(pw_log_BACKEND
        pw_log_tokenized
        CACHE STRING "Use the tokenized backend for pigweed logging"
    )

    set(pw_log_tokenized.handler_BACKEND
        ${COMMONS_LOGGING_LIBRARY_NAME}
        CACHE STRING "Current library implements the message handler for pw_log_tokenized"
    )

    set(pw_assert.assert_BACKEND
        pw_assert.print_and_abort_assert_backend
        CACHE STRING "Use the print and abort backend for pw_assert.assert"
    )

    set(pw_assert.check_BACKEND
        pw_assert.print_and_abort_check_backend
        CACHE STRING "Use the print and abort backend for pw_assert.check"
    )

    list(APPEND LOG_PRODUCER_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/TokenizedLogProducer.cpp)

    if (CONFIG_COMMONS_LOGGING_BASE64_ENCODING)
        target_compile_definitions(${COMMONS_LOGGING_LIBRARY_NAME}
            PUBLIC
                CONFIG_COMMONS_LOGGING_BASE64_ENCODING=1
        )
        list(APPEND LOG_PRODUCER_LINK_LIBS pw_tokenizer.base64)
    endif()
else()
    set(pw_log_BACKEND
        pw_log_string
        CACHE STRING "Use the string backend for pigweed logging"
    )

    set(pw_log_string.handler_BACKEND
        ${COMMONS_LOGGING_LIBRARY_NAME}
        CACHE STRING "Current library implements the message handler for pw_log_string"
    )

    list(APPEND LOG_PRODUCER_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/BasicLogProducer.cpp)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/FetchPigweed.cmake)

target_include_directories(${COMMONS_LOGGING_LIBRARY_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_sources(${COMMONS_LOGGING_LIBRARY_NAME}
    PRIVATE
        ${LOG_PRODUCER_SRC_LIST}
)

target_link_libraries(${COMMONS_LOGGING_LIBRARY_NAME}
    PUBLIC
        ${LOG_PRODUCER_LINK_LIBS}
)
