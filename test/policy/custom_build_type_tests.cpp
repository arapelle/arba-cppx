#include <arba/cppx/policy/build_type.hpp>

#include <gtest/gtest.h>

#include <cstdlib>

TEST(build_type_tests, release_build__name__expected_value)
{
#ifdef ARBA_CPPX_RELEASE_BUILD
    static_assert(cppx::release_build.name() == "CustomRelease");
    ASSERT_EQ(cppx::release_build.name(), "CustomRelease");
#else
    static_assert(cppx::release_build.name() == "Release");
    ASSERT_EQ(cppx::release_build.name(), "Release");
#endif
}

TEST(custom_build_type_tests, debug_build__name__expected_value)
{
#ifdef ARBA_CPPX_RELEASE_BUILD
    static_assert(cppx::debug_build.name() == "Debug");
    ASSERT_EQ(cppx::debug_build.name(), "Debug");
#else
    static_assert(cppx::debug_build.name() == "CustomDebug");
    ASSERT_EQ(cppx::debug_build.name(), "CustomDebug");
#endif
}

TEST(custom_build_type_tests, build_type__custom_name__expected_default_value)
{
#ifdef ARBA_CPPX_RELEASE_BUILD
    static_assert(cppx::build_type.name() == "CustomRelease");
    ASSERT_EQ(cppx::build_type.name(), "CustomRelease");
#else
    static_assert(cppx::build_type.name() == "CustomDebug");
    ASSERT_EQ(cppx::build_type.name(), "CustomDebug");
#endif
}
