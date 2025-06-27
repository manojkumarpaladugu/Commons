#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

cmake_minimum_required(VERSION 4.0.0)

project(Commons-UnitTest LANGUAGES CXX)

set(EXECUTABLE_NAME app)
add_executable(${EXECUTABLE_NAME})

set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty)

# Include Commons library with logging enabled
set(CONFIG_LIB_COMMONS_LOGGING y)
set(CONFIG_LIB_COMMONS_TOKENIZED_LOGGING n)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/Commons)

target_sources(${EXECUTABLE_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Main.cpp
)

target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE
        Commons
)
