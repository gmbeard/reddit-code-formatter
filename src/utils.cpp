#include "./utils.hpp"
#include <cassert>

auto rcf::NoParameterOptions::operator()(Span<char const>) const noexcept -> bool
{
    return false;
}

auto rcf::trim_option(char const* opt) noexcept -> char const*
{
    assert(opt);
    while (*opt != '\0' && *opt == '-')
        ++opt;
    
    return opt;
}
