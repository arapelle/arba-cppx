#include <arba/cppx/string/string_constant.hpp>

#include <gtest/gtest.h>

#include <cstdlib>

TEST(basic_string_constant_tests, basic_string_constant__empty_string__ok)
{
    cppx::basic_string_constant fstr("");
    ASSERT_EQ(fstr.size(), 0);
    std::string_view sv(fstr);
    ASSERT_EQ(sv, "");
    ASSERT_EQ(fstr.c_str[0], '\0');
    cppx::basic_string_constant fstr2("");
    ASSERT_EQ(fstr, fstr2);
}

TEST(basic_string_constant_tests, basic_string_constant__not_empty_string__ok)
{
    cppx::basic_string_constant fstr("abcd");
    ASSERT_EQ(fstr.size(), 4);
    std::string_view sv(fstr);
    ASSERT_EQ(sv, "abcd");
    ASSERT_EQ(fstr.c_str[0], 'a');
    ASSERT_EQ(fstr.c_str[1], 'b');
    ASSERT_EQ(fstr.c_str[2], 'c');
    ASSERT_EQ(fstr.c_str[3], 'd');
    ASSERT_EQ(fstr.c_str[4], '\0');
    cppx::basic_string_constant fstr2("abcd");
    ASSERT_EQ(fstr, fstr2);
}

template <cppx::basic_string_constant arg>
class global_title
{
public:
    static constexpr typename decltype(arg)::string_view value = arg;
};

TEST(basic_string_constant_tests, basic_string_constant__as_template_parameter__ok)
{
    ASSERT_EQ(global_title<"libarba">::value, "libarba");
    ASSERT_EQ(global_title<U"libarba">::value, U"libarba");
}
