#
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required(VERSION 4.0.0)

set(COMMONS_LIBRARY_NAME commons)
add_library(${COMMONS_LIBRARY_NAME} STATIC)

target_include_directories(${COMMONS_LIBRARY_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(${COMMONS_LIBRARY_NAME}
    PRIVATE commons.cc
)

add_subdirectory(logging)
