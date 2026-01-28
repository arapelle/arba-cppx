cmake_minimum_required(VERSION 3.30)

# CMAKE INCLUDES

include(CMakePrintHelpers)

# CONFIGURATION

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug" "MinSizeRel" "RelWithDebInfo")
endif()

# C++ PROJECT

project("arba-cppx"
        VERSION 0.5.0
        DESCRIPTION "A C++ library providing essential features."
        HOMEPAGE_URL "https://github.com/arapelle/arba-cppx"
        LANGUAGES CXX)
message(STATUS "PROJECT : ${PROJECT_NAME} ${PACKAGE_SEMANTIC_VERSION} ${CMAKE_BUILD_TYPE}")

find_package(cmaketk 1.0.0 CONFIG REQUIRED COMPONENTS cpp_lib_project cpp_lib_test cpp_lib_example)

cmtk_set_package_name(CONTEXT_NAME "arba" SUBJECT_NAME "cppx")
string(TIMESTAMP configure_datetime "%Y%m%d-%H%M%S")
cmtk_set_package_semantic_version(${PROJECT_VERSION} PRE_RELEASE "dev" BUILD_METADATA "${configure_datetime}")

# C++ LIBRARY

## Generated/Configured headers:
cmtk_configure_headers(configured_headers
    FILES
        include/${PACKAGE_CONTEXT_NAME}/${PACKAGE_SUBJECT_NAME}/version.hpp.in
)

## Headers:
set(headers
    include/arba/cppx/compilation_error.hpp
    include/arba/cppx/policy/build_type.hpp
    include/arba/cppx/policy/endianness_policy.hpp
    include/arba/cppx/policy/exception_policy.hpp
    include/arba/cppx/policy/execution_policy.hpp
    include/arba/cppx/policy/thread_policy.hpp
    include/arba/cppx/preprocessor/auto_var_name.hpp
    include/arba/cppx/preprocessor/concat.hpp
    include/arba/cppx/preprocessor/exception.hpp
    include/arba/cppx/preprocessor/format_var.hpp
    include/arba/cppx/preprocessor/identity_type.hpp
    include/arba/cppx/preprocessor/stringize.hpp
    include/arba/cppx/string/string_constant.hpp
    include/arba/cppx/string/string_conversion.hpp
    include/arba/cppx/type_traits/demangled_type_name.hpp
    include/arba/cppx/type_traits/type_name.hpp
    include/arba/cppx/version/concepts/numver.hpp
    include/arba/cppx/version/concepts/semver.hpp
    include/arba/cppx/version/is_compatible_with.hpp
    include/arba/cppx/version/numver_constant.hpp
    include/arba/cppx/version/numver.hpp
    include/arba/cppx/version/_private/extract_numver.hpp
    include/arba/cppx/version/_private/extract_semver.hpp
    include/arba/cppx/version/semver.hpp
)

## Add C++ library:
cmtk_cxx_standard_option(${PROJECT_UPPER_VAR_NAME}_CXX_STANDARD MIN 20 MAX 26)

cmtk_add_cpp_library(${PROJECT_NAME} HEADER_ONLY
  HEADERS ${headers} ${configured_headers}
  CXX_STANDARD ${${PROJECT_UPPER_VAR_NAME}_CXX_STANDARD}
  DEFAULT_WARNING_OPTIONS
  DEFAULT_ERROR_OPTIONS
)
add_library("${PROJECT_CONTEXT_NAME}::${PROJECT_SUBJECT_NAME}" ALIAS ${PROJECT_NAME})

set(${PROJECT_UPPER_VAR_NAME}_EXECUTION_BACKEND "" CACHE STRING "Choose the backend for using all std::execution policies.")
set_property(CACHE ${PROJECT_UPPER_VAR_NAME}_EXECUTION_BACKEND PROPERTY STRINGS ";TBB")

if("${${PROJECT_UPPER_VAR_NAME}_EXECUTION_BACKEND}" STREQUAL "TBB")
    find_package(TBB 2022 CONFIG REQUIRED COMPONENTS tbb)
    target_link_libraries(${PROJECT_NAME} INTERFACE TBB::tbb)
    target_compile_definitions(${PROJECT_NAME} INTERFACE ARBA_CPPX_EXECUTION_ALL_STD_POLICIES=true)
endif()

## Add tests:
cmtk_add_test_subdirectory_if_built(test NAME ${PACKAGE_NAME})

## Add examples:
cmtk_add_example_subdirectory_if_built(example NAME ${PACKAGE_NAME})

# C++ INSTALL

## Install C++ library:
cmtk_install_targets(TARGETS ${PACKAGE_NAME} EXPORT ${PACKAGE_NAME}-targets NAMESPACE "${PACKAGE_NAME}::")

## Install project package
cmtk_install_package(${PACKAGE_NAME} INPUT_PACKAGE_CONFIG_FILE cmake/config/package-config.cmake.in)
cmtk_install_uninstall_script(${PACKAGE_NAME} LIB)
