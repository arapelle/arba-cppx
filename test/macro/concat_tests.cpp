#include <arba/cppx/preprocessor/concat.hpp>

#include <gtest/gtest.h>

TEST(concat_tests, concat__var__ok)
{
    const unsigned ARBA_CPPX_PP_CONCAT(var_, 7) = 0;
    static_assert(std::is_same_v<decltype(var_7), const unsigned>);
    const unsigned CPPX_PP_CONCAT(other_, 7) = 0;
    static_assert(std::is_same_v<decltype(other_7), const unsigned>);
}

#define UTSUFFIX _suffix

TEST(concat_tests, concat__macro__ok)
{
    const unsigned ARBA_CPPX_PP_CONCAT(var, UTSUFFIX) = 0;
    static_assert(std::is_same_v<decltype(var_suffix), const unsigned>);
    const unsigned CPPX_PP_CONCAT(other, UTSUFFIX) = 0;
    static_assert(std::is_same_v<decltype(other_suffix), const unsigned>);
}
