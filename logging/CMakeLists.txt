#
# SPDX-License-Identifier: Apache-2.0
#

if(CONFIG_LIB_COMMONS_LOGGING)
    set(COMMONS_LOGGING_LIBRARY_NAME commons-logging)
    add_library(${COMMONS_LOGGING_LIBRARY_NAME} STATIC)

    target_link_libraries(${COMMONS_LIBRARY_NAME}
        PUBLIC ${COMMONS_LOGGING_LIBRARY_NAME}
    )

    target_include_directories(${COMMONS_LOGGING_LIBRARY_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    add_subdirectory(adapters)
endif()
