#include "./reddit_code_formatter.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

auto format(rcf::Span<char const>, std::ostream&) -> void;
auto buffer_from_input(std::istream&) -> std::vector<char>;
auto operator<<(std::ostream&, rcf::Span<char const>) -> std::ostream&;

auto main(int argc, char const** argv) -> int
{
    (void)(argc);
    (void)(argv);

    auto input_data = buffer_from_input(std::cin);
    format({ &input_data[0], input_data.size() }, std::cout);

    return 0;
}

auto buffer_from_input(std::istream& input) -> std::vector<char>
{
    std::size_t constexpr kReadSize = 128;
    char buffer[kReadSize];
    std::vector<char> data;

    while (true) {
        input.read(&buffer[0], std::size(buffer));
        if (input.gcount() == 0)
            break;

        std::copy_n(&buffer[0], input.gcount(), std::back_inserter(data));
    }

    return data;
}

auto operator<<(std::ostream& output, rcf::Span<char const> span) -> std::ostream&
{
    for (auto ch: span)
        output << ch;

    return output;
}

auto operator<<(std::ostream& output, rcf::Token token) -> std::ostream&
{
    return output << token.data;
}

auto format(rcf::Span<char const> data, std::ostream& output) -> void
{
    rcf::Span<char const> constexpr kIndent = { "    ", 4 };
    rcf::Tokenizer tokenizer { data };
    rcf::TokenType last_token_type = rcf::TokenType::Newline;

    while (!tokenizer.at_end()) {
        if (last_token_type == rcf::TokenType::Newline)
            output << kIndent;

        auto token = tokenizer.consume();
        output << token;

        last_token_type = token.type;
    }

    if (last_token_type != rcf::TokenType::Newline)
        output << '\n';
}
