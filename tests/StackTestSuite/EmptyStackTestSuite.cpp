#include <gtest/gtest.h>
#include "Stack.hpp"

namespace {

constexpr int EMPTY_STACK = 0;
constexpr int DEFAULT_VALUE = 100;
const auto EMPTY_VARIABLE = std::nullopt;

containers::Stack<int> BuildFilledStack(int value) {
    containers::Stack<int> result;
    for (size_t i = 0; i < 5; ++i) {
        result.emplace(value + i);
    }
    return result;
}
} // namespace anonymous

namespace containers::ut
{

using namespace testing;

class EmptyStackTestSuite : public Test {
public:
	Stack<int> sut;
};

TEST_F(EmptyStackTestSuite, ShouldAssignOtherStacckToEmptyOne) {
    Stack<int> result = BuildFilledStack(DEFAULT_VALUE);
    sut = result;

    ASSERT_EQ(result, sut);
}

TEST_F(EmptyStackTestSuite, ShouldReturnLastElementAsNull) {
    ASSERT_EQ(EMPTY_VARIABLE, sut.top());
}

TEST_F(EmptyStackTestSuite, ShouldSwapWithNonEmptyStack) {
    Stack<int> other = BuildFilledStack(DEFAULT_VALUE);

    sut.swap(other);
    ASSERT_FALSE(sut.empty());
    ASSERT_EQ(5, sut.size());
    ASSERT_EQ(DEFAULT_VALUE + 4, sut.top());
}

TEST_F(EmptyStackTestSuite, ShouldEmplaceVariable) {
    sut.emplace(10);

    ASSERT_FALSE(sut.empty());
    ASSERT_EQ(EMPTY_STACK + 1, sut.size());
    ASSERT_EQ(10, sut.top());
}

TEST_F(EmptyStackTestSuite, ShouldPushVariable) {
    sut.push(DEFAULT_VALUE);

    ASSERT_EQ(EMPTY_STACK + 1, sut.size());
    ASSERT_FALSE(sut.empty());
}

TEST_F(EmptyStackTestSuite, ShouldReturnIsEmpty) {
    ASSERT_EQ(EMPTY_STACK, sut.size());
    ASSERT_TRUE(sut.empty());
}

} // namespace containers::ut
