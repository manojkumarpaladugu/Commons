#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

if(NOT DEFINED CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS)
    message(FATAL_ERROR "CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS is not defined.\
                         Please set the max number of consumers.")
endif()

target_compile_definitions(${COMMONS_LOGGING_LIBRARY_NAME}
    PRIVATE
        CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS=${CONFIG_LIB_COMMONS_LOGGING_MAX_CONSUMERS}
)

target_include_directories(${COMMONS_LOGGING_LIBRARY_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${COMMONS_LOGGING_LIBRARY_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/LogConsumer.cpp
)
