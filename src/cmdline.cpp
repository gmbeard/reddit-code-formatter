#include "./cmdline.hpp"
#include "./utils.hpp"
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iterator>

rcf::LongOption::LongOption(char const* value) noexcept :
    m_value { value }
{
    assert(m_value);
}

rcf::LongOption::operator char const*() const noexcept
{
    return m_value;
}

rcf::ShortOption::ShortOption(char value) noexcept :
    m_value { value }
{
    assert(m_value);
}

rcf::ShortOption::operator char() const noexcept
{
    return m_value;
}

rcf::Option::Option() noexcept :
    m_present { false }
,   m_arg { nullptr }
{ }

rcf::Option::Option(OptionPresent, char const* arg) noexcept :
    m_present { true }
,   m_arg { arg }
{ }

rcf::Option::operator bool() const noexcept
{
    return m_present;
}

auto rcf::Option::argument() const noexcept -> char const*
{
    return m_arg;
}

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

auto get_long_option(
        rcf::Span<char const*> opt,
        rcf::LongOption long_option,
        bool with_param) noexcept -> rcf::Option
{
    using rcf::char_span;
    using rcf::Option;
    using rcf::option_present;
    using rcf::trim_option;

    assert(opt.size() >= 1);
    auto opt_value = char_span(trim_option(opt[0]));
    auto const long_opt_value = char_span(trim_option(long_option));

    if (!long_opt_value.content_equal(
            opt_value.subspan(opt_value.begin(), opt_value.find('='))))
        return { };

    if (!with_param)
        return Option { option_present };

    if (auto equal_ch = opt_value.find('='); equal_ch != opt_value.end()) {
        return rcf::Option {
            option_present,
            opt_value.subspan_from(++equal_ch).data()
        };
    }

    if (opt.size() == 1 || *opt[1] == '-')
        return Option { option_present };

    return Option { option_present, opt[1] };
}

auto get_short_option(
        rcf::Span<char const*> opt,
        rcf::ShortOption short_option,
        bool with_param) noexcept -> rcf::Option
{
    using rcf::char_span;
    using rcf::Option;
    using rcf::option_present;
    using rcf::trim_option;
    using std::next;

    assert(opt.size() >= 1);
    auto opt_value = char_span(trim_option(opt[0]));

    if (!opt_value.size() || opt_value[0] != short_option)
        return { };

    if (!with_param)
        return Option { option_present };

    opt_value = opt_value.subspan_from(next(opt_value.begin()));
    if (opt_value.size())
        return Option { option_present, opt_value.data() };

    if (opt.size() == 1 || *opt[1] == '-')
        return Option { option_present };

    return Option { option_present, opt[1] };
}

auto rcf::CmdLine::get_option(
        ShortOption short_opt,
        bool with_param) const noexcept -> Option
{
    auto opts = options();
    for (auto it = opts.begin(); it != opts.end(); ++it) {
        if (auto result = get_short_option(opts.subspan_from(it), short_opt, with_param); result)
            return result;
    }

    return { };
}

auto rcf::CmdLine::get_option(
        LongOption long_opt,
        bool with_param) const noexcept -> Option
{
    auto opts = options();
    for (auto it = opts.begin(); it != opts.end(); ++it) {
        if (auto result = get_long_option(opts.subspan_from(it), long_opt, with_param); result)
            return result;
    }

    return { };
}

auto rcf::CmdLine::get_option(
    LongOption long_opt,
    ShortOption short_opt,
    bool with_param) const noexcept -> Option
{
    auto opts = options();
    for (auto it = opts.begin(); it != opts.end(); ++it) {
        if (auto result = get_long_option(opts.subspan_from(it), long_opt, with_param); result)
            return result;

        if (auto result = get_short_option(opts.subspan_from(it), short_opt, with_param); result)
            return result;
    }

    return { };
}

auto rcf::long_option(char const* val) noexcept -> LongOption
{
    return LongOption { val };
}

auto rcf::short_option(char val) noexcept -> ShortOption 
{
    return ShortOption { val };
}

