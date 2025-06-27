#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

# Add the macro as a preprocessor definition
target_compile_definitions(${COMMONS_LOGGING_LIBRARY_NAME}
    PRIVATE
        CONFIG_LIB_COMMONS_LOGGING_MAX_STRING_LENGTH=${CONFIG_LIB_COMMONS_LOGGING_MAX_STRING_LENGTH}
)

set(SOURCE_LIST)
set(LINK_LIBS pw_log)

# Configure pigweed's backend before fetching pigweed library
if (CONFIG_LIB_COMMONS_TOKENIZED_LOGGING)
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

    list(APPEND SOURCE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/TokenizedLogToStdout.cpp)
else()
    set(pw_log_BACKEND
        pw_log_string
        CACHE STRING "Use the string backend for pigweed logging"
    )

    set(pw_log_string.handler_BACKEND
        ${COMMONS_LOGGING_LIBRARY_NAME}
        CACHE STRING "Current library implements the message handler for pw_log_string"
    )

    list(APPEND SOURCE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/BasicLogToStdout.cpp)
endif()

target_sources(${COMMONS_LOGGING_LIBRARY_NAME} PRIVATE ${SOURCE_LIST})

target_link_libraries(${COMMONS_LOGGING_LIBRARY_NAME} PUBLIC ${LINK_LIBS})
