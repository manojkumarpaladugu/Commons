#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

set(LOG_CORE_SRC_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/LogCore.cpp
)

if(LIB_COMMONS_LOGGING_ASYNC)
    list(APPEND LOG_CORE_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/LogThread.cpp)
endif()

target_include_directories(${COMMONS_LOGGING_LIBRARY_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_sources(${COMMONS_LOGGING_LIBRARY_NAME}
    PRIVATE
        ${LOG_CORE_SRC_LIST}
)
