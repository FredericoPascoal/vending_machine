// Smoke test: proves the toolchain, GoogleTest and CTest are wired correctly.
// Delete it once the first real (requirement-traced) test exists.
#include <gtest/gtest.h>

TEST(Smoke, ToolchainWorks) {
    EXPECT_EQ(1 + 1, 2);
}
