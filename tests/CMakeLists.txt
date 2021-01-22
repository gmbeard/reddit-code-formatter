set(LIB_NAME ${PROJECT_NAME}-lib)

add_executable(tokenizer_tests tokenizer_tests.cpp)
target_link_libraries(tokenizer_tests PRIVATE ${LIB_NAME})
add_test(NAME tokenizer_tests COMMAND tokenizer_tests)

add_executable(cmdline_tests cmdline_tests.cpp)
target_link_libraries(cmdline_tests PRIVATE ${LIB_NAME})
add_test(NAME cmdline_tests COMMAND cmdline_tests)
