#include <arba/cppx/type_traits/demangled_type_name.hpp>

#include <gtest/gtest.h>

inline namespace ut
{
namespace tmpl
{
class class_base
{
public:
    virtual ~class_base() = default;
};

template <class T>
class tclass : public class_base
{
public:
    virtual ~tclass() override = default;
};
} // namespace tmpl
} // namespace ut

TEST(demangled_type_name_tests, demangled_type_name__basic_type__ok)
{
#if ARBA_CPPX_IS_DEMANGLED_TYPE_NAME_AVAILABLE
    constexpr std::string_view expected = "int";
    ASSERT_EQ(cppx::demangled_type_name(int()), expected);
    ASSERT_EQ(cppx::demangled_type_name<int>(), expected);
#else
    SUCCEED();
#endif
}

TEST(demangled_type_name_tests, demangled_type_name__template_type__ok)
{
#if ARBA_CPPX_IS_DEMANGLED_TYPE_NAME_AVAILABLE
    constexpr std::string_view expected = "ut::tmpl::tclass<bool>";
    ut::tmpl::tclass<bool> tc;
    ut::tmpl::class_base* cb = &tc;
    ASSERT_EQ(cppx::demangled_type_name(*cb), expected);
    ASSERT_EQ(cppx::demangled_type_name<ut::tmpl::tclass<bool>>(), expected);
#else
    SUCCEED();
#endif
}
