
add_cpp_library_basic_tests(${PROJECT_NAME} GTest::gtest_main
    SOURCES
        stringize_tests.cpp
        concat_tests.cpp
        identity_type_tests.cpp
        format_var_tests.cpp
        exception_tests.cpp
        exception_no_exceptions_tests.cpp
)
