#include <arba/cppx/version/_private/extract_numver.hpp>

#include <gtest/gtest.h>

inline namespace arba
{
namespace cppx
{
namespace private_
{

[[nodiscard]] constexpr bool extract_version_number_(std::string_view version, std::string_view& num_sv,
                                                     std::string_view sep, bool end_is_ok)
{
    auto iter = version.cbegin();
    return extract_version_number_(iter, version.cend(), num_sv, sep, end_is_ok);
}

} // namespace private_
} // namespace cppx
} // namespace arba

using namespace cppx::private_;

// extract_version_number

TEST(extract_numver, extract_version_number__empty_str__false)
{
    std::string_view num_sv;
    ASSERT_FALSE(extract_version_number_("", num_sv, ".-+", true));
    ASSERT_FALSE(extract_version_number_(".", num_sv, ".-+", true));
    ASSERT_FALSE(extract_version_number_("-", num_sv, ".-+", true));
    ASSERT_FALSE(extract_version_number_("+", num_sv, ".-+", true));
}

TEST(extract_numver, extract_version_number__bad_char__false)
{
    std::string_view num_sv;
    ASSERT_FALSE(extract_version_number_("#", num_sv, ".-+", true));
}

TEST(extract_numver, extract_version_number__0_good_next__true)
{
    std::string_view num_sv;
    ASSERT_TRUE(extract_version_number_("0.", num_sv, ".", false));
    ASSERT_EQ(num_sv, "0");
}

TEST(extract_numver, extract_version_number__0_end_is_ok__true)
{
    std::string_view num_sv;
    ASSERT_TRUE(extract_version_number_("0", num_sv, "-+", true));
    ASSERT_EQ(num_sv, "0");
}

TEST(extract_numver, extract_version_number__0_bad_next__false)
{
    std::string_view num_sv;
    ASSERT_FALSE(extract_version_number_("00", num_sv, ".-+", false));
}

TEST(extract_numver, extract_version_number__0_end_is_not_ok__false)
{
    std::string_view num_sv;
    ASSERT_FALSE(extract_version_number_("0", num_sv, ".", false));
}

TEST(extract_numver, extract_version_number__pos_num_good_next__true)
{
    std::string_view num_sv;
    ASSERT_TRUE(extract_version_number_("112.", num_sv, ".", false));
    ASSERT_EQ(num_sv, "112");
}

TEST(extract_numver, extract_version_number__pos_num_end_is_ok__true)
{
    std::string_view num_sv;
    ASSERT_TRUE(extract_version_number_("112", num_sv, "-+", true));
    ASSERT_EQ(num_sv, "112");
}

TEST(extract_numver, extract_version_number__pos_num_bad_next__false)
{
    std::string_view num_sv;
    ASSERT_FALSE(extract_version_number_("112#", num_sv, ".-+", false));
}

TEST(extract_numver, extract_version_number__pos_num_end_is_not_ok__false)
{
    std::string_view num_sv;
    ASSERT_FALSE(extract_version_number_("112", num_sv, ".", false));
}

// extract_version_core

TEST(extract_numver, extract_version_core__empty_str__false)
{
    std::string_view major, minor, patch;
    ASSERT_FALSE(extract_numver_("", major, minor, patch));
}

TEST(extract_numver, extract_version_core__valid_end_is_ok__true)
{
    std::string_view major, minor, patch;
    ASSERT_TRUE(extract_numver_("0.0.0", major, minor, patch));
    ASSERT_EQ(major, "0");
    ASSERT_EQ(minor, "0");
    ASSERT_EQ(patch, "0");
    ASSERT_TRUE(extract_numver_("56.178.4", major, minor, patch));
    ASSERT_EQ(major, "56");
    ASSERT_EQ(minor, "178");
    ASSERT_EQ(patch, "4");
    ASSERT_TRUE(extract_numver_("5.1.42", major, minor, patch));
    ASSERT_EQ(major, "5");
    ASSERT_EQ(minor, "1");
    ASSERT_EQ(patch, "42");
}

TEST(extract_numver, extract_version_core__valid_good_next__true)
{
    std::string_view major, minor, patch;
    ASSERT_TRUE(extract_numver_("0.0.0-", major, minor, patch));
    ASSERT_EQ(major, "0");
    ASSERT_EQ(minor, "0");
    ASSERT_EQ(patch, "0");
    ASSERT_TRUE(extract_numver_("56.178.4-", major, minor, patch));
    ASSERT_EQ(major, "56");
    ASSERT_EQ(minor, "178");
    ASSERT_EQ(patch, "4");
    ASSERT_TRUE(extract_numver_("5.1.42-", major, minor, patch));
    ASSERT_EQ(major, "5");
    ASSERT_EQ(minor, "1");
    ASSERT_EQ(patch, "42");
    ASSERT_TRUE(extract_numver_("0.0.0+", major, minor, patch));
    ASSERT_EQ(major, "0");
    ASSERT_EQ(minor, "0");
    ASSERT_EQ(patch, "0");
    ASSERT_TRUE(extract_numver_("56.178.4+", major, minor, patch));
    ASSERT_EQ(major, "56");
    ASSERT_EQ(minor, "178");
    ASSERT_EQ(patch, "4");
    ASSERT_TRUE(extract_numver_("5.1.42+", major, minor, patch));
    ASSERT_EQ(major, "5");
    ASSERT_EQ(minor, "1");
    ASSERT_EQ(patch, "42");
}

TEST(extract_numver, extract_version_core__valid_bad_next__false)
{
    std::string_view major, minor, patch;
    ASSERT_FALSE(extract_numver_("0.0.0#", major, minor, patch));
    ASSERT_FALSE(extract_numver_("56.178.4#", major, minor, patch));
    ASSERT_FALSE(extract_numver_("5.1.42#", major, minor, patch));
}
