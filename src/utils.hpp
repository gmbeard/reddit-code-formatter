#ifndef REDDIT_CODE_FORMATTER_UTILS_HPP_INCLUDED
#define REDDIT_CODE_FORMATTER_UTILS_HPP_INCLUDED

#include "./span.hpp"
#include <algorithm>
#include <cassert>

namespace rcf
{

using CmdLineIterator = char const**;

struct NoParameterOptions
{
    auto operator()(Span<char const>) const noexcept -> bool;
};

auto trim_option(char const*) noexcept -> char const*;

template<typename F = NoParameterOptions>
auto stable_partition_args(
    CmdLineIterator first,
    CmdLineIterator last,
    F option_has_parameter_predicate = F { }) noexcept -> CmdLineIterator
{
    CmdLineIterator pos = first;
    CmdLineIterator partition = first;
    CmdLineIterator displacement = last;

    bool ignore_next_arg = false;

    for (; pos != last; ++pos) {
        assert(*pos);

        if (ignore_next_arg && **pos != '-') {
            ignore_next_arg = false;
            continue;
        }

        if ((**pos) == '-') {
            ignore_next_arg =
                option_has_parameter_predicate(char_span(trim_option(*pos)));
            continue;
        }

        auto start_moved_to = std::rotate(partition, pos, last);
        displacement -= (last - start_moved_to);
        pos = partition++;
    }

    std::rotate(partition, displacement, last);

    return partition;
}

}
#endif //REDDIT_CODE_FORMATTER_UTILS_HPP_INCLUDED
