#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

if(CONFIG_LIB_COMMONS_LOGGING)
    set(COMMONS_LOGGING_LIBRARY_NAME CommonsLogging)
    add_library(${COMMONS_LOGGING_LIBRARY_NAME} STATIC)

    target_link_libraries(${COMMONS_LIBRARY_NAME}
        PUBLIC ${COMMONS_LOGGING_LIBRARY_NAME}
    )

    target_include_directories(${COMMONS_LOGGING_LIBRARY_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Include
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include
    )

    add_subdirectory(Adapters)
endif()
