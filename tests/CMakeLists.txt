include(FetchContent)

# GoogleTest is downloaded at configure time and pinned by hash, so every
# build (local and CI) uses exactly the same, verified source.
FetchContent_Declare(
    googletest
    URL      https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
    URL_HASH SHA256=7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926
    SYSTEM   # its headers are -isystem: our strict warnings don't fire on them
)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK   ON  CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(vending_tests
    smoke_test.cpp
)

target_link_libraries(vending_tests PRIVATE
    vending_project_options
    vending_core
    GTest::gtest_main
)

# Registers each TEST() as a separate CTest test (visible in `ctest -N`).
gtest_discover_tests(vending_tests)
