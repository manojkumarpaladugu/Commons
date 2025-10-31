#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

cmake_minimum_required(VERSION 4.0.0)

project(Logging-UnitTest LANGUAGES CXX)

set(APPLICATION_NAME app)
add_executable(${APPLICATION_NAME})

set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty)

# Include Commons library and enable features
set(CONFIG_COMMONS_LOGGING ON)
set(CONFIG_COMMONS_LOGGING_TOKENIZED ON)
set(CONFIG_COMMONS_LOGGING_BASE64_ENCODING ON)
set(CONFIG_COMMONS_LOGGING_BUFFER_SIZE 128)
set(CONFIG_COMMONS_LOGGING_MAX_CONSUMERS 1)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../.. ${CMAKE_CURRENT_BINARY_DIR}/Commons)

add_subdirectory(StdOut)

target_sources(${APPLICATION_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
)

target_link_libraries(${APPLICATION_NAME}
    PRIVATE
        Commons
)
