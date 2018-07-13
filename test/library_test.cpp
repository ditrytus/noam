#include <include/gtest/gtest.h>
#include "library.h"

TEST(LibraryTest, ReturnsOne) {
    EXPECT_EQ(one(), 1) << "one() should return integer 1.";
}