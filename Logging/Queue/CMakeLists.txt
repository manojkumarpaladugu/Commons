#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

if (CONFIG_LIB_COMMONS_LOGGING_ASYNC)
    target_include_directories(${COMMONS_LOGGING_LIBRARY_NAME}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Include
    )

    target_sources(${COMMONS_LOGGING_LIBRARY_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/LogQueue.cpp)
endif()