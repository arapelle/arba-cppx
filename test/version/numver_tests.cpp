#include <arba/cppx/version/numver.hpp>

#include <gtest/gtest.h>

static_assert(sizeof(cppx::numver) == sizeof(uint64_t) * 2);

TEST(numver_tests, constructor__numbers__succeed)
{
    EXPECT_NO_THROW(
        cppx::numver sv("0.11.223");
        ASSERT_EQ(sv.major(), 0);
        ASSERT_EQ(sv.minor(), 11);
        ASSERT_EQ(sv.patch(), 223);
        );
}

TEST(numver_tests, copy_constructor__numver__succeed)
{
    EXPECT_NO_THROW(
        cppx::numver version(0, 11, 223);
        cppx::numver sv(version);
        ASSERT_EQ(sv.major(), 0);
        ASSERT_EQ(sv.minor(), 11);
        ASSERT_EQ(sv.patch(), 223);
        );
}

TEST(numver_tests, constructor__version_like__succeed)
{
    class custom_version
    {
    public:
        custom_version() : major_(6), minor_(4), patch_(2) {}
        unsigned major() const { return major_; }
        unsigned minor() const { return minor_; }
        unsigned patch() const { return patch_; }

    private:
        unsigned major_, minor_, patch_;
    };

    EXPECT_NO_THROW(
        custom_version version;
        cppx::numver sv(version);
        ASSERT_EQ(sv.major(), 6);
        ASSERT_EQ(sv.minor(), 4);
        ASSERT_EQ(sv.patch(), 2);
        );
}

TEST(numver_tests, constructor__valid_string__succeed)
{
    EXPECT_NO_THROW(
        cppx::numver sv("0.11.223");
        ASSERT_EQ(sv.major(), 0);
        ASSERT_EQ(sv.minor(), 11);
        ASSERT_EQ(sv.patch(), 223);
        );
}

TEST(numver_tests, constructor__invalid_string__expect_invalid_argument)
{
    EXPECT_THROW(cppx::numver sv("0.1.2x");, std::invalid_argument);
}

TEST(numver_tests, constructor__string_quadnum__expect_invalid_argument)
{
    EXPECT_THROW(cppx::numver version("1.2.3.4");, std::invalid_argument);
}

TEST(numver_tests, constructor__string_00__expect_invalid_argument)
{
    EXPECT_THROW(cppx::numver version("00.2.3");, std::invalid_argument);
}

TEST(numver_tests, constructor__string_binum__expect_invalid_argument)
{
    EXPECT_THROW(cppx::numver version("0.1");, std::invalid_argument);
}

TEST(numver_tests, set_major__nominal_case__no_exception)
{
    cppx::numver version(1, 2, 3);
    version.set_major(999);
    ASSERT_EQ(version.major(), 999);
    ASSERT_EQ(version.minor(), 2);
    ASSERT_EQ(version.patch(), 3);
}

TEST(numver_tests, set_minor__nominal_case__no_exception)
{
    cppx::numver version(1, 2, 3);
    version.set_minor(999);
    ASSERT_EQ(version.major(), 1);
    ASSERT_EQ(version.minor(), 999);
    ASSERT_EQ(version.patch(), 3);
}

TEST(numver_tests, set_patch__nominal_case__no_exception)
{
    cppx::numver version(1, 2, 3);
    version.set_patch(999);
    ASSERT_EQ(version.major(), 1);
    ASSERT_EQ(version.minor(), 2);
    ASSERT_EQ(version.patch(), 999);
}

TEST(numver_tests, up_major__nominal_case__no_exception)
{
    cppx::numver version(1, 2, 3);
    version.up_major();
    ASSERT_EQ(version, cppx::numver(2, 0, 0));
}

TEST(numver_tests, up_minor__nominal_case__no_exception)
{
    cppx::numver version(1, 2, 3);
    version.up_minor();
    ASSERT_EQ(version, cppx::numver(1, 3, 0));
}

TEST(numver_tests, up_patch__nominal_case__no_exception)
{
    cppx::numver version(1, 2, 3);
    version.up_patch();
    ASSERT_EQ(version, cppx::numver(1, 2, 4));
}

