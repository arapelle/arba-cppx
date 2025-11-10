#pragma once

#include <execution>
#include <type_traits>

inline namespace arba
{
namespace cppx
{

template <class Type>
concept ExecutionPolicy = std::is_execution_policy_v<Type>;

namespace execution
{
consteval bool are_all_std_policies_available()
{
    return
#ifdef ARBA_CPPX_EXECUTION_ALL_STD_POLICIES
        true
#else
        false
#endif
        ;
}

} // namespace execution
} // namespace cppx
} // namespace arba
