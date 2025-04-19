
add_cpp_library_basic_tests(${PROJECT_NAME} GTest::gtest_main
    SOURCES
        stringize_tests.cpp
        concat_tests.cpp
        auto_var_name_tests.cpp
        identity_type_tests.cpp
        format_var_tests.cpp
        exception_tests.cpp
)

add_cpp_library_test(exception_no_exceptions_tests ${PROJECT_NAME} GTest::gtest_main
    SOURCES
        exception_no_exceptions_tests.cpp
)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(exception_no_exceptions_tests PUBLIC -fno-exceptions)
endif()