TEST(numver_tests, is_major_compatible_with__compatible_version__expect_true)
{
    EXPECT_TRUE(cppx::numver("1.4.1").is_major_compatible_with(cppx::numver("1.4.1")));
    EXPECT_TRUE(cppx::numver("1.4.2").is_major_compatible_with(cppx::numver("1.4.1")));
    EXPECT_TRUE(cppx::numver("1.5.0").is_major_compatible_with(cppx::numver("1.4.1")));
    EXPECT_TRUE(cppx::numver("1.5.6").is_major_compatible_with(cppx::numver("1.4.1")));
}

TEST(numver_tests, is_major_compatible_with__incompatible_version__expect_false)
{
    EXPECT_FALSE(cppx::numver("0.4.1").is_major_compatible_with(cppx::numver("1.4.1")));
    EXPECT_FALSE(cppx::numver("1.4.0").is_major_compatible_with(cppx::numver("1.4.1")));
    EXPECT_FALSE(cppx::numver("1.3.1").is_major_compatible_with(cppx::numver("1.4.1")));
    EXPECT_FALSE(cppx::numver("2.4.1").is_major_compatible_with(cppx::numver("1.4.1")));
}

TEST(numver_tests, is_minor_compatible_with__compatible_version__expect_true)
{
    EXPECT_TRUE(cppx::numver("1.4.1").is_minor_compatible_with(cppx::numver("1.4.1")));
    EXPECT_TRUE(cppx::numver("1.4.2").is_minor_compatible_with(cppx::numver("1.4.1")));
}

TEST(numver_tests, is_minor_compatible_with__incompatible_version__expect_false)
{
    EXPECT_FALSE(cppx::numver("0.4.1").is_minor_compatible_with(cppx::numver("1.4.1")));
    EXPECT_FALSE(cppx::numver("1.3.1").is_minor_compatible_with(cppx::numver("1.4.1")));
    EXPECT_FALSE(cppx::numver("1.4.0").is_minor_compatible_with(cppx::numver("1.4.1")));
    EXPECT_FALSE(cppx::numver("1.5.1").is_minor_compatible_with(cppx::numver("1.4.1")));
    EXPECT_FALSE(cppx::numver("2.4.1").is_minor_compatible_with(cppx::numver("1.4.1")));
}

struct quadnum_version
{
public:
    uint64_t major() const noexcept { return 2; }
    uint64_t minor() const noexcept { return 10; }
    uint64_t patch() const noexcept { return 15; }
    uint64_t tweak() const noexcept { return 230; }
};

TEST(numver_tests, is_patch_compatible_with__compatible_version__expect_true)
{
    EXPECT_TRUE(cppx::numver("2.10.15").is_patch_compatible_with(quadnum_version()));
}

TEST(numver_tests, is_patch_compatible_with__incompatible_version__expect_false)
{
    EXPECT_FALSE(cppx::numver("1.10.15").is_patch_compatible_with(quadnum_version()));
    EXPECT_FALSE(cppx::numver("3.10.15").is_patch_compatible_with(quadnum_version()));
    EXPECT_FALSE(cppx::numver("2.11.16").is_patch_compatible_with(quadnum_version()));
    EXPECT_FALSE(cppx::numver("2.12.14").is_patch_compatible_with(quadnum_version()));
    EXPECT_FALSE(cppx::numver("2.10.16").is_patch_compatible_with(quadnum_version()));
    EXPECT_FALSE(cppx::numver("2.10.14").is_patch_compatible_with(quadnum_version()));
}

TEST(numver_tests, operator_eq__eq_version__expect_true)
{
    ASSERT_EQ(cppx::numver("2.4.5"), cppx::numver("2.4.5"));
}

TEST(numver_tests, operator_ne__ne_version__expect_true)
{
    ASSERT_NE(cppx::numver("2.4.5"), cppx::numver("2.4.6"));
}

