#include "./cmdline.hpp"
#include "./utils.hpp"
#include <algorithm>
#include <cstring>

rcf::CmdLine::CmdLine(Span<char const*> args, Span<char const*> opts) noexcept :
    m_arguments { args }
,   m_options { opts }
{ }

auto rcf::CmdLine::arguments() const noexcept -> Span<char const*>
{
    return m_arguments;
}

auto rcf::CmdLine::options() const noexcept -> Span<char const*>
{
    return m_options;
}

auto rcf::CmdLine::get_option(char const* name) const noexcept -> char const*
{
    for (auto opt: options())
        if (std::strcmp(trim_option(name), trim_option(opt)) == 0)
            return opt;

    return nullptr;
}

auto rcf::parse_cmdline(Span<char const*> args) noexcept -> CmdLine
{
    auto options_start = stable_partition_args(args.begin(), args.end());

    return CmdLine {
        args.subspan_to(options_start),
        args.subspan_from(options_start),
    };
}
