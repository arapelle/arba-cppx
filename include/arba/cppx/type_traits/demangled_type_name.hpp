#pragma once

#if __has_include(<cxxabi.h>)
#include <cxxabi.h>

#include <cstdlib>
#include <memory>
#include <string>
#include <typeinfo>

inline namespace arba
{
namespace cppx
{
inline consteval bool is_demangled_type_name_available()
{
    return true;
}
#define ARBA_CPPX_IS_DEMANGLED_TYPE_NAME_AVAILABLE true

// https://stackoverflow.com/questions/281818/unmangling-the-result-of-stdtype-infoname

namespace private_
{
inline std::string demangle_(const char* name)
{
    int status = -1;
    std::unique_ptr<char, void (*)(void*)> res{ abi::__cxa_demangle(name, NULL, NULL, &status), std::free };
    return (status == 0) ? res.get() : name;
}
} // namespace private_

template <class Type>
std::string demangled_type_name(const Type& arg)
{
    return private_::demangle_(typeid(arg).name());
}

template <class Type>
std::string demangled_type_name()
{
    return private_::demangle_(typeid(Type).name());
}

} // namespace cppx
} // namespace arba

#else
inline namespace arba
{
namespace cppx
{
inline consteval bool is_demangled_type_name_available()
{
    return false;
}
#define ARBA_CPPX_IS_DEMANGLED_TYPE_NAME_AVAILABLE false
} // namespace cppx
} // namespace arba
#endif

#ifndef CPPX_IS_DEMANGLED_TYPE_NAME_AVAILABLE
#define CPPX_IS_DEMANGLED_TYPE_NAME_AVAILABLE ARBA_CPPX_IS_DEMANGLED_TYPE_NAME_AVAILABLE
#else
#if not defined(NDEBUG) && (defined(__GNUC__) || defined(__GNUG__) || defined(_MSC_VER) || defined(__clang__))
#pragma message                                                                                                        \
    "CPPX_IS_DEMANGLED_TYPE_NAME_AVAILABLE already exists. You must use ARBA_CPPX_IS_DEMANGLED_TYPE_NAME_AVAILABLE."
#endif
#endif
