/*
 * Author: Milosz Barylowicz
 * Date:   2023
 */

#include <gtest/gtest.h>
#include "Vector.hpp"

namespace
{
constexpr int DEFAULT_VALUE = 100;
constexpr size_t DEFAULT_CAPACITY = 10;
} // namespace anonymous

namespace containers::ut
{
using namespace ::testing;

class EmptyVectorTestSuite : public Test
{
public:
    Vector<int> sut;
};

// TEST_F(EmptyVectorTestSuite, ShouldThrowWhenAccessingElements) //TODO: investigate issue with this test-case
// {
//     ASSERT_THROW(sut.at(0), std::out_of_range);
// }

TEST_F(EmptyVectorTestSuite, ShouldCreateEmptyVector)
{
    ASSERT_TRUE(sut.empty());
}

TEST_F(EmptyVectorTestSuite, ShouldCreateEmptyVectorWIthDefaultCapacity)
{
    ASSERT_EQ(DEFAULT_CAPACITY, sut.capacity());
}

TEST_F(EmptyVectorTestSuite, ShouldPushBackNewElementsEvenWhenBasicCapacityWillBeCrossed)
{
    for (size_t i = 0; i < DEFAULT_CAPACITY + 2; ++i)
    {
        sut.push_back(DEFAULT_VALUE);
    }

    ASSERT_EQ(DEFAULT_CAPACITY + 2, sut.size());
}

TEST_F(EmptyVectorTestSuite, ShouldAssignNonEmptyVectorToEmptyOne)
{
    Vector<int> result {1,2,3,4,5};
    sut = result;

    ASSERT_EQ(result.size(), sut.size());
    ASSERT_EQ(result, sut);
}

TEST_F(EmptyVectorTestSuite, ShouldAddNewElement)
{
    sut.push_back(DEFAULT_VALUE);
    ASSERT_EQ(DEFAULT_VALUE, sut[0]);
}

TEST(EmptyVectorTester, ShouldCreateNewVectorFromExistingOne)
{
    Vector<int> other {1, 2, 3, 4, 5};
    Vector<int> sut(other);

    ASSERT_EQ(5, sut.size());
    ASSERT_EQ(5, sut[4]); // TODO: add matcher for whole vector
}

TEST(EmptyVectorTester, ShouldCreateNewVectorFromOtherCreatedInPlace)
{
    Vector<int> other {1, 2, 3, 4, 5};
    Vector<int> sut(std::move(other));

    ASSERT_EQ(5, sut.size());
    ASSERT_EQ(5, sut[4]); // TODO: add matcher for whole vector
}

} // namespace containers::ut
