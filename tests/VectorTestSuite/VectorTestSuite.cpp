/*
 * Author: Milosz Barylowicz
 * Date:   2023
 */

#include <gtest/gtest.h>
#include "Vector.hpp"

namespace
{
constexpr int DEFAULT_VALUE = 100;
} // namespace anonymous

namespace containers::ut
{
using namespace ::testing;


class VectorTestSuite : public Test
{
public:
    Vector<int> sut {DEFAULT_VALUE, DEFAULT_VALUE + 1};
};

TEST_F(VectorTestSuite, ShouldModifyElementUsingAccessOperator)
{
    sut[1]++;
    ASSERT_EQ(DEFAULT_VALUE + 2, sut[1]);
}

TEST_F(VectorTestSuite, ShouldAssingNonEmptyVectorWithDifferentSize)
{
    Vector<int> result {DEFAULT_VALUE + 10, DEFAULT_VALUE + 20, DEFAULT_VALUE + 30};

    sut = result;

    ASSERT_EQ(result.size(), sut.size());
    ASSERT_EQ(result, sut);
}

TEST_F(VectorTestSuite, ShouldAssignTwoVectorsWithTheSameSizeButDifferentValues)
{
    Vector<int> result {DEFAULT_VALUE + 10, DEFAULT_VALUE + 20};

    sut = result;

    ASSERT_EQ(result, sut);
}

TEST_F(VectorTestSuite, ShouldAddNewElement)
{
    sut.push_back(DEFAULT_VALUE + 2);
    ASSERT_EQ(DEFAULT_VALUE + 2, sut[2]);
}

TEST(VectorTest, ShouldCreateMoreThen10ElementsInVector)
{
    Vector<int> sut {DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE,
        DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE + 1};
    ASSERT_EQ(12, sut.size());
    ASSERT_EQ(DEFAULT_VALUE + 1, sut[11]);
}

} // namespace containers::ut
