/*
 * Author: Milosz Barylowicz
 * Date:   2023
 */

#include <gtest/gtest.h>
#include "Vector.hpp"

namespace
{
constexpr int DEFAULT_VALUE = 100;
constexpr size_t DEFAULT_CAPACITY = 2;
} // namespace anonymous

namespace containers::ut
{
using namespace ::testing;


class VectorTestSuite : public Test
{
public:
    Vector<int> sut {DEFAULT_VALUE, DEFAULT_VALUE + 1};
};

TEST_F(VectorTestSuite, ShouldThrowWhenTryingToAccessOutOfRange)
{
    ASSERT_THROW(sut.at(sut.size() + 1), std::out_of_range);
}

TEST_F(VectorTestSuite, ShouldAccessAndBeAbleToModyfiElementsInrange)
{
    int& value = sut.at(1);
    ASSERT_EQ(value, DEFAULT_VALUE + 1);

    value++;
    ASSERT_EQ(sut.at(1), DEFAULT_VALUE + 2);
}

TEST_F(VectorTestSuite, ShouldCreateNonEmptyVector)
{
    ASSERT_FALSE(sut.empty());
}

TEST_F(VectorTestSuite, ShouldIncreaseCapacityWhenThereArevectorResizeInvoked)
{
    for (size_t i = 0; i < DEFAULT_CAPACITY; ++i)
    {
        sut.push_back(DEFAULT_VALUE);
    }

    ASSERT_EQ(DEFAULT_CAPACITY * 10, sut.capacity());
}

TEST_F(VectorTestSuite, ShouldCreateVectorWithDefaultCapacity)
{
    ASSERT_EQ(DEFAULT_CAPACITY, sut.capacity());
}

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
