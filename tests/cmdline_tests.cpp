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

auto retrieve_options_test() -> void
{
    char const* kVals[] = {
        "my-prog",
        "-V",
        "--filename",
        "./some-file",
        "-T2",
        "--tabs=2",
        "--output",
        "-W",
        "4",
    };

    auto cmdline = rcf::parse_cmdline(
            { begin(kVals), std::size(kVals) },
            [](auto opt) {
                return
                    std::strcmp(opt, "filename") == 0 
                    || std::strcmp(opt, "W") == 0;
            });

    Expect(!cmdline.get_option(rcf::LongOption("version"), rcf::ShortOption('P')));
    Expect(cmdline.get_option(rcf::ShortOption('V')));
    Expect(cmdline.get_option(rcf::ShortOption('T')));
    Expect(cmdline.get_option(rcf::LongOption("output")));
    Expect(cmdline.get_option(rcf::LongOption("tabs")));
    Expect(cmdline.get_option(rcf::LongOption("filename")));

    Expect(std::string { cmdline.get_option(rcf::LongOption("filename"), true).argument() } == "./some-file");
    Expect(std::string { cmdline.get_option(rcf::ShortOption('T'), true).argument() } == "2");
    Expect(std::string { cmdline.get_option(rcf::LongOption("tabs"), true).argument() } == "2");
    Expect(std::string { cmdline.get_option(rcf::ShortOption('W'), true).argument() } == "4");
}

auto retrieve_single_test() {
    char const* kVals[] = {
        "my-prog",
        "--ver",
    };

    auto cmdline = rcf::parse_cmdline({ begin(kVals), std::size(kVals) });

    Expect(!cmdline.get_option(rcf::LongOption("version"), rcf::ShortOption('V')));
}

auto main() -> int
{
    return run_tests({
        empty_cmdline_test,
        simple_cmdline_test,
        complex_cmdline_test,
        retrieve_options_test,
        retrieve_single_test,
    });
}
