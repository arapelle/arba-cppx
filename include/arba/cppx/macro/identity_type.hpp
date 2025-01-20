#pragma once

inline namespace arba
{
namespace cppx
{
namespace private_
{
template <typename>
struct first_function_arg_type_;
template <typename T>
struct first_function_arg_type_<void(T)>
{
    typedef T type;
};
} // namespace private_

#define ARBA_CPPX_IDENTITY_TYPE(type_) typename arba::cppx::private_::first_function_arg_type_<void(type_)>::type

#ifndef CPPX_IDENTITY_TYPE
#define CPPX_IDENTITY_TYPE(arg_) ARBA_CPPX_IDENTITY_TYPE(arg_)
#else
#pragma message "CPPX_IDENTITY_TYPE already exists. You must use ARBA_CPPX_IDENTITY_TYPE instead."
#endif

} // namespace cppx
} // namespace arba
