/*
 * Author: Milosz Barylowicz
 * Date:   2022-2023
 */

#include <gtest/gtest.h>
#include "Stack.hpp"

namespace containers::ut
{

namespace
{
constexpr int DEFAULT_VALUE = 100;
constexpr int EXPECTED_VALUE = 9;
constexpr size_t DEFAULT_SIZE = 10;

Stack<int> BuildFilledStack(int value)
{
    Stack<int> result;
    for (size_t i = 0; i < 5; ++i)
    {
        result.emplace(value + i);
    }

    return result;
}

} // namespace anonymous

using namespace testing;

class StackTestSuite : public Test
{
public:
    Stack<int> sut;
};

class NonEmptyStackTestSuite : public StackTestSuite
{
public:
    void SetUp() override
    {
        FillStackWithData();
        ASSERT_FALSE(sut.empty());
    }

    void ExpectThatThereIsAdditionalVariable() const
    {
        ASSERT_FALSE(sut.empty());
        ASSERT_EQ(11, sut.size());
        ASSERT_EQ(DEFAULT_VALUE, sut.top());
    }

private:
    void FillStackWithData()
    {
        for (size_t i = 0; i < DEFAULT_SIZE; ++i)
        {
            sut.emplace(i);
        }
    }
};

TEST_F(NonEmptyStackTestSuite, ShouldNotBeEqualIfThereAreDifferentValuesInStacksBuTheSameSizes)
{
    Stack<int> result;
    for (size_t i = 0; i < DEFAULT_SIZE; ++i)
    {
        result.push(DEFAULT_VALUE);
    }

    ASSERT_EQ(sut.size(), result.size());
    ASSERT_NE(sut, result);
}

TEST_F(NonEmptyStackTestSuite, ShouldNotBeEqualIfThereAreDifferentSizesOfStacks)
{
    Stack<int> result;
    result.push(DEFAULT_VALUE);

    ASSERT_NE(result, sut);
}

TEST_F(NonEmptyStackTestSuite, ShouldBuildStackBasedOnOtherOne)
{
    Stack<int> result(sut);
    ASSERT_EQ(sut, result);
}

TEST_F(NonEmptyStackTestSuite, ShouldPushNextVariable)
{
    sut.push(DEFAULT_VALUE);
    ExpectThatThereIsAdditionalVariable();
}

TEST_F(NonEmptyStackTestSuite, ShouldEmplaceNextVariable)
{
    sut.emplace(100);
    ExpectThatThereIsAdditionalVariable();
}

TEST_F(NonEmptyStackTestSuite, ShouldSwapTwoStacksWithEachOther)
{
    Stack<int> other = BuildFilledStack(DEFAULT_VALUE);

    sut.swap(other);

    ASSERT_FALSE(sut.empty());
    ASSERT_EQ(5, sut.size());
}

TEST_F(NonEmptyStackTestSuite, ShouldReturnSizeEqToPushCallTimesAndItIsMoreThenOnce)
{
    ASSERT_EQ(EXPECTED_VALUE, sut.top());
    ASSERT_EQ(DEFAULT_SIZE, sut.size());
}

} // namespace containers::ut
