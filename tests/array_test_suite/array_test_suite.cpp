#include <gtest/gtest.h>

#include "array.hpp"

namespace {

constexpr int DEFAULT_VALUE = 100;
constexpr size_t MAX_SIZE = std::numeric_limits<size_t>::max();
constexpr size_t EMPTY = 0;
constexpr size_t NON_EMPTY = 5;
constexpr int FIRST_ELEMENT = 1;
const containers::array<int, NON_EMPTY> NON_EMPTY_ARRAY{
    FIRST_ELEMENT, FIRST_ELEMENT + 1, FIRST_ELEMENT + 2, FIRST_ELEMENT + 3,
    FIRST_ELEMENT + 4};

void ExpectThatArrayWillBeFilledUpWithZeros(
    const containers::array<int, 2>& res) {
  for (size_t i = 0; i < 2; ++i) {
    ASSERT_EQ(EMPTY, res[i]);
  }
}

void ExpectThatArrayIsFilledCorrectly(const int* array, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    ASSERT_EQ(NON_EMPTY_ARRAY[i], *array);
    array++;
  }
}

void ExpectThatArrayIsFilledWithDefaultValue(
    const containers::array<int, 5>& array) {
  for (size_t i = 0; i < array.size(); ++i) {
    ASSERT_EQ(DEFAULT_VALUE, array[i]);
  }
}

}  // namespace

namespace containers::ut {

using namespace ::testing;

class ArrayTestSuite : public Test {
 public:
  array<int, NON_EMPTY> sut{FIRST_ELEMENT, FIRST_ELEMENT + 1, FIRST_ELEMENT + 2,
                            FIRST_ELEMENT + 3, FIRST_ELEMENT + 4};
};

TEST_F(ArrayTestSuite, ShouldAccessLastElementUsingConstEndIterator) {
  auto it = sut.cend();
  it--;
  ASSERT_EQ(FIRST_ELEMENT + 4, *it);
}

TEST_F(ArrayTestSuite, ShouldAccessLastElementUsingEndIterator) {
  auto it = sut.end();
  it--;
  ASSERT_EQ(FIRST_ELEMENT + 4, *it);
}

TEST_F(ArrayTestSuite, ShouldAccessFirstElementUsingConstBeginIterator) {
  auto it = sut.cbegin();
  ASSERT_EQ(FIRST_ELEMENT, *it);
}

TEST_F(ArrayTestSuite, ShouldAccessFirstElementUsingBeginIterator) {
  auto it = sut.begin();
  ASSERT_EQ(FIRST_ELEMENT, *it);

  it++;
  ASSERT_EQ(FIRST_ELEMENT + 1, *it);
}

TEST_F(ArrayTestSuite, ShouldSwapToArraysOfTheSameSize) {
  array<int, NON_EMPTY> result{FIRST_ELEMENT, FIRST_ELEMENT + 10,
                               FIRST_ELEMENT + 20, FIRST_ELEMENT + 30,
                               FIRST_ELEMENT + 40};
  sut.swap(result);

  ASSERT_EQ(FIRST_ELEMENT + 10, sut[1]);
  ASSERT_EQ(FIRST_ELEMENT + 1, result[1]);
}

TEST_F(ArrayTestSuite, ShouldAssingOneArrayToOtherOne) {
  array<int, NON_EMPTY> result{10, 20, 30, 40, 50};
  sut = result;
  ASSERT_EQ(result, sut);
}

TEST_F(ArrayTestSuite, ShouldFillUpArrayWithDefaultValue) {
  sut.fill(DEFAULT_VALUE);
  ExpectThatArrayIsFilledWithDefaultValue(sut);
}

TEST_F(ArrayTestSuite, ShouldGrandAccessToUnderlyingData) {
  ExpectThatArrayIsFilledCorrectly(sut.data(), sut.size());
}

TEST_F(ArrayTestSuite, ShouldReturnMaxPossibleSizeOfArray) {
  ASSERT_EQ(MAX_SIZE, sut.max_size());
}

TEST_F(ArrayTestSuite, ShouldAccessFirstElement) {
  ASSERT_EQ(FIRST_ELEMENT, sut.front());
}

TEST_F(ArrayTestSuite, ShouldAccessLastElement) {
  ASSERT_EQ(FIRST_ELEMENT + 4, sut.back());
}

TEST_F(ArrayTestSuite, ShouldModifySpecificElementOfArray) {
  auto value = sut[1];
  EXPECT_EQ(FIRST_ELEMENT + 1, value);

  value++;
  EXPECT_EQ(FIRST_ELEMENT + 2, value);
}

TEST_F(ArrayTestSuite, ShouldAccessSpecificElementOfArray) {
  EXPECT_EQ(FIRST_ELEMENT + 1, sut[1]);
}

TEST_F(ArrayTestSuite, ShouldModifySpecificElementOfArrayUsingAtMethod) {
  auto value = sut.at(1);
  EXPECT_EQ(FIRST_ELEMENT + 1, value);

  value++;
  EXPECT_EQ(FIRST_ELEMENT + 2, value);
}

TEST_F(ArrayTestSuite, ShouldAccessSpecificElementOfArrayUsingAtMethod) {
  EXPECT_EQ(FIRST_ELEMENT + 1, sut.at(1));
}

TEST_F(ArrayTestSuite, ShouldModifyFirstElementOfArray) {
  auto value = sut.front();
  EXPECT_EQ(FIRST_ELEMENT, value);

  value->get() = FIRST_ELEMENT + 1;
  ASSERT_EQ(FIRST_ELEMENT + 1, value);
}

TEST_F(ArrayTestSuite, ShouldModifyLastElementOfArray) {
  auto value = sut.back();
  EXPECT_EQ(FIRST_ELEMENT + 4, value);

  value->get() = FIRST_ELEMENT;
  ASSERT_EQ(FIRST_ELEMENT, value);
}

TEST_F(ArrayTestSuite, ShouldCreateNonEmptyArray) {
  ASSERT_FALSE(sut.empty());
  ASSERT_EQ(NON_EMPTY, sut.size());
  ASSERT_EQ(NON_EMPTY_ARRAY, sut);
}

TEST_F(ArrayTestSuite, ShouldCreateDefultArrayFilledWithZeros) {
  array<int, 2> result;
  ExpectThatArrayWillBeFilledUpWithZeros(result);
}

}  // namespace containers::ut
