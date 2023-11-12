#include <gtest/gtest.h>

#include "list.hpp"

namespace {

constexpr containers::list<int>::size_type EMPTY = 0;
constexpr int DEFAULT_VALUE = 123;
constexpr containers::list<int>::size_type SIZE = 10;
constexpr containers::list<int>::size_type MAX_ELEMENT_COUNT =
    std::numeric_limits<size_t>::max();

containers::list<int> BuildNonEmptyList(
    containers::list<int>::size_type size = SIZE) {
  containers::list<int> result;
  for (size_t i = 0; i < size; ++i) {
    result.push_back(DEFAULT_VALUE + i);
  }

  return result;
}

containers::list<int> BuildExpectedList() {
  containers::list<int> result = BuildNonEmptyList();
  result.push_back(DEFAULT_VALUE);

  return result;
}

containers::list<int> BuildListWithValueAndSize(
    containers::list<int>::size_type count,
    containers::list<int>::value_type value) {
  containers::list<int> result;
  for (containers::list<int>::size_type i = 0; i < count; ++i) {
    result.push_back(value);
  }

  return result;
}

containers::list<int> EXPECTED = BuildExpectedList();
containers::list<int> EXPECTED_EMPTY_LIST;

}  // namespace

namespace containers::ut {

using namespace ::testing;

class ListTestSuite : public Test {
 public:
  void SetUp() override { sut = BuildNonEmptyList(); }

  void EvaluateLastElementOfList(int value) const {
    ASSERT_EQ(sut.back(), value);
  }

  void EvaluateFirstElementOfList(int value) const {
    ASSERT_EQ(*sut.front(), value);
  }

  list<int> sut;
};

TEST_F(ListTestSuite, ShouldSwapWithListWithDifferentSize) {
  list<int> other = BuildListWithValueAndSize(SIZE + 1, DEFAULT_VALUE + 123);
  sut.swap(other);

  ASSERT_EQ(sut, BuildListWithValueAndSize(SIZE + 1, DEFAULT_VALUE + 123));
  ASSERT_EQ(other, BuildNonEmptyList());
}

TEST_F(ListTestSuite, ShouldSwapWithNonEmptyListWithSameSize) {
  list<int> other = BuildListWithValueAndSize(SIZE, DEFAULT_VALUE + 123);
  sut.swap(other);

  ASSERT_EQ(sut, BuildListWithValueAndSize(SIZE, DEFAULT_VALUE + 123));
  ASSERT_EQ(other, BuildNonEmptyList());
}

TEST_F(ListTestSuite, ShouldSwapWithEmptyList) {
  list<int> other;
  sut.swap(other);

  ASSERT_EQ(sut, EXPECTED_EMPTY_LIST);
  ASSERT_EQ(other, BuildNonEmptyList());
}

TEST_F(
    ListTestSuite,
    ShouldResizeWhenCountIsLesserThenListSizeAndDefinedValueAndJustCutAdditionalValues) {
  sut.resize(SIZE - 1, DEFAULT_VALUE + 100);
  ASSERT_EQ(sut, BuildNonEmptyList(SIZE - 1));
}

TEST_F(ListTestSuite,
       ShouldNotResizeListIfSizeAndNewSizeIsTheSameAndDefinedValue) {
  sut.resize(SIZE, DEFAULT_VALUE);
  ASSERT_EQ(sut, BuildNonEmptyList());
}

TEST_F(ListTestSuite, ShouldResizeListWithMoreElementsAndDefinedValue) {
  sut.resize(SIZE + 1, DEFAULT_VALUE + 10);
  auto EXPECTED_RESIZED_LIST = BuildNonEmptyList();
  EXPECTED_RESIZED_LIST.push_back(DEFAULT_VALUE + 10);

  ASSERT_EQ(sut, EXPECTED_RESIZED_LIST);
}

TEST_F(ListTestSuite,
       ShouldResizeWhenCountIsLesserThenListSizeAndJustCutAdditionalValues) {
  sut.resize(SIZE - 1);
  ASSERT_EQ(sut, BuildNonEmptyList(SIZE - 1));
}

TEST_F(ListTestSuite, ShouldNotResizeListIfSizeAndNewSizeIsTheSame) {
  sut.resize(SIZE);
  ASSERT_EQ(sut, BuildNonEmptyList());
}

TEST_F(ListTestSuite, ShouldResizeListWithMoreElementsAndValueZero) {
  sut.resize(SIZE + 1);
  auto EXPECTED_RESIZED_LIST = BuildNonEmptyList();
  EXPECTED_RESIZED_LIST.push_back(0);

  ASSERT_EQ(sut, EXPECTED_RESIZED_LIST);
}

TEST_F(ListTestSuite, ShouldAccessLastElement) {
  auto last = sut.cend();
  ASSERT_EQ(last->data, DEFAULT_VALUE + (SIZE - 1));
}

TEST_F(ListTestSuite, ShouldAccessAndGivePossibilityToModifyLastElement) {
  auto last = sut.end();
  ASSERT_EQ(last->data, DEFAULT_VALUE + (SIZE - 1));

  last->data += 100;
  ASSERT_EQ(sut.back(), DEFAULT_VALUE + (SIZE - 1) + 100);
}

TEST_F(ListTestSuite, ShouldAccessFirstElement) {
  auto first = sut.cbegin();
  ASSERT_EQ(first->data, DEFAULT_VALUE);
}

TEST_F(ListTestSuite, ShouldAccessAndGivePossibilityToModifyFirstElement) {
  auto first = sut.begin();
  ASSERT_EQ(first->data, DEFAULT_VALUE);

  first->data += 100;
  ASSERT_EQ(sut.front(), DEFAULT_VALUE + 100);
}

TEST_F(ListTestSuite, ShouldAssignNewListUsingInitList) {
  sut.assign({DEFAULT_VALUE, DEFAULT_VALUE + 1, DEFAULT_VALUE + 2,
              DEFAULT_VALUE + 3, DEFAULT_VALUE + 4});
  ASSERT_EQ(sut, BuildNonEmptyList(5));
}

TEST_F(ListTestSuite, ShouldAddElemnetInFrontOfList) {
  sut.push_front(DEFAULT_VALUE + 100);

  ASSERT_EQ(sut.size(), SIZE + 1);
  EvaluateFirstElementOfList(DEFAULT_VALUE + 100);
}

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

}  // namespace containers::ut
