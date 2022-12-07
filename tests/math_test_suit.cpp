#include <gtest/gtest.h>
#include "math.hpp"

using namespace ::testing;

TEST(InitialTestSuite, AddingTest)
{
    ASSERT_EQ(3, add(1, 2));
}