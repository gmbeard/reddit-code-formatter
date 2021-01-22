#include "reddit_code_formatter.hpp"
#include "./testing.hpp"

#include <iterator>
#include <string>

auto empty_data_test()
{
    rcf::Tokenizer tokenizer { { } };
    Expect(tokenizer.at_end());
}

auto token_output_test()
{
    char constexpr kData[] = "function print(data) {\r\n\t";

    rcf::Tokenizer tokenizer { { &kData[0], std::size(kData) - 1 } };

    Expect(!tokenizer.at_end());

    Expect(tokenizer.consume().type == rcf::TokenType::Other);
    Expect(tokenizer.peek().type == rcf::TokenType::Whitespace);

    Expect(tokenizer.consume().type == rcf::TokenType::Whitespace);
    Expect(tokenizer.peek().type == rcf::TokenType::Other);

    Expect(tokenizer.consume().type == rcf::TokenType::Other);
    Expect(tokenizer.peek().type == rcf::TokenType::Whitespace);

    Expect(tokenizer.consume().type == rcf::TokenType::Whitespace);
    Expect(tokenizer.peek().type == rcf::TokenType::Other);

    Expect(tokenizer.consume().type == rcf::TokenType::Other);
    Expect(tokenizer.peek().type == rcf::TokenType::Newline);

    Expect(tokenizer.consume().type == rcf::TokenType::Newline);
    Expect(tokenizer.peek().type == rcf::TokenType::Tab);

    Expect(tokenizer.consume().type == rcf::TokenType::Tab);

    Expect(tokenizer.at_end());
}

auto to_string(rcf::Span<char const> data)
{
    return std::string { data.data(), data.size() };
}

auto token_content_test()
{
    char constexpr kData[] = "function print(data)\r\n\t";
    rcf::Tokenizer tokenizer { { &kData[0], std::size(kData) -1 } };

    rcf::Token token;

    token = tokenizer.consume();
    Expect(to_string(token.data) == "function");

    token = tokenizer.consume();
    Expect(to_string(token.data) == " ");

    token = tokenizer.consume();
    Expect(to_string(token.data) == "print(data)");

    token = tokenizer.consume();
    Expect(to_string(token.data) == "\r\n");

    token = tokenizer.consume();
    Expect(to_string(token.data) == "\t");
}

auto main() -> int
{
    return run_tests({
        token_output_test,
        empty_data_test,
        token_content_test,
    });
}
