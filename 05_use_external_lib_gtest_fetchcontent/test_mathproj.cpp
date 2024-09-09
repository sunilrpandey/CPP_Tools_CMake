#include <gtest/gtest.h>

#include "mathlib.h"

// Demonstrate some basic assertions.
TEST(MathLibTest, SumTest) {
  // Expect two strings not to be equal.
  EXPECT_EQ(11, sum(3,8));
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
