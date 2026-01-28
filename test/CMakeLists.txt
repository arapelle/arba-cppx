
include(GoogleTest)

find_package(GTest 1.14 CONFIG REQUIRED)

cmtk_add_cpp_library_basic_gtests(${PROJECT_NAME} GTest::gtest_main
    SOURCES
        project_version_tests.cpp
)

add_subdirectory(preprocessor)
add_subdirectory(string)
add_subdirectory(version)
add_subdirectory(type_traits)
add_subdirectory(policy)
