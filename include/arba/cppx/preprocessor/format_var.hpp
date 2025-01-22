#pragma once

#include <format>

inline namespace arba
{
namespace cppx
{

#ifndef ARBA_CPPX_PP_VAR_FORMAT_STRING
#define ARBA_CPPX_PP_VAR_FORMAT_STRING "{} = {}"
#endif

#define ARBA_CPPX_PP_FORMAT_VAR(arg_) std::format(ARBA_CPPX_PP_VAR_FORMAT_STRING, #arg_, arg_)

#ifndef CPPX_PP_FORMAT_VAR
#define CPPX_PP_FORMAT_VAR(arg_) std::format(ARBA_CPPX_PP_VAR_FORMAT_STRING, #arg_, arg_)
#else
#pragma message "CPPX_PP_FORMAT_VAR already exists. You must use ARBA_CPPX_PP_FORMAT_VAR instead."
#endif

} // namespace cppx
} // namespace arba
