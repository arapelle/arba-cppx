#pragma once

#include <string_view>

inline namespace arba
{
namespace cppx
{

// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0732r2.pdf

template <typename CharT, size_t N>
struct basic_string_constant
{
    using string_view = std::basic_string_view<CharT>;

    constexpr basic_string_constant(const CharT (&str)[N + 1])
    {
        for (std::size_t i = 0; i < (N + 1); ++i)
            c_str[i] = str[i];
    }

    constexpr static std::size_t size() noexcept { return N; }

    constexpr operator string_view() const { return string_view(c_str, N); }

    constexpr auto operator<=>(const basic_string_constant&) const = default;

    CharT c_str[N + 1];
};

template <typename CharT, std::size_t N>
basic_string_constant(const CharT (&str)[N]) -> basic_string_constant<CharT, N - 1>;

template <std::size_t N>
using string_constant = basic_string_constant<char, N>;

} // namespace cppx
} // namespace arba
