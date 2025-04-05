#pragma once

#include "concat.hpp"

inline namespace arba
{
namespace cppx
{

#define ARBA_CPPX_AUTO_VAR_NAME ARBA_CPPX_PP_CONCAT(ARBA_CPPX_PP_CONCAT(var_, __LINE__), _)

#ifndef CPPX_AUTO_VAR_NAME
#define CPPX_AUTO_VAR_NAME ARBA_CPPX_AUTO_VAR_NAME
#else
#pragma message "CPPX_AUTO_VAR_NAME already exists. You must use ARBA_CPPX_AUTO_VAR_NAME instead."
#endif

} // namespace cppx
} // namespace arba
