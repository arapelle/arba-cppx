find_package(cmaketk 1.0.0 CONFIG REQUIRED COMPONENTS cpp_lib_example)

cmtk_add_cpp_library_basic_examples(${PROJECT_NAME}
    SOURCES
        example.cpp
)
