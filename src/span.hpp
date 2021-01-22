#ifndef REDDIT_CODE_FORMATTER_SPAN_HPP_INCLUDED
#define REDDIT_CODE_FORMATTER_SPAN_HPP_INCLUDED

#include <cstddef>
#include <type_traits>

namespace rcf
{

template<typename T>
struct Span
{
    static_assert(!std::is_reference<T>::value, "T cannot be a reference");

    template<typename U>
    friend struct Span;

    using value_type = T;
    using size_type = std::size_t;
    using pointer = T*;
    using const_pointer = T const*;
    using iterator = T*;
    using const_iterator = T const*;

    Span() noexcept = default;
    Span(Span const& other) noexcept = default;

    template<
        typename U,
        typename std::enable_if_t<
            std::is_convertible<U*, T*>::value>* = nullptr
    >
    constexpr Span(U* data, size_type length) noexcept :
        m_data { data }
    ,   m_length { length }
    { }

    template<
        typename U,
        std::size_t N,
        typename std::enable_if_t<
            std::is_convertible<U*, T*>::value>* = nullptr
    >
    constexpr explicit Span(U (&data)[N]) noexcept :
        m_data { data }
    ,   m_length { N }
    { }

    template<
        typename U,
        typename std::enable_if_t<
            std::is_convertible<U*, T*>::value>* = nullptr
    >
    constexpr Span(Span<U> other) noexcept :
        m_data { other.m_data }
    ,   m_length { other.m_length }
    { }

    constexpr auto size() const noexcept -> size_type
    {
        return m_length;
    }

    constexpr auto data() noexcept -> pointer
    {
        return m_data;
    }

    constexpr auto data() const noexcept -> const_pointer
    {
        return m_data;
    }

    constexpr auto begin() noexcept -> iterator
    {
        return m_data;
    }

    constexpr auto end() noexcept -> iterator
    {
        return (m_data + m_length);
    }

    constexpr auto begin() const noexcept -> const_iterator
    {
        return m_data;
    }

    constexpr auto end() const noexcept -> const_iterator
    {
        return (m_data + m_length);
    }

    constexpr auto subspan_to(const_iterator to) const noexcept -> Span
    {
        return {
            m_data,
            static_cast<size_type>(to - begin())
        };
    }

    constexpr auto subspan_from(const_iterator from) const noexcept -> Span
    {
        return {
            m_data + (from - begin()),
            static_cast<size_type>(end() - from)
        };
    }

private:
    pointer m_data { nullptr };
    size_type m_length { 0 };
};

}

#endif //REDDIT_CODE_FORMATTER_SPAN_HPP_INCLUDED
