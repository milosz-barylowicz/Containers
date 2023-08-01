#include <gtest/gtest.h>
#include "list.hpp"

namespace {

constexpr containers::list<int>::size_type EMPTY = 0;
constexpr int DEFAULT_VALUE = 123;
constexpr containers::list<int>::size_type SIZE = 10;
constexpr containers::list<int>::size_type MAX_ELEMENT_COUNT = std::numeric_limits<size_t>::max();

containers::list<int> BuildNonEmptyList() {
    containers::list<int> result;
    for (size_t i = 0; i < SIZE; ++i) {
        result.push_back(DEFAULT_VALUE + i);
    }

    return result;
}

containers::list<int> BuildExpectedList() {
    containers::list<int> result = BuildNonEmptyList();
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

containers::list<int> EXPECTED = BuildExpectedList();
containers::list<int> EXPECTED_EMPTY_LIST;

} // namespace

namespace containers::ut {

using namespace ::testing;

class ListTestSuite : public Test {
public:
    void SetUp() override {
        sut = BuildNonEmptyList();
    }

    void EvaluateLastElementOfList(int value) const {
        ASSERT_EQ(sut.back(), value);
    }

    void EvaluateFirstElementOfList(int value) const {
        ASSERT_EQ(*sut.front(), value);
    }

    list<int> sut;
};

TEST_F(ListTestSuite, ShouldReplaceOldListWithNewOneWhenAssigning) {
    sut.assign(5, DEFAULT_VALUE);
    ASSERT_EQ(sut, BuildListWithValueAndSize(5, DEFAULT_VALUE));
}

TEST_F(ListTestSuite, ShouldRemoveFrstElementOfList) {
    sut.pop_front();

    ASSERT_EQ(sut.size(), SIZE - 1);
    EvaluateFirstElementOfList(DEFAULT_VALUE + 1);
}

TEST_F(ListTestSuite, ShouldClearNonEmptyList) {
    sut.clear();

    ASSERT_EQ(sut.size(), EMPTY);
    ASSERT_EQ(sut, EXPECTED_EMPTY_LIST);
}

TEST_F(ListTestSuite, ShouldShowMaxElementCount) {
    ASSERT_EQ(sut.max_size(), MAX_ELEMENT_COUNT);
}

TEST_F(ListTestSuite, ShouldShowThatListIsNonEmpty) {
    ASSERT_FALSE(sut.empty());
}

TEST_F(ListTestSuite, ShouldAccessFirstElementOfList) {
    ASSERT_EQ(sut.front(), DEFAULT_VALUE);
}

TEST_F(ListTestSuite, ShouldAccessLastElementOfList) {
    EvaluateLastElementOfList(DEFAULT_VALUE + (SIZE - 1));
}

TEST_F(ListTestSuite, ShouldRemoveLastElementOfList) {
    sut.pop_back();

    ASSERT_EQ(sut.size(), SIZE - 1);
    EvaluateLastElementOfList(DEFAULT_VALUE + (SIZE - 2));
}

TEST_F(ListTestSuite, ShouldAddNewElementAtTheEndOfList) {
    ASSERT_EQ(sut.size(), SIZE);

    sut.push_back(DEFAULT_VALUE);
    ASSERT_EQ(sut.size(), SIZE + 1);

    ASSERT_EQ(sut, EXPECTED);
}

TEST_F(ListTestSuite, ShouldSizeNotBeEqInNonEmptyList) {
    ASSERT_NE(sut.size(), EMPTY);
}

} // namespace containers::ut
