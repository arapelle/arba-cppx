
add_cpp_library_basic_tests(${PROJECT_NAME} GTest::gtest_main
    SOURCES
        stringize_tests.cpp
        identity_type_tests.cpp
        format_var_tests.cpp
)
