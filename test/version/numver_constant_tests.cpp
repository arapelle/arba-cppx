#include <arba/cppx/version/numver_constant.hpp>

#include <gtest/gtest.h>

TEST(numver_constant_tests, constructo__no_arg__succeed)
{
    using version_t = cppx::numver_constant<1, 2, 3>;
    EXPECT_NO_THROW(
        version_t version;
        EXPECT_EQ(version.major(), 1);
        EXPECT_EQ(version.minor(), 2);
        EXPECT_EQ(version.patch(), 3);
        );
}

TEST(numver_constant_tests, operator_eq__other__succeed)
{
    EXPECT_EQ((cppx::numver_constant<1, 2, 3>()), (cppx::numver_constant<1, 2, 3>()));
}

TEST(numver_constant_tests, operator_ne__other__succeed)
{
    EXPECT_NE((cppx::numver_constant<1, 2, 3>()), (cppx::numver_constant<0, 2, 3>()));
    EXPECT_NE((cppx::numver_constant<1, 2, 3>()), (cppx::numver_constant<1, 0, 3>()));
    EXPECT_NE((cppx::numver_constant<1, 2, 3>()), (cppx::numver_constant<1, 2, 0>()));
}

TEST(numver_constant_tests, operator_lt__other__succeed)
{
    EXPECT_LT((cppx::numver_constant<1, 2, 3>()), (cppx::numver_constant<1, 2, 4>()));
    EXPECT_LT((cppx::numver_constant<1, 2, 3>()), (cppx::numver_constant<1, 3, 0>()));
    EXPECT_LT((cppx::numver_constant<1, 2, 3>()), (cppx::numver_constant<2, 0, 0>()));
}

TEST(numver_constant_tests, operator_gt__other__succeed)
{
    EXPECT_GT((cppx::numver_constant<1, 2, 4>()), (cppx::numver_constant<1, 2, 3>()));
    EXPECT_GT((cppx::numver_constant<1, 3, 0>()), (cppx::numver_constant<1, 2, 3>()));
    EXPECT_GT((cppx::numver_constant<2, 0, 0>()), (cppx::numver_constant<1, 2, 3>()));
}

TEST(numver_constant_tests, operator_le__other__succeed)
{
    EXPECT_LE((cppx::numver_constant<1, 2, 3>()), (cppx::numver_constant<1, 2, 3>()));
    EXPECT_LE((cppx::numver_constant<1, 2, 3>()), (cppx::numver_constant<1, 2, 4>()));
    EXPECT_LE((cppx::numver_constant<1, 2, 3>()), (cppx::numver_constant<1, 3, 0>()));
    EXPECT_LE((cppx::numver_constant<1, 2, 3>()), (cppx::numver_constant<2, 0, 0>()));
}

TEST(numver_constant_tests, operator_ge__other__succeed)
{
    EXPECT_GE((cppx::numver_constant<1, 2, 3>()), (cppx::numver_constant<1, 2, 3>()));
    EXPECT_GE((cppx::numver_constant<1, 2, 4>()), (cppx::numver_constant<1, 2, 3>()));
    EXPECT_GE((cppx::numver_constant<1, 3, 0>()), (cppx::numver_constant<1, 2, 3>()));
    EXPECT_GE((cppx::numver_constant<2, 0, 0>()), (cppx::numver_constant<1, 2, 3>()));
}

TEST(numver_constant_tests, constexpr__valid_args__no_compile_error)
{
    constexpr cppx::numver_constant<0, 1, 5> sv;
    static_assert(sv.major() == 0);
    static_assert(sv.minor() == 1);
    static_assert(sv.patch() == 5);

    constexpr cppx::numver_constant<15, 13, 234> sv2;
    static_assert(sv2.major() == 15);
    static_assert(sv2.minor() == 13);
    static_assert(sv2.patch() == 234);

    static_assert(sv != sv2);
    static_assert(sv < sv2);
}
