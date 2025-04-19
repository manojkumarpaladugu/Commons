#
# SPDX-License-Identifier: Apache-2.0
#

if(CONFIG_LIB_COMMONS_LOGGING)
    set(COMMONS_LOGGING_LIBRARY_NAME CommonsLogging)
    add_library(${COMMONS_LOGGING_LIBRARY_NAME} STATIC)

    target_include_directories(${COMMONS_LOGGING_LIBRARY_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    add_subdirectory(adapters)
endif()
