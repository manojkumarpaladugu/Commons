#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

if(NOT DEFINED CONFIG_LIB_COMMONS_LOGGING_ASYNC)
    message(FATAL_ERROR "CONFIG_LIB_COMMONS_LOGGING_ASYNC is not defined.\
                         Please set whether to use asynchronous logging or not.")
endif()

if (CONFIG_LIB_COMMONS_LOGGING_ASYNC)
    target_include_directories(${COMMONS_LOGGING_LIBRARY_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_sources(${COMMONS_LOGGING_LIBRARY_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/LogQueue.cpp)
endif()