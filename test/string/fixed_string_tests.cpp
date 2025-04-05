#include <arba/cppx/string/fixed_string.hpp>

#include <gtest/gtest.h>

#include <cstdlib>

TEST(basic_fixed_string_tests, basic_fixed_string__empty_string__ok)
{
    cppx::basic_fixed_string fstr("");
    ASSERT_EQ(fstr.size(), 0);
    std::string_view sv(fstr);
    ASSERT_EQ(sv, "");
    ASSERT_EQ(fstr.c_str[0], '\0');
    cppx::basic_fixed_string fstr2("");
    ASSERT_EQ(fstr, fstr2);
}

TEST(basic_fixed_string_tests, basic_fixed_string__not_empty_string__ok)
{
    cppx::basic_fixed_string fstr("abcd");
    ASSERT_EQ(fstr.size(), 4);
    std::string_view sv(fstr);
    ASSERT_EQ(sv, "abcd");
    ASSERT_EQ(fstr.c_str[0], 'a');
    ASSERT_EQ(fstr.c_str[1], 'b');
    ASSERT_EQ(fstr.c_str[2], 'c');
    ASSERT_EQ(fstr.c_str[3], 'd');
    ASSERT_EQ(fstr.c_str[4], '\0');
    cppx::basic_fixed_string fstr2("abcd");
    ASSERT_EQ(fstr, fstr2);
}

template <cppx::basic_fixed_string arg>
class global_title
{
public:
    static constexpr typename decltype(arg)::string_view value = arg;
};

TEST(basic_fixed_string_tests, basic_fixed_string__as_template_parameter__ok)
{
    ASSERT_EQ(global_title<"libarba">::value, "libarba");
    ASSERT_EQ(global_title<U"libarba">::value, U"libarba");
}
