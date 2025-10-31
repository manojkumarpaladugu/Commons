#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

target_include_directories(${APPLICATION_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_sources(${APPLICATION_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/LogToStdOut.cpp
)
