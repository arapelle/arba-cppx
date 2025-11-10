#include <arba/cppx/version.hpp>
#include <arba/cppx/version/semver.hpp>
#include <arba/cppx/policy/execution_policy.hpp>

#include <cstdlib>
#include <iostream>

int main()
{
    std::cout << std::boolalpha << "ARBA_CPPX_EXECUTION_ALL_STD_POLICIES: " <<
#ifdef ARBA_CPPX_EXECUTION_ALL_STD_POLICIES
        true
#else
        false
#endif
              << std::endl
              << "cppx::execution::are_all_std_policies_available(): "
              << cppx::execution::are_all_std_policies_available() << std::endl;
    std::cout << std::format("{}", cppx::semver("0.1.0-dev+metadata")) << std::endl;
    std::cout << "TEST PACKAGE SUCCESS" << std::endl;
    return EXIT_SUCCESS;
}
