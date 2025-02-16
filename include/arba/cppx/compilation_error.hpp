#pragma once

inline namespace arba
{
namespace cppx
{

inline void compilation_error(...)
{
    throw "This function must only be called in constant context. (ex: cppx::compilation_error(\"error message\");)";
}

} // namespace cppx
} // namespace arba
