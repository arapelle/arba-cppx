#pragma once

#include <execution>
#include <type_traits>

inline namespace arba
{
namespace cppx
{

template <class Type>
concept ExecutionPolicy = std::is_execution_policy_v<Type>;

} // namespace cppx
} // namespace arba
