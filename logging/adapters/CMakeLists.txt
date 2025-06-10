set(source_list)
set(link_libs pw_log)

if (CONFIG_LIB_COMMONS_TOKENIZED_LOGGING)
    set(pw_log_BACKEND
        pw_log_tokenized
        CACHE STRING "Use the tokenized backend for pigweed logging"
    )

    set(pw_log_tokenized.handler_BACKEND
        ${COMMONS_LOGGING_LIBRARY_NAME}
        CACHE STRING "Current library implements the message handler for pw_log_tokenized"
    )

    set(pw_assert.assert_BACKEND
        pw_assert.print_and_abort_assert_backend
        CACHE STRING "Use the print and abort backend for pw_assert.assert"
    )

    set(pw_assert.check_BACKEND
        pw_assert.print_and_abort_check_backend
        CACHE STRING "Use the print and abort backend for pw_assert.check"
    )

    list(APPEND source_list ${CMAKE_CURRENT_SOURCE_DIR}/tokenized_log_to_stdout.cc)
else()
    set(pw_log_BACKEND
        pw_log_string
        CACHE STRING "Use the string backend for pigweed logging"
    )

    set(pw_log_string.handler_BACKEND
        ${COMMONS_LOGGING_LIBRARY_NAME}
        CACHE STRING "Current library implements the message handler for pw_log_string"
    )

    list(APPEND source_list ${CMAKE_CURRENT_SOURCE_DIR}/basic_log_to_stdout.cc)
endif()

target_sources(${COMMONS_LOGGING_LIBRARY_NAME} PRIVATE ${source_list})

target_link_libraries(${COMMONS_LOGGING_LIBRARY_NAME} PUBLIC ${link_libs})
