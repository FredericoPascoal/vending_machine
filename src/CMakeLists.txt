# Core library: all vending machine logic, with no main().
# The tests (and later the executable) link against it.
add_library(vending_core STATIC
    produto.cpp
)

# PUBLIC: vending_core needs these headers to compile, and so does anyone
# who links against it (e.g. the tests doing #include "vending/produto.h").
target_include_directories(vending_core PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# PRIVATE: the strict warnings apply when compiling this library's own .cpp files.
target_link_libraries(vending_core PRIVATE
    vending_project_options
)
