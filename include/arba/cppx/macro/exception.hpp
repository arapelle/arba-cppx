#pragma once

#ifdef ARBA_CPPX_NO_EXCEPTIONS
#include <cstdio>
#include <cstdlib>
#include <format>
#ifndef NDEBUG
#include <version>
// clang-format off
#if __cpp_lib_debugging >= 202311L
// clang-format on
#include <debug>
#endif
#endif
#endif

inline namespace arba
{
namespace cppx
{

#ifndef ARBA_CPPX_NO_EXCEPTIONS

#define ARBA_CPPX_TRY try
#define ARBA_CPPX_CATCH(exce_decl__) catch (exce_decl__)
#define ARBA_CPPX_THROW(exce__, ...) throw(exce__)

#else

#define ARBA_CPPX_TRY
#define ARBA_CPPX_CATCH(exce_decl) if constexpr (false)

// clang-format off
#if __cpp_lib_debugging >= 202311L
// clang-format on
#define ARBA_CPPX_THROW(exce, ...)                                                                                     \
    (std::fprintf(stderr, "%s", std::format("" __VA_OPT__("{}", ) __VA_ARGS__).data()),                                \
     std::breakpoint_if_debugging(), std::abort(), 0)
#else
#define ARBA_CPPX_THROW(exce, ...)                                                                                     \
    (std::fprintf(stderr, "%s", std::format("" __VA_OPT__("{}", ) __VA_ARGS__).data()), std::abort(), 0)
#endif

#endif

#ifndef CPPX_TRY
#define CPPX_TRY ARBA_CPPX_TRY
#else
#pragma message "CPPX_TRY already exists. You must use ARBA_CPPX_TRY instead."
#endif

#ifndef CPPX_CATCH
#define CPPX_CATCH(exce_decl__) ARBA_CPPX_CATCH(exce_decl__)
#else
#pragma message "CPPX_CATCH already exists. You must use ARBA_CPPX_CATCH instead."
#endif

#ifndef CPPX_THROW
#define CPPX_THROW(exce_decl__, ...) ARBA_CPPX_THROW(exce_decl__ __VA_OPT__(, ) __VA__ARGS__)
#else
#pragma message "CPPX_THROW already exists. You must use ARBA_CPPX_THROW instead."
#endif

} // namespace cppx
} // namespace arba
