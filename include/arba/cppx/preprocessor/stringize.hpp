#pragma once

#include <format>

inline namespace arba
{
namespace cppx
{

#define ARBA_CPPX_PP_STRINGIZE_CODE(text_) #text_
#define ARBA_CPPX_PP_STRINGIZE(arg_) ARBA_CPPX_PP_STRINGIZE_CODE(arg_)

#ifndef CPPX_PP_STRINGIZE_CODE
#define CPPX_PP_STRINGIZE_CODE(text_) #text_
#else
#pragma message "CPPX_PP_STRINGIZE_CODE already exists. You must use ARBA_CPPX_PP_STRINGIZE_CODE instead."
#endif

#ifndef CPPX_PP_STRINGIZE
#define CPPX_PP_STRINGIZE(arg_) ARBA_CPPX_PP_STRINGIZE_CODE(arg_)
#else
#pragma message "CPPX_PP_STRINGIZE already exists. You must use ARBA_CPPX_PP_STRINGIZE instead."
#endif

} // namespace cppx
} // namespace arba
