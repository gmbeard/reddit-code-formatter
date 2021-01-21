#ifndef REDDIT_CODE_FORMATTER_TOKENIZER_HPP_INCLUDED
#define REDDIT_CODE_FORMATTER_TOKENIZER_HPP_INCLUDED

#include "./tokens.hpp"
#include "./span.hpp"

#include <cassert>
#include <iterator>

namespace rcf
{

/**
 * Represents a forward-only stream of tokens extracted from a caller-provided
 * buffer. Instances of `Tokenizer` neither own, nor allocate any data for the
 * tokens they produce. All data for the tokens is represented using "slices"
 * of the original caller-provided buffer. This means that the buffer provided
 * must live at least as long as any instances that use it.
 */
struct Tokenizer
{
    Tokenizer() noexcept;

    Tokenizer(Span<char const> data) noexcept;

    /**
     * Indicates whether the token stream is at the end
     */
    auto at_end() const noexcept -> bool;

    /**
     * Returns the next token without advancing the token stream. It is
     * undefined behaviour to call if `at_end() == true`.
     */
    auto peek() const noexcept -> Token const&;

    /**
     * Returns the next token and advances the token stream. It is undefined
     * behaviour to call if `at_end() == true`.
     */
    [[nodiscard]] auto consume() noexcept -> Token;

private:
    auto next() noexcept -> void;

    Span<char const> m_data;
    Span<char const>::const_iterator m_position;
    Token m_current;
};

}

#endif //REDDIT_CODE_FORMATTER_SPAN_HPP_INCLUDED
