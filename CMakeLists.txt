cmake_minimum_required(VERSION 3.10)

project(
    reddit-code-formatter
    LANGUAGES CXX
    VERSION 0.1.0
)

option(
    REDDIT_CODE_FORMATTER_ENABLE_TESTS
    "Enable tests for ${PROJECT_NAME}"
    OFF
)

set(COMMIT_HASH "\"\"")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG_VERSION "-debug")
endif()

find_program(GIT_PROG git)

if(NOT GIT_PROG STREQUAL "GIT_PROG-NOTFOUND")
    message(STATUS "Found git: ${GIT_PROG}")
    execute_process(
        COMMAND ${GIT_PROG} log HEAD --pretty="%H"
        OUTPUT_VARIABLE COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

configure_file(
    src/config.hpp.in
    config.hpp
    @ONLY
)

add_subdirectory(src)

if (REDDIT_CODE_FORMATTER_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
