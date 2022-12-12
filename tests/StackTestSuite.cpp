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
} // namespace anonymus

using namespace ::testing;

class StackTestSuite : public Test
{
public:
    Stack<int> sut;
};

TEST_F(StackTestSuite, ShouldEmplaceValueOnEmptyStack)
{
    sut.emplace(10);

    ASSERT_FALSE(sut.empty());
    ASSERT_EQ(EMPTY_STACK + 1, sut.size());
    ASSERT_EQ(10, sut.top());
}

TEST_F(StackTestSuite, ShouldReturnSizeEqToPushCallTimesAndItIsMoreThenOnce)
{
    sut.push(DEFAULT_VALUE);
    sut.push(DEFAULT_VALUE + 1);

    ASSERT_FALSE(sut.empty());
    ASSERT_EQ(EMPTY_STACK + 2, sut.size());
    ASSERT_EQ(DEFAULT_VALUE + 1, sut.top());
}

TEST_F(StackTestSuite, ShouldReturnSizeNotEqZeroWhenElementWasPushedOnStack)
{
    sut.push(DEFAULT_VALUE);

    ASSERT_EQ(EMPTY_STACK + 1, sut.size());
    ASSERT_FALSE(sut.empty());
}

TEST_F(StackTestSuite, ShouldReturnSizeEqZeroWhenStackWasJustCreated)
{
    ASSERT_EQ(EMPTY_STACK, sut.size());
    ASSERT_TRUE(sut.empty());
}

TEST_F(StackTestSuite, ShouldReturnNonEmptyWhenPushingValueOnStack)
{
    sut.push(DEFAULT_VALUE);
    ASSERT_FALSE(sut.empty());
}

} // namespace containers::ut
