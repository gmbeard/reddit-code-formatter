#include "reddit_code_formatter.hpp"
#include "./testing.hpp"
#include <iterator>
#include <iostream>
#include <string>
#include <cstring>

using std::begin;
using std::end;

auto empty_cmdline_test() -> void
{
    char const* kVals[] = { "" };

    auto partition = rcf::stable_partition_args(begin(kVals), begin(kVals));

    Expect(partition - begin(kVals) == 0);
}

auto simple_cmdline_test() -> void
{
    char const* kVals[] = {
        "--version",
        "one",
    };

    auto partition = rcf::stable_partition_args(begin(kVals), end(kVals));

    Expect(partition - begin(kVals) == 1);
    Expect(end(kVals) - partition == 1);
    Expect(std::string { *begin(kVals) } == "one");
    Expect(std::string { *partition } == "--version");
}

auto complex_cmdline_test() -> void
{
    char const* kVals[] = {
        "-v",
        "one",
        "two",
        "--filename",
        "./some-file",
        "--tabs",
        "three",
        "--output",
        "four",
        "",
        "--",
    };

    auto partition = rcf::stable_partition_args(
        begin(kVals),
        end(kVals),
        [](char const* opt) noexcept {
            return std::strcmp(opt, "filename") == 0;
        });

    auto args = begin(kVals);
    Expect(partition - args == 5);
    Expect(std::string { *args++ } == "one");
    Expect(std::string { *args++ } == "two");
    Expect(std::string { *args++ } == "three");
    Expect(std::string { *args++ } == "four");

    auto options = partition;
    Expect(end(kVals) - partition == 6);
    Expect(std::string { *options++ } == "-v");
    Expect(std::string { *options++ } == "--filename");
    Expect(std::string { *options++ } == "./some-file");
    Expect(std::string { *options++ } == "--tabs");
    Expect(std::string { *options++ } == "--output");
    Expect(std::string { *options++ } == "--");
}

auto main() -> int
{
    return run_tests({
        empty_cmdline_test,
        simple_cmdline_test,
        complex_cmdline_test,
    });
}
