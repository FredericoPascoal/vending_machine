cmake_minimum_required(VERSION 3.25)

project(vending_machine
    VERSION 0.1.0
    DESCRIPTION "Vending machine - modern C++ learning project"
    LANGUAGES CXX
)

# ---------------------------------------------------------------------------
# Language standard
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)          # -std=c++20, not -std=gnu++20

# compile_commands.json is consumed by clang-tidy, cppcheck and IDEs.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------
option(VENDING_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)
option(VENDING_ENABLE_SANITIZERS  "Build with AddressSanitizer + UBSan" OFF)
option(VENDING_BUILD_TESTS        "Build the unit/integration tests" ON)

# ---------------------------------------------------------------------------
# Shared build settings, applied to OUR targets only (never to third-party code)
# ---------------------------------------------------------------------------
add_library(vending_project_options INTERFACE)

target_compile_options(vending_project_options INTERFACE
    -Wall -Wextra -Wpedantic
    -Wshadow                 # a local hides a member/outer variable
    -Wconversion             # implicit narrowing (e.g. double -> int)
    -Wsign-conversion        # implicit signed <-> unsigned
    -Wnon-virtual-dtor       # polymorphic class without virtual destructor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wnull-dereference
    $<$<BOOL:${VENDING_WARNINGS_AS_ERRORS}>:-Werror>
)

if(VENDING_ENABLE_SANITIZERS)
    target_compile_options(vending_project_options INTERFACE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -fno-sanitize-recover=all  # UB aborts the test instead of only printing
    )
    target_link_options(vending_project_options INTERFACE
        -fsanitize=address,undefined
    )
endif()

# ---------------------------------------------------------------------------
# Production code
# ---------------------------------------------------------------------------
# The core library will live in src/ once the first class exists (Produto).
# Then uncomment the line below; src/CMakeLists.txt will define `vending_core`.
# add_subdirectory(src)

# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------
if(VENDING_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
