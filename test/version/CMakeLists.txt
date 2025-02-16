
add_cpp_library_basic_tests(${PROJECT_NAME} GTest::gtest_main
    SOURCES
        extract_semver_tests.cpp
        extract_numver_tests.cpp
        numver_tests.cpp
        numver_constant_tests.cpp
        semver_tests.cpp
)
