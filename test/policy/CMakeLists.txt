
cmtk_add_cpp_library_gtest(build_type_tests ${PROJECT_NAME} GTest::gtest_main
    SOURCES
        build_type_tests.cpp
)

cmtk_add_cpp_library_gtest(custom_build_type_tests ${PROJECT_NAME} GTest::gtest_main
    SOURCES
        custom_build_type_tests.cpp
)
target_compile_definitions(custom_build_type_tests PUBLIC -DARBA_CPPX_BUILD_TYPE="Custom${CMAKE_BUILD_TYPE}")

cmtk_add_cpp_library_basic_gtests(${PROJECT_NAME} GTest::gtest_main
    SOURCES
        endianness_policy_tests.cpp
        exception_policy_tests.cpp
        execution_policy_tests.cpp
        thread_policy_tests.cpp
)
