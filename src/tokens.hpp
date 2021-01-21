#ifndef REDDIT_CODE_FORMATTER_TOKENS_HPP_INCLUDED
#define REDDIT_CODE_FORMATTER_TOKENS_HPP_INCLUDED

#include "./span.hpp"

namespace rcf
{

Span<char const> constexpr kEmptyData { };

enum class TokenType
{
    Whitespace,
    Tab,
    Newline,
    Other,
    End,
};

struct Token
{
    TokenType type;
    Span<char const> data;
};

}

#endif //REDDIT_CODE_FORMATTER_SPAN_HPP_INCLUDED
