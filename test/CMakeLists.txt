
include(GoogleTest)

find_package(GTest 1.14 CONFIG REQUIRED)
find_package(cmakecc 1.0.0 CONFIG REQUIRED)
find_package(cmaketk 1.0.0 CONFIG REQUIRED cpp_lib_test cpp_cmake_workflow_test)

cmtk_add_cpp_library_basic_gtests(${PROJECT_NAME} GTest::gtest_main
    SOURCES
        project_version_tests.cpp
)

add_subdirectory(preprocessor)
add_subdirectory(string)
add_subdirectory(version)
add_subdirectory(type_traits)
add_subdirectory(policy)

cmtk_add_cpp_cmake_workflow_gtest_if_built(${PACKAGE_NAME} GTest::gtest_main PACKAGE_TYPE "lib")
