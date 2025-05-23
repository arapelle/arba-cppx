cmake_minimum_required(VERSION 3.26)

# EXTERNAL DEPENDENCIES

add_subdirectory(external)

# CMAKE INCLUDES

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/external/cmake/)
include(CMakePrintHelpers)
include(cmtk/CppLibraryProject)

# CONFIGURATION

disable_in_source_build()
set_build_type_ifndef()

# C++ PROJECT

set_project_name(NAMESPACE "arba" FEATURE_NAME "cppx")
string(TIMESTAMP configure_datetime "%Y%m%d-%H%M%S")
set_project_semantic_version("0.3.0" BUILD_METADATA "${configure_datetime}")

project(${PROJECT_NAME}
        VERSION ${PROJECT_VERSION}
        DESCRIPTION "A C++ library providing essential features."
        HOMEPAGE_URL "https://github.com/arapelle/arba-cppx"
        LANGUAGES CXX)
message(STATUS "PROJECT : ${PROJECT_NAME} ${PROJECT_SEMANTIC_VERSION} ${CMAKE_BUILD_TYPE}")

# C++ LIBRARY

## Generated/Configured headers:
configure_headers(configured_headers
    FILES
        include/${PROJECT_NAMESPACE}/${PROJECT_FEATURE_NAME}/version.hpp.in
)

## Headers:
set(headers
    include/arba/cppx/compilation_error.hpp
    include/arba/cppx/policy/build_type.hpp
    include/arba/cppx/preprocessor/auto_var_name.hpp
    include/arba/cppx/preprocessor/concat.hpp
    include/arba/cppx/preprocessor/exception.hpp
    include/arba/cppx/preprocessor/format_var.hpp
    include/arba/cppx/preprocessor/identity_type.hpp
    include/arba/cppx/preprocessor/stringize.hpp
    include/arba/cppx/string/fixed_string.hpp
    include/arba/cppx/string/string_conversion.hpp
    include/arba/cppx/version/concepts/numver.hpp
    include/arba/cppx/version/concepts/semver.hpp
    include/arba/cppx/version/is_compatible_with.hpp
    include/arba/cppx/version/numver.hpp
    include/arba/cppx/version/semver.hpp
    include/arba/cppx/version/numver_constant.hpp
    include/arba/cppx/version/_private/extract_numver.hpp
    include/arba/cppx/version/_private/extract_semver.hpp
)

## Add C++ library:
cxx_standard_option(${PROJECT_UPPER_VAR_NAME}_CXX_STANDARD MIN 20 MAX 26)

add_cpp_library(${PROJECT_NAME} HEADER_ONLY
  HEADERS ${headers} ${configured_headers}
  CXX_STANDARD ${${PROJECT_UPPER_VAR_NAME}_CXX_STANDARD}
  DEFAULT_WARNING_OPTIONS
  DEFAULT_ERROR_OPTIONS
)
add_library("${PROJECT_NAMESPACE}::${PROJECT_FEATURE_NAME}${LIBRARY_TYPE_POSTFIX}" ALIAS ${PROJECT_NAME})

## Add tests:
add_test_subdirectory_if_build(test)

## Add examples:
add_example_subdirectory_if_build(example)

# C++ INSTALL

## Install C++ library:
install_cpp_libraries(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets)

## Install project package
install_library_package(${PROJECT_NAME} INPUT_PACKAGE_CONFIG_FILE cmake/config/package-config.cmake.in)
install_uninstall_script(${PROJECT_NAME})
