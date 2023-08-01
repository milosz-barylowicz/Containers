#include <gtest/gtest.h>
#include "list.hpp"

namespace {

constexpr containers::list<int>::size_type EMPTY = 0;
constexpr int DEFAULT_VALUE = 57;
constexpr auto NO_ELEMENT_EXPECTED = std::nullopt;
constexpr containers::list<int>::size_type MAX_ELEMENT_COUNT = std::numeric_limits<size_t>::max();

containers::list<int> BuildExpectedNonEmptyListWithSingleElement() {
    containers::list<int> result;
    result.push_back(DEFAULT_VALUE);

    return result;
}

containers::list<int> BuildListWithValueAndSize(containers::list<int>::size_type count, containers::list<int>::value_type value) {
    containers::list<int> result;
    for (containers::list<int>::size_type i = 0; i < count; ++i) {
        result.push_back(value);
    }

    return result;
}

containers::list<int> EXPECTED_LIST_WITH_ONE_ELEMET = BuildExpectedNonEmptyListWithSingleElement();
containers::list<int> EXPECTED_EMPTY_LIST;

} // namespace

namespace containers::ut {

using namespace ::testing;

class EmptyListTestSuite : public Test {
public:
    void EvaluateThatListIsEmpty() {
        ASSERT_EQ(sut, EXPECTED_EMPTY_LIST);
        ASSERT_EQ(sut.size(), EMPTY);
    }

    list<int> sut;
};

TEST_F(EmptyListTestSuite, ShouldAssignGivenValueGivenTimes) {
    sut.assign(5, DEFAULT_VALUE);
    ASSERT_EQ(sut, BuildListWithValueAndSize(5, DEFAULT_VALUE));
}

TEST_F(EmptyListTestSuite, ShouldDoNotChangeAnythingWhenTryingToPopFrontElement) {
    sut.pop_front();
    EvaluateThatListIsEmpty();
}

TEST_F(EmptyListTestSuite, ShouldNotChangeAnythingWhileTryingClearEmptyList) {
    sut.clear();
    EvaluateThatListIsEmpty();
}

TEST_F(EmptyListTestSuite, ShouldShowMaxElementCount) {
    ASSERT_EQ(sut.max_size(), MAX_ELEMENT_COUNT);
}

TEST_F(EmptyListTestSuite, ShouldShowThatListIsEmpty) {
    ASSERT_TRUE(sut.empty());
}

TEST_F(EmptyListTestSuite, ShouldShowNothingWhileTryingToAccessFirstElement) {
    ASSERT_EQ(sut.front(), NO_ELEMENT_EXPECTED);
}

TEST_F(EmptyListTestSuite, ShouldShowNothingWhenTryingToAccessLastElement) {
    ASSERT_EQ(sut.back(), NO_ELEMENT_EXPECTED);
}

TEST_F(EmptyListTestSuite, ShouldNotTakeAnyActionWhenTryingToPopBackLastElement) {
    sut.pop_back();

    EvaluateThatListIsEmpty();
}

TEST_F(EmptyListTestSuite, ShouldAddNewElementAtTheEndOfList) {
    ASSERT_EQ(sut.size(), EMPTY);

    sut.push_back(DEFAULT_VALUE);
    ASSERT_EQ(sut.size(), EMPTY + 1);

    ASSERT_EQ(sut, EXPECTED_LIST_WITH_ONE_ELEMET);
}

TEST_F(EmptyListTestSuite, ShouldShowSizeEqToZero) {
    EvaluateThatListIsEmpty();
}

} // namespace namespace containers::ut
