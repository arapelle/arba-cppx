#include <arba/cppx/cppx.hpp>
#include <arba/cppx/version.hpp>

#include <cstdlib>
#include <iostream>

int main()
{
    std::cout << arba::cppx::project_name() << std::endl;
    std::cout << "EXIT SUCCESS" << std::endl;
    return EXIT_SUCCESS;
}
