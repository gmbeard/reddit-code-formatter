#include "./tokenizer.hpp"
#include <cassert>

rcf::Tokenizer::Tokenizer() noexcept :
    m_position { m_data.begin() }
,   m_current { TokenType::Other, kEmptyData }
{ }

rcf::Tokenizer::Tokenizer(Span<char const> data) noexcept :
    m_data { data }
,   m_position { data.begin() }
,   m_current { TokenType::Other, kEmptyData }
{
    next();
}

auto rcf::Tokenizer::at_end() const noexcept -> bool
{
    return m_current.type == TokenType::End;
}

auto rcf::Tokenizer::peek() const noexcept -> Token const&
{
    assert(!at_end());
    return m_current;
}

auto rcf::Tokenizer::consume() noexcept -> Token
{
    assert(!at_end());
    auto value = m_current;
    next();
    return value;
}

auto rcf::Tokenizer::next() noexcept -> void
{
    if (at_end())
        return;

    if (m_position == m_data.end()) {
        m_current = { TokenType::End, kEmptyData };
        return;
    }

    switch (*m_position) {
        case ' ':
            m_current = { TokenType::Whitespace, { &*m_position++, 1 } };
            break;
        case '\t':
            m_current = { TokenType::Tab, { &*m_position++, 1 } };
            break;
        case '\r':
            {
                auto n = std::next(m_position);
                if (n != m_data.end() && *n == '\n') {
                    m_current = { TokenType::Newline, { &*m_position, 2 } };
                    m_position = ++n;
                }
                else {
                    m_current = { TokenType::Other, { &*m_position++, 1 } };
                }
                break;
            }
        case '\n':
            m_current = { TokenType::Newline, { &*m_position++, 1 } };
            break;
        default:
            {
                auto p = std::next(m_position);
                for (; p != m_data.end(); ++p) {
                    if (*p == '\r' || *p == '\n' || *p == ' ' || *p == '\t')
                        break;
                }

                m_current = {
                    TokenType::Other,
                    {
                        &*m_position,
                        static_cast<std::size_t>(p - m_position)
                    }
                };

                m_position = p;
            }
            break;
    }
}
