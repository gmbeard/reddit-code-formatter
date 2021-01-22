#ifndef REDDIT_CODE_FORMATTER_CMDLINE_HPP_INCLUDED
#define REDDIT_CODE_FORMATTER_CMDLINE_HPP_INCLUDED

#include "./span.hpp"

namespace rcf
{

struct CmdLine
{
    CmdLine(Span<char const*> args, Span<char const*> opts) noexcept;
    auto arguments() const noexcept -> Span<char const*>;
    auto options() const noexcept -> Span<char const*>;
    auto get_option(char const*) const noexcept -> char const*;
private:
    Span<char const*> m_arguments;
    Span<char const*> m_options;
};

auto parse_cmdline(Span<char const*> args) noexcept -> CmdLine;

}

#endif //REDDIT_CODE_FORMATTER_CMDLINE_HPP_INCLUDED
