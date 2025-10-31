#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

if (CONFIG_COMMONS_LOGGING_DEFERRED)
    target_compile_definitions(${COMMONS_LOGGING_LIBRARY_NAME}
        PUBLIC
            CONFIG_COMMONS_LOGGING_DEFERRED=1
    )

    if (CONFIG_COMMONS_LOGGING_OVERFLOW)
        target_compile_definitions(${COMMONS_LOGGING_LIBRARY_NAME}
            PUBLIC
                CONFIG_COMMONS_LOGGING_OVERFLOW=1
        )
    endif()

    target_include_directories(${COMMONS_LOGGING_LIBRARY_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_sources(${COMMONS_LOGGING_LIBRARY_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/LogQueue.cpp)
endif()
