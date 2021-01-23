#ifndef REDDIT_CODE_FORMATTER_CMDLINE_HPP_INCLUDED
#define REDDIT_CODE_FORMATTER_CMDLINE_HPP_INCLUDED

#include "./span.hpp"
#include "./utils.hpp"

namespace rcf
{

struct LongOption
{
    explicit LongOption(char const*) noexcept;
    operator char const*() const noexcept;

private:
    char const* m_value;
};

struct ShortOption
{
    explicit ShortOption(char) noexcept;
    operator char() const noexcept;
private:
    char m_value;
};

struct OptionPresent { } const option_present;

struct Option
{
    Option() noexcept;
    explicit Option(OptionPresent, char const* arg = nullptr) noexcept;
    operator bool() const noexcept;
    auto argument() const noexcept -> char const*;
private:
    bool m_present;
    char const* m_arg;
};

auto long_option(char const*) noexcept -> LongOption;
auto short_option(char) noexcept -> ShortOption;

struct CmdLine
{
    CmdLine(Span<char const*> args, Span<char const*> opts) noexcept;
    auto arguments() const noexcept -> Span<char const*>;
    auto options() const noexcept -> Span<char const*>;
    auto get_option(LongOption, ShortOption, bool = false) const noexcept -> Option;
    auto get_option(LongOption, bool = false) const noexcept -> Option;
    auto get_option(ShortOption, bool = false) const noexcept -> Option;
private:
    Span<char const*> m_arguments;
    Span<char const*> m_options;
};

template<typename F = NoParameterOptions>
auto parse_cmdline(
        Span<char const*> args,
        F option_has_parameter_predicate = F { }) noexcept -> CmdLine
{
    auto options_start =
        stable_partition_args(
            args.begin(),
            args.end(),
            std::move(option_has_parameter_predicate));

    return CmdLine {
        args.subspan_to(options_start),
        args.subspan_from(options_start),
    };
}

}

#endif //REDDIT_CODE_FORMATTER_CMDLINE_HPP_INCLUDED
