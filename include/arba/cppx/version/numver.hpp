#pragma once

#include "../preprocessor/exception.hpp"
#include "_private/extract_numver.hpp"
#include "concepts/numver.hpp"
#include "is_compatible_with.hpp"
#include <arba/cppx/compilation_error.hpp>
#include <arba/cppx/string/string_conversion.hpp>

#include <cstdint>
#include <format>
#include <tuple>

inline namespace arba
{
namespace cppx
{

class numver : public std::tuple<uint64_t, uint32_t, uint32_t>
{
public:
    using tuple_type = std::tuple<uint64_t, uint32_t, uint32_t>;

    constexpr numver();
    constexpr explicit numver(uint64_t major, uint32_t minor, uint32_t patch);
    constexpr explicit numver(const Numver auto& version);
    constexpr explicit numver(std::string_view version_str);

    constexpr numver(const numver&) = default;
    constexpr numver& operator=(const numver&) = default;

    inline constexpr uint64_t major() const noexcept { return std::get<0>(*this); }
    inline constexpr uint32_t minor() const noexcept { return std::get<1>(*this); }
    inline constexpr uint32_t patch() const noexcept { return std::get<2>(*this); }

    inline constexpr void set_major(uint64_t major) noexcept { std::get<0>(*this) = major; }
    inline constexpr void set_minor(uint32_t minor) noexcept { std::get<1>(*this) = minor; }
    inline constexpr void set_patch(uint32_t patch) noexcept { std::get<2>(*this) = patch; }

    inline constexpr void up_major() noexcept
    {
        ++std::get<0>(*this);
        std::get<1>(*this) = 0;
        std::get<2>(*this) = 0;
    }
    inline constexpr void up_minor() noexcept
    {
        ++std::get<1>(*this);
        std::get<2>(*this) = 0;
    }
    inline constexpr void up_patch() noexcept { ++std::get<2>(*this); }

    inline constexpr bool is_major_compatible_with(const Numver auto& rv) const noexcept
    {
        return cppx::is_major_compatible_with(*this, rv);
    }

    inline constexpr bool is_minor_compatible_with(const Numver auto& rv) const noexcept
    {
        return cppx::is_minor_compatible_with(*this, rv);
    }

    inline constexpr bool is_patch_compatible_with(const Numver auto& rv) const noexcept
    {
        return cppx::is_patch_compatible_with(*this, rv);
    }

private:
    static constexpr numver make_instance_(std::string_view version_str);
};

constexpr numver::numver() : tuple_type{ 0, 1, 0 }
{
}

constexpr numver::numver(uint64_t major, uint32_t minor, uint32_t patch) : tuple_type{ major, minor, patch }
{
}

constexpr numver::numver(const Numver auto& version)
    : tuple_type{ static_cast<uint64_t>(version.major()), static_cast<uint32_t>(version.minor()),
                  static_cast<uint32_t>(version.patch()) }
{
}

constexpr numver::numver(std::string_view version_str) : numver(make_instance_(version_str))
{
}

constexpr numver numver::make_instance_(std::string_view version_str)
{
    std::string_view major, minor, patch;
    if (!private_::extract_numver_(version_str, major, minor, patch)) [[unlikely]]
    {
        if (std::is_constant_evaluated())
        {
            compilation_error("'version_str' is not a valid version."
                              R"(regex to match: ^(0|[1-9]\d*)\.(0|[1-9]\d*)\.(0|[1-9]\d*)$)");
        }
        ARBA_CPPX_THROW(std::invalid_argument(std::string(version_str)));
    }
    return numver(stoi64(major), static_cast<uint32_t>(stoi64(minor)), static_cast<uint32_t>(stoi64(patch)));
}

} // namespace cppx
} // namespace arba

template <class CharT>
struct std::formatter<::arba::cppx::numver, CharT>
{
    template <class FormatParseContext>
    inline constexpr auto parse(FormatParseContext& ctx)
    {
        return ctx.begin();
    }

    template <class FormatContext>
    auto format(const ::arba::cppx::numver& version, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "{}.{}.{}", version.major(), version.minor(), version.patch());
    }
};