TEST(numver_tests, operator_lt__lt_version__expect_true)
{
    ASSERT_LT(cppx::numver("2.4.5"), cppx::numver("2.4.6"));
    ASSERT_LT(cppx::numver("2.4.5"), cppx::numver("2.4.10"));
    ASSERT_LT(cppx::numver("2.4.5"), cppx::numver("2.5.5"));
    ASSERT_LT(cppx::numver("2.4.5"), cppx::numver("2.5.0"));
    ASSERT_LT(cppx::numver("2.4.5"), cppx::numver("3.4.5"));
    ASSERT_LT(cppx::numver("2.4.5"), cppx::numver("3.0.0"));
}

TEST(numver_tests, operator_le__le_version__expect_true)
{
    ASSERT_LE(cppx::numver("2.4.5"), cppx::numver("2.4.5"));
    ASSERT_LE(cppx::numver("2.4.5"), cppx::numver("2.4.6"));
    ASSERT_LE(cppx::numver("2.4.5"), cppx::numver("2.4.10"));
    ASSERT_LE(cppx::numver("2.4.5"), cppx::numver("2.5.5"));
    ASSERT_LE(cppx::numver("2.4.5"), cppx::numver("2.5.0"));
    ASSERT_LE(cppx::numver("2.4.5"), cppx::numver("3.4.5"));
    ASSERT_LE(cppx::numver("2.4.5"), cppx::numver("3.0.0"));
}

TEST(numver_tests, operator_lt__ge_version__expect_false)
{
    ASSERT_FALSE(cppx::numver("2.4.5") < cppx::numver("2.4.5"));
    ASSERT_FALSE(cppx::numver("2.4.6") < cppx::numver("2.4.5"));
}

TEST(numver_tests, operator_gt__gt_version__expect_true)
{
    ASSERT_GT(cppx::numver("2.4.6"), cppx::numver("2.4.5"));
    ASSERT_GT(cppx::numver("2.4.10"), cppx::numver("2.4.5"));
    ASSERT_GT(cppx::numver("2.5.5"), cppx::numver("2.4.5"));
    ASSERT_GT(cppx::numver("2.5.0"), cppx::numver("2.4.5"));
    ASSERT_GT(cppx::numver("3.4.5"), cppx::numver("2.4.5"));
    ASSERT_GT(cppx::numver("3.0.0"), cppx::numver("2.4.5"));
}

TEST(numver_tests, operator_ge__ge_version__expect_true)
{
    ASSERT_GE(cppx::numver("2.4.5"), cppx::numver("2.4.5"));
    ASSERT_GE(cppx::numver("2.4.6"), cppx::numver("2.4.5"));
    ASSERT_GE(cppx::numver("2.4.10"), cppx::numver("2.4.5"));
    ASSERT_GE(cppx::numver("2.5.5"), cppx::numver("2.4.5"));
    ASSERT_GE(cppx::numver("2.5.0"), cppx::numver("2.4.5"));
    ASSERT_GE(cppx::numver("3.4.5"), cppx::numver("2.4.5"));
    ASSERT_GE(cppx::numver("3.0.0"), cppx::numver("2.4.5"));
}

TEST(numver_tests, operator_gt__ge_version__expect_false)
{
    ASSERT_FALSE(cppx::numver("2.4.5") > cppx::numver("2.4.5"));
    ASSERT_FALSE(cppx::numver("2.4.5") > cppx::numver("3.4.5"));
}

TEST(numver_tests, std_format__version__correct_formatted_string)
{
    ASSERT_EQ(std::format("{}", cppx::numver(2, 10, 5)), "2.10.5");
}

TEST(numver_tests, constexpr__valid_args__no_compile_error)
{
    constexpr cppx::numver sv(0, 1, 5);
    static_assert(sv.major() == 0);
    static_assert(sv.minor() == 1);
    static_assert(sv.patch() == 5);

    constexpr cppx::numver sv2("15.13.234");
    static_assert(sv2.major() == 15);
    static_assert(sv2.minor() == 13);
    static_assert(sv2.patch() == 234);

    static_assert(sv != sv2);
    static_assert(sv < sv2);
}
