#include <arba/cppx/type_traits/type_name.hpp>

#include <gtest/gtest.h>

inline namespace ut
{
namespace tmpl
{
template <class T>
class tclass
{
};
} // namespace tmpl
} // namespace ut

TEST(type_name_tests, type_name__basic_type__ok)
{
#if ARBA_CPPX_IS_TYPE_NAME_AVAILABLE
    if constexpr (cppx::is_type_name_available())
    {
        constexpr std::string_view expected = "int";
        ASSERT_EQ(cppx::type_name<int>(), expected);
        static_assert(cppx::type_name<int>() == expected);
    }
#else
    SUCCEED();
#endif
}

TEST(type_name_tests, type_name__std_string__ok)
{
    if constexpr (cppx::is_type_name_available())
    {
        constexpr std::string_view expected = "std::string";
        ASSERT_EQ(cppx::type_name<std::string>(), expected);
        static_assert(cppx::type_name<std::string>() == expected);
    }
}

TEST(type_name_tests, type_name__std_string_view__ok)
{
    if constexpr (cppx::is_type_name_available())
    {
        constexpr std::string_view expected = "std::string_view";
        ASSERT_EQ(cppx::type_name<std::string_view>(), expected);
        static_assert(cppx::type_name<std::string_view>() == expected);
    }
}

TEST(type_name_tests, type_name__template_type__ok)
{
    if constexpr (cppx::is_type_name_available())
    {
        constexpr std::string_view expected = "ut::tmpl::tclass<bool>";
        ASSERT_EQ(cppx::type_name<tmpl::tclass<bool>>(), expected);
        static_assert(cppx::type_name<tmpl::tclass<bool>>() == expected);
    }
}
