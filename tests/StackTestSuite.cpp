/*
 * Author: Milosz Barylowicz
 * Date:   2022
 */

#include <gtest/gtest.h>
#include "Stack.hpp"

namespace containers::ut
{

namespace
{
constexpr int DEFAULT_VALUE = 100;
constexpr int EMPTY_STACK = 0;
constexpr int EXPECTED_VALUE = 9;
const auto EMPTY_VARIABLE = std::nullopt;

Stack<int> BuildFilledStack(int value)
{
    Stack<int> result;
    for (size_t i = 0; i < 5; ++i)
    {
        result.emplace(value + i);
    }

    return result;
}

} // namespace anonymus

using namespace ::testing;

class StackTestSuite : public Test
{
public:
    Stack<int> sut;
};

class EmptyStackTestSuite : public StackTestSuite
{};

TEST_F(EmptyStackTestSuite, ShouldReturnLastElementAsNull)
{
    ASSERT_EQ(EMPTY_VARIABLE, sut.top());
}

TEST_F(EmptyStackTestSuite, ShouldSwapWithNonEmptyStack)
{
    Stack<int> other = BuildFilledStack(DEFAULT_VALUE);

    sut.swap(other);
    ASSERT_FALSE(sut.empty());
    ASSERT_EQ(5, sut.size());
    ASSERT_EQ(DEFAULT_VALUE + 4, sut.top());
}

TEST_F(EmptyStackTestSuite, ShouldEmplaceVariable)
{
    sut.emplace(10);

    ASSERT_FALSE(sut.empty());
    ASSERT_EQ(EMPTY_STACK + 1, sut.size());
    ASSERT_EQ(10, sut.top());
}

TEST_F(EmptyStackTestSuite, ShouldPushVariable)
{
    sut.push(DEFAULT_VALUE);

    ASSERT_EQ(EMPTY_STACK + 1, sut.size());
    ASSERT_FALSE(sut.empty());
}

TEST_F(EmptyStackTestSuite, ShouldReturnIsEmpty)
{
    ASSERT_EQ(EMPTY_STACK, sut.size());
    ASSERT_TRUE(sut.empty());
}

class NonEmptyStackTestSuite : public StackTestSuite
{
public:
    void SetUp() override
    {
        FillStackWithData();
        ASSERT_FALSE(sut.empty());
    }

    void FillStackWithData()
    {
        for (size_t i = 0; i < 10; ++i)
        {
            sut.emplace(i);
        }
    }

    void ExpectThatThereIsAdditionalVariable() const
    {
        ASSERT_FALSE(sut.empty());
        ASSERT_EQ(11, sut.size());
        ASSERT_EQ(DEFAULT_VALUE, sut.top());
    }
};

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
    ASSERT_EQ(10, sut.size());
}

} // namespace containers::ut
