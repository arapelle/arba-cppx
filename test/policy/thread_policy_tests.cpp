#include <arba/cppx/policy/thread_policy.hpp>

#include <gtest/gtest.h>

int func(cppx::ThreadPolicy auto)
{
    return 0;
}

int func(cppx::thread_safe_t)
{
    return 642;
}

TEST(thread_policy_tests, test_thread_policy)
{
    ASSERT_EQ(func(cppx::thread_safe), 642);
    ASSERT_EQ(func(cppx::thread_unsafe), 0);
}
