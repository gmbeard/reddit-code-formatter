#ifndef REDDIT_CODE_FORMATTER_TESTS_TESTING_HPP_INCLUDED
#define REDDIT_CODE_FORMATTER_TESTS_TESTING_HPP_INCLUDED

#include <iostream>
#include <initializer_list>
#include <stdexcept>

#define STRINGIFY_IMPL(x) #x
#define STRINGIFY(x) STRINGIFY_IMPL(x)
#define FailureMessage(cond) \
    STRINGIFY(cond) " - " __FILE__ ":" STRINGIFY(__LINE__)

#define Expect(cond)                                        \
do {                                                        \
    if (!(cond))                                            \
        throw std::logic_error { FailureMessage(cond) };    \
}                                                           \
while (0)

template<typename F>
auto run_tests(std::initializer_list<F> tests) -> int
{
    int result_code = 0;
    for (auto t: tests) {
        try {
            t();
        }
        catch (std::exception const& e) {
            std::cerr << "FAILED: " << e.what() << '\n';
            result_code = 1;
            break;
        }
    }

    return result_code;
}

#endif // REDDIT_CODE_FORMATTER_TESTS_TESTING_HPP_INCLUDED
