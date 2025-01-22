#pragma once

inline namespace arba
{
namespace cppx
{

#define ARBA_CPPX_PP_CONCAT_CODE(left_, right_) left_##right_
#define ARBA_CPPX_PP_CONCAT(left_, right_) CPPX_PP_CONCAT_CODE(left_, right_)

#ifndef CPPX_PP_CONCAT_CODE
#define CPPX_PP_CONCAT_CODE(left_, right_) left_##right_
#else
#pragma message "CPPX_PP_CONCAT_CODE already exists. You must use ARBA_CPPX_PP_CONCAT_CODE instead."
#endif

#ifndef CPPX_PP_CONCAT
#define CPPX_PP_CONCAT(left_, right_) ARBA_CPPX_PP_CONCAT(left_, right_)
#else
#pragma message "CPPX_PP_CONCAT already exists. You must use ARBA_CPPX_PP_CONCAT instead."
#endif

} // namespace cppx
} // namespace arba
