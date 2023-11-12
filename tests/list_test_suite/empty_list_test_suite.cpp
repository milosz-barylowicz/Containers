#include "list.hpp"
#include <gtest/gtest.h>

namespace {

constexpr containers::list<int>::size_type EMPTY = 0;
constexpr int DEFAULT_VALUE = 57;
constexpr auto NO_ELEMENT_EXPECTED = std::nullopt;
constexpr containers::list<int>::size_type MAX_ELEMENT_COUNT =
    std::numeric_limits<size_t>::max();
constexpr containers::list<int>::iterator NON_EXISTING_ELEMENT = nullptr;
constexpr containers::list<int>::size_type SIZE = 5;

containers::list<int> BuildListFilledWithZerosWithGivenSize(
    containers::list<int>::size_type size, int value = 0) {
  containers::list<int> result;
  for (containers::list<int>::size_type i = 0; i < size; ++i) {
    result.push_back(value);
  }

  return result;
}

containers::list<int> BuildExpectedNonEmptyListWithSingleElement() {
  containers::list<int> result;
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

containers::list<int> BuildListWithElementsStartingWith(
    containers::list<int>::value_type value,
    containers::list<int>::size_type count) {
  containers::list<int> result;
  for (containers::list<int>::size_type i = 0; i < count; ++i) {
    result.push_back(value + i);
  }

  return result;
}

containers::list<int> EXPECTED_LIST_WITH_ONE_ELEMET =
    BuildExpectedNonEmptyListWithSingleElement();
containers::list<int> EXPECTED_EMPTY_LIST;

}  // namespace

namespace containers::ut {

using namespace ::testing;

class EmptyListTestSuite : public Test {
 public:
  void EvaluateList(list<int>::size_type size = EMPTY,
                    const list<int>& expected = EXPECTED_EMPTY_LIST) {
    ASSERT_EQ(sut, expected);
    ASSERT_EQ(sut.size(), size);
  }

  list<int> sut;
};

TEST_F(EmptyListTestSuite, ShouldSwapWithNonEmptyList) {
  list<int> other = BuildExpectedNonEmptyListWithSingleElement();
  sut.swap(other);

  ASSERT_EQ(sut, EXPECTED_LIST_WITH_ONE_ELEMET);
  ASSERT_EQ(other, EXPECTED_EMPTY_LIST);
}

TEST_F(EmptyListTestSuite, ShouldSwapContentWithEmptyList) {
  list<int> other;
  sut.swap(other);

  ASSERT_EQ(sut, EXPECTED_EMPTY_LIST);
  ASSERT_EQ(other, EXPECTED_EMPTY_LIST);
}

TEST_F(EmptyListTestSuite, ShouldResizeAndFillWithDefinedvalue) {
  sut.resize(SIZE, DEFAULT_VALUE - 10);
  ASSERT_EQ(sut,
            BuildListFilledWithZerosWithGivenSize(SIZE, DEFAULT_VALUE - 10));
}

TEST_F(EmptyListTestSuite, ShouldResizeAndFillWithZeros) {
  sut.resize(SIZE);
  ASSERT_EQ(sut, BuildListFilledWithZerosWithGivenSize(SIZE));
}

TEST_F(EmptyListTestSuite, ShouldNotReturnConstIteratorToLastElement) {
  ASSERT_EQ(sut.cend(), NON_EXISTING_ELEMENT);
}

TEST_F(EmptyListTestSuite, ShouldNotReturnIteratorToLastElement) {
  ASSERT_EQ(sut.end(), NON_EXISTING_ELEMENT);
}

TEST_F(EmptyListTestSuite, ShouldNotReturnConstIteratorToFirstElement) {
  ASSERT_EQ(sut.cbegin(), NON_EXISTING_ELEMENT);
}

TEST_F(EmptyListTestSuite, ShouldNotReturnIteratorToFirstElement) {
  ASSERT_EQ(sut.begin(), NON_EXISTING_ELEMENT);
}

TEST_F(EmptyListTestSuite, ShouldAssignNewListUsingInitList) {
  sut.assign({DEFAULT_VALUE, DEFAULT_VALUE + 1, DEFAULT_VALUE + 2,
              DEFAULT_VALUE + 3, DEFAULT_VALUE + 4});
  ASSERT_EQ(sut, BuildListWithElementsStartingWith(DEFAULT_VALUE, 5));
}

TEST_F(EmptyListTestSuite, ShouldAddnewElementToFronOfList) {
  sut.push_front(DEFAULT_VALUE);
  EvaluateList(1, EXPECTED_LIST_WITH_ONE_ELEMET);
}

TEST_F(EmptyListTestSuite, ShouldAssignGivenValueGivenTimes) {
  sut.assign(5, DEFAULT_VALUE);
  ASSERT_EQ(sut, BuildListWithValueAndSize(5, DEFAULT_VALUE));
}

TEST_F(EmptyListTestSuite,
       ShouldDoNotChangeAnythingWhenTryingToPopFrontElement) {
  sut.pop_front();
  EvaluateList();
}

TEST_F(EmptyListTestSuite, ShouldNotChangeAnythingWhileTryingClearEmptyList) {
  sut.clear();
  EvaluateList();
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

TEST_F(EmptyListTestSuite,
       ShouldNotTakeAnyActionWhenTryingToPopBackLastElement) {
  sut.pop_back();

  EvaluateList();
}

TEST_F(EmptyListTestSuite, ShouldAddNewElementAtTheEndOfList) {
  ASSERT_EQ(sut.size(), EMPTY);

  sut.push_back(DEFAULT_VALUE);
  ASSERT_EQ(sut.size(), EMPTY + 1);

  ASSERT_EQ(sut, EXPECTED_LIST_WITH_ONE_ELEMET);
}

TEST_F(EmptyListTestSuite, ShouldShowSizeEqToZero) { EvaluateList(); }

}  // namespace containers::ut
