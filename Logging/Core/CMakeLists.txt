#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

target_sources(${COMMONS_LOGGING_LIBRARY_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/LogThread.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LogCore.cpp
)
