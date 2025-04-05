#include <arba/cppx/preprocessor/format_var.hpp>

#include <gtest/gtest.h>

#include <format>

TEST(format_var_tests, format_var__default_var_format_string__var__ok)
{
    const int value = 5;
    std::string fstr = ARBA_CPPX_PP_FORMAT_VAR(value);
    ASSERT_EQ(fstr, "value = 5");
    fstr = CPPX_PP_FORMAT_VAR(value);
    ASSERT_EQ(fstr, "value = 5");
}

#define UTVALUE std::size_t(6)

TEST(format_var_tests, format_var__default_var_format_string__macro__ok)
{
    std::string fstr = ARBA_CPPX_PP_FORMAT_VAR(UTVALUE);
    ASSERT_EQ(fstr, "UTVALUE = 6");
    fstr = CPPX_PP_FORMAT_VAR(UTVALUE);
    ASSERT_EQ(fstr, "UTVALUE = 6");
}

#undef ARBA_CPPX_PP_VAR_FORMAT_STRING
#define ARBA_CPPX_PP_VAR_FORMAT_STRING "{}: {}"

TEST(format_var_tests, format_var__custom_var_format_string__var__ok)
{
    const int value = 5;
    std::string fstr = ARBA_CPPX_PP_FORMAT_VAR(value);
    ASSERT_EQ(fstr, "value: 5");
    fstr = CPPX_PP_FORMAT_VAR(value);
    ASSERT_EQ(fstr, "value: 5");
}

#define UTVALUE std::size_t(6)

TEST(format_var_tests, format_var__custom_var_format_string__macro__ok)
{
    std::string fstr = ARBA_CPPX_PP_FORMAT_VAR(UTVALUE);
    ASSERT_EQ(fstr, "UTVALUE: 6");
    fstr = CPPX_PP_FORMAT_VAR(UTVALUE);
    ASSERT_EQ(fstr, "UTVALUE: 6");
}
