#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

cmake_minimum_required(VERSION 4.0.0)

set(COMMONS_LIBRARY_NAME Commons)
add_library(${COMMONS_LIBRARY_NAME} STATIC)

target_include_directories(${COMMONS_LIBRARY_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_sources(${COMMONS_LIBRARY_NAME}
    PRIVATE Commons.cpp
)

add_subdirectory(Logging)
