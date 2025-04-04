#pragma once

#include <string_view>

inline namespace arba
{
namespace cppx
{
consteval bool is_type_name_available()
{
#if defined(__clang__) || defined(__GNUC__) || defined(_MSC_VER)
#define ARBA_CPPX_IS_TYPE_NAME_AVAILABLE true
    return true;
#else
#define ARBA_CPPX_IS_TYPE_NAME_AVAILABLE false
    return false;
#endif
}

template <typename T>
requires (is_type_name_available())
constexpr auto type_name() -> std::string_view;

namespace private_
{
struct type_name_info_base_
{
private:
    template <typename T>
    static consteval auto full_function_name_() -> std::string_view
    {
#if defined(__clang__) || defined(__GNUC__)
        return std::string_view{ __PRETTY_FUNCTION__ };
#elif defined(_MSC_VER)
        return std::string_view{ __FUNCSIG__ };
#else
        return std::string_view{"void"};
#endif
    }

    friend struct type_name_info_;
};

struct type_name_info_ : public type_name_info_base_
{
private:
    static constexpr auto prefix_offset_ = full_function_name_<void>().find("void");
    static constexpr auto suffix_offset_ = full_function_name_<void>().size() - prefix_offset_ - 4;

    static consteval auto type_name_(std::string_view function_name) -> std::string_view
    {
        const auto start = prefix_offset_;
        const auto end = function_name.size() - suffix_offset_;
        const auto size = end - start;
        return function_name.substr(start, size);
    }

    template <typename T>
    static consteval auto type_name_() -> std::string_view
    {
        return type_name_(full_function_name_<T>());
    }

    template <typename T>
    requires (is_type_name_available())
    friend constexpr auto ::arba::cppx::type_name() -> std::string_view;
};
} // namespace private_

template <typename T>
requires (is_type_name_available())
constexpr auto type_name() -> std::string_view
{
    if constexpr (std::is_same_v<T, std::string>)
        return std::string_view("std::string");
    else if constexpr (std::is_same_v<T, std::string_view>)
        return std::string_view("std::string_view");
    else
    {
        constexpr auto name = private_::type_name_info_::type_name_<T>();
        return name;
    }
}

} // namespace cppx
} // namespace arba

#ifndef CPPX_IS_TYPE_NAME_AVAILABLE
#define CPPX_IS_TYPE_NAME_AVAILABLE ARBA_CPPX_IS_TYPE_NAME_AVAILABLE
#else
#if not defined(NDEBUG) && (defined(__GNUC__) || defined(__GNUG__) || defined(_MSC_VER) || defined(__clang__))
#pragma message                                                                                                        \
"CPPX_IS_TYPE_NAME_AVAILABLE already exists. You must use ARBA_CPPX_IS_TYPE_NAME_AVAILABLE."
#endif
#endif
