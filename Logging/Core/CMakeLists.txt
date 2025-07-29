#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

if(DEFINED CONFIG_LIB_COMMONS_LOGGING_DEFERRED AND NOT DEFINED CONFIG_LIB_COMMONS_LOGGING_THRESHOLD)
    message(FATAL_ERROR "CONFIG_LIB_COMMONS_LOGGING_THRESHOLD is not defined.\
                         Please set the threshold.")
endif()

set(LOG_CORE_SRC_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/LogCore.cpp
)

target_include_directories(${COMMONS_LOGGING_LIBRARY_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_sources(${COMMONS_LOGGING_LIBRARY_NAME}
    PRIVATE
        ${LOG_CORE_SRC_LIST}
)
