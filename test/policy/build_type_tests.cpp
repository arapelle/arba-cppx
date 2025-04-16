#include <arba/cppx/policy/build_type.hpp>

#include <gtest/gtest.h>

#include <cstdlib>

TEST(build_type_tests, arba_cppx_bt_build__bt__defined)
{
#ifdef NDEBUG

#ifdef ARBA_CPPX_DEBUG_BUILD
    FAIL();
#else
    #ifdef ARBA_CPPX_RELEASE_BUILD
        SUCCEED();
    #else
        FAIL();
    #endif
#endif

#else

#ifdef ARBA_CPPX_RELEASE_BUILD
    FAIL();
#else
    #ifdef ARBA_CPPX_DEBUG_BUILD
        SUCCEED();
    #else
        FAIL();
    #endif
#endif

#endif
}

TEST(build_type_tests, release_build__name__expected_value)
{
    static_assert(cppx::release_build.name() == "Release");
    ASSERT_EQ(cppx::release_build.name(), "Release");
}

TEST(build_type_tests, debug_build__name__expected_value)
{
    static_assert(cppx::debug_build.name() == "Debug");
    ASSERT_EQ(cppx::debug_build.name(), "Debug");
}

TEST(build_type_tests, build_type__type__expected_type)
{
#ifdef ARBA_CPPX_RELEASE_BUILD
    static_assert(std::is_same_v<std::remove_cvref_t<decltype(cppx::build_type)>, cppx::build_type_t>);
    static_assert(std::is_same_v<std::remove_cvref_t<decltype(cppx::build_type)>, cppx::release_build_t>);
#else
    static_assert(std::is_same_v<std::remove_cvref_t<decltype(cppx::build_type)>, cppx::build_type_t>);
    static_assert(std::is_same_v<std::remove_cvref_t<decltype(cppx::build_type)>, cppx::debug_build_t>);
#endif
}

TEST(build_type_tests, build_type__is_release__expected_bool)
{
#ifdef ARBA_CPPX_RELEASE_BUILD
    static_assert(cppx::build_type.is_release());
    ASSERT_TRUE(cppx::build_type.is_release());
#else
    static_assert(!cppx::build_type.is_release());
    ASSERT_FALSE(cppx::build_type.is_release());
#endif
}

TEST(build_type_tests, build_type__is_debug__expected_bool)
{
#ifdef ARBA_CPPX_RELEASE_BUILD
    static_assert(!cppx::build_type.is_debug());
    ASSERT_FALSE(cppx::build_type.is_debug());
#else
    static_assert(cppx::build_type.is_debug());
    ASSERT_TRUE(cppx::build_type.is_debug());
#endif
}

TEST(build_type_tests, build_type__name__expected_default_value)
{
#ifdef ARBA_CPPX_RELEASE_BUILD
    static_assert(cppx::build_type.name() == "Release");
    ASSERT_EQ(cppx::build_type.name(), "Release");
#else
    static_assert(cppx::build_type.name() == "Debug");
    ASSERT_EQ(cppx::build_type.name(), "Debug");
#endif
}
