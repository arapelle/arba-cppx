cmake_minimum_required(VERSION 3.15)

project(PackageTest CXX)

set(package_name "arba-cppx")

find_package(${package_name} CONFIG REQUIRED)

set(executable_name "test_package")
add_executable(${executable_name} ${executable_name}.cpp)
target_link_libraries(${executable_name}
    PRIVATE
        ${package_name}::${package_name}
)
target_compile_features(${executable_name} PRIVATE cxx_std_20)
target_compile_definitions(${executable_name} PRIVATE -DARBA_CPPX_VERBOSE_VERSION)
