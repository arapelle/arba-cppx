#pragma once

#include "../preprocessor/exception.hpp"

#include <cstdint>
#include <stdexcept>
#include <string_view>

inline namespace arba
{
namespace cppx
{

static constexpr int64_t stoi64(std::string_view str)
{
    constexpr std::string_view spaces = " \f\n\r\t\v";
    std::size_t pos = str.find_first_not_of(spaces);
    if (pos == std::string_view::npos)
    {
        constexpr std::string_view error_msg = "Input string is empty or full of space characters.";
        ARBA_CPPX_THROW(std::invalid_argument(error_msg.data()), error_msg);
    }
    str.remove_prefix(pos);
    str.remove_suffix(str.size() - str.find_last_not_of(spaces) - 1);

    int64_t sign = 1;
    char ch = str[0];
    if (ch == '-')
    {
        sign = -1;
        str.remove_prefix(1);
    }
    else if (ch == '+')
    {
        str.remove_prefix(1);
    }

    int64_t result = 0;
    int64_t multiplier = 1;
    for (std::ptrdiff_t i = str.size() - 1; i >= 0; --i)
    {
        ch = str[i];
        if (ch < '0' || ch > '9') [[unlikely]]
        {
            constexpr std::string_view error_msg = "Invalid character found in input string.";
            ARBA_CPPX_THROW(std::invalid_argument(error_msg.data()), error_msg);
        }
        int64_t number = ch - '0';
        result += number * multiplier;
        multiplier *= 10;
        // TODO?
        // https://stackoverflow.com/questions/1815367/catch-and-compute-overflow-during-multiplication-of-two-large-integers
    }

    return sign * result;
}

} // namespace cppx
} // namespace arba
