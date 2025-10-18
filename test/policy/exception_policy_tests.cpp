#include <arba/cppx/policy/exception_policy.hpp>

#include <gtest/gtest.h>

int func(cppx::ExceptionPolicy auto)
{
    return 0;
}

int func(cppx::maythrow_t)
{
    return 642;
}

TEST(exception_policy_tests, test_exception_policy)
{
    ASSERT_EQ(func(cppx::maythrow), 642);
    ASSERT_EQ(func(std::nothrow), 0);
#ifdef NDEBUG
    ASSERT_EQ(func(cppx::smartthrow), 0);
#else
    ASSERT_EQ(func(cppx::smartthrow), 642);
#endif
}
