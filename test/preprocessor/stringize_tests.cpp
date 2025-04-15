#include <arba/cppx/preprocessor/stringize.hpp>

#include <gtest/gtest.h>

#include <format>

TEST(stringize_tests, stringize__var__ok)
{
    int value = 5;

    auto name = ARBA_CPPX_PP_STRINGIZE_CODE(value);
    static_assert(std::is_same_v<decltype(name), const char*>);
    std::string str = std::format("{}: {}", name, value);
    ASSERT_EQ(str, "value: 5");

    auto xname = ARBA_CPPX_PP_STRINGIZE(value);
    static_assert(std::is_same_v<decltype(xname), const char*>);
    str = std::format("{}: {}", xname, value);
    ASSERT_EQ(str, "value: 5");
}

#define UTVALUE std::size_t(6)

TEST(stringize_tests, stringize__macro__ok)
{
    auto str = ARBA_CPPX_PP_STRINGIZE(UTVALUE);
    auto xstr = ARBA_CPPX_PP_STRINGIZE_CODE(UTVALUE);
    auto value = UTVALUE;
    static_assert(std::is_same_v<decltype(str), const char*>);
    static_assert(std::is_same_v<decltype(xstr), const char*>);
    static_assert(std::is_same_v<decltype(value), std::size_t>);
    std::string fstr = std::format("{}: {}", ARBA_CPPX_PP_STRINGIZE_CODE(UTVALUE), ARBA_CPPX_PP_STRINGIZE(UTVALUE));
    ASSERT_EQ(fstr, "UTVALUE: std::size_t(6)");
}
