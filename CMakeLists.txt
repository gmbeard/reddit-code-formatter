cmake_minimum_required(VERSION 3.10)

project(
    reddit-code-formatter
    LANGUAGES CXX
    VERSION 0.1
)

option(
    REDDIT_CODE_FORMATTER_ENABLE_TESTS
    "Enable tests for ${PROJECT_NAME}"
    OFF
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
