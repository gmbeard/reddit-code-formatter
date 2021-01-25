set(LIB_NAME ${PROJECT_NAME}-lib)

add_library(
    ${LIB_NAME}
    OBJECT 
    cmdline.cpp
    tokenizer.cpp
    utils.cpp
)

target_include_directories(
    ${LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${PROJECT_BINARY_DIR}
)

target_compile_features(
    ${LIB_NAME}
    PUBLIC
    cxx_std_17
)

target_compile_options(
    ${LIB_NAME}
    PUBLIC
    -Wall -Werror -Wextra -Wpedantic -Wconversion
)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${LIB_NAME}
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)
