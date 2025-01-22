#include <arba/cppx/preprocessor/auto_var_name.hpp>

#include <gtest/gtest.h>

TEST(concat_tests, concat__var__ok)
{
    const unsigned ARBA_CPPX_AUTO_VAR_NAME = 0;
    static_assert(std::is_same_v<decltype(var_7_), const unsigned>);
    const unsigned CPPX_AUTO_VAR_NAME = 0;
    static_assert(std::is_same_v<decltype(var_9_), const unsigned>);
}
