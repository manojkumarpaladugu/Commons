#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
#

# Fetch the pigweed library
if(NOT DEFINED THIRD_PARTY_DIR)
    message(FATAL_ERROR "THIRD_PARTY_DIR is not defined.")
endif()

include(FetchContent)
if(NOT EXISTS "${THIRD_PARTY_DIR}/pigweed/CMakeLists.txt")
    message(STATUS "Fetching Pigweed library from remote repository...")
    FetchContent_Declare(
        pigweed
        SYSTEM SOURCE_DIR "${THIRD_PARTY_DIR}/pigweed"
        URL https://pigweed.googlesource.com/pigweed/pigweed/+archive/90d1391ff0c2fcb4717dc578bceccb2ec38643b8.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
else()
    message(STATUS "Pigweed is already available locally at ${THIRD_PARTY_DIR}/pigweed")
    FetchContent_Declare(
        pigweed
        SYSTEM SOURCE_DIR "${THIRD_PARTY_DIR}/pigweed"
    )
endif()

if(NOT DEFINED ENV{PW_ROOT})
    set(ENV{PW_ROOT} "${THIRD_PARTY_DIR}/pigweed")
else()
    message(STATUS "PW_ROOT is set to: $ENV{PW_ROOT}")
endif()

FetchContent_MakeAvailable(pigweed)

# Propagate the compiler options to libraries
target_link_libraries(pw_build INTERFACE ${COMMONS_LIBRARY_NAME})
