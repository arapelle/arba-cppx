#pragma once

#include <string_view>

inline namespace arba
{
namespace cppx
{

#ifdef NDEBUG
#define ARBA_CPPX_RELEASE_BUILD
#else
#define ARBA_CPPX_DEBUG_BUILD
#endif

struct release_build_t
{
    explicit release_build_t() = default;
    static constexpr std::string_view name() noexcept
    {
        return
#if defined(ARBA_CPPX_RELEASE_BUILD) && defined(ARBA_CPPX_BUILD_TYPE)
            ARBA_CPPX_BUILD_TYPE
#else
            "Release"
#endif
            ;
    }
    static constexpr bool is_debug() noexcept { return false; }
    static constexpr bool is_release() noexcept { return true; }
};
constexpr release_build_t release_build;

struct debug_build_t
{
    explicit debug_build_t() = default;
    static constexpr std::string_view name() noexcept
    {
        return
#if defined(ARBA_CPPX_DEBUG_BUILD) && defined(ARBA_CPPX_BUILD_TYPE)
            ARBA_CPPX_BUILD_TYPE
#else
            "Debug"
#endif
            ;
    }
    static constexpr bool is_debug() noexcept { return true; }
    static constexpr bool is_release() noexcept { return false; }
};
constexpr debug_build_t debug_build;

#ifdef ARBA_CPPX_RELEASE_BUILD
using build_type_t = release_build_t;
#else
using build_type_t = debug_build_t;
#endif
constexpr build_type_t build_type;
}
}
