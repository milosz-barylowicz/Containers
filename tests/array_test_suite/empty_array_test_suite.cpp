#include <gtest/gtest.h>

#include "array.hpp"

namespace {

constexpr int DEFAULT_VALUE = 100;
constexpr size_t EMPTY = 0;
const containers::array<int, EMPTY> EMPTY_ARRAY;
constexpr size_t MAX_SIZE = std::numeric_limits<size_t>::max();

}  // namespace

namespace containers::ut {

using namespace ::testing;

class EmptyArrayTestSuite : public Test {
 public:
  array<int, EMPTY> sut;
};

TEST_F(EmptyArrayTestSuite, ShouldSwapTwoEmptyArrays) {
  array<int, EMPTY> result;
  sut.swap(result);

  ASSERT_EQ(EMPTY, sut.size());
  ASSERT_EQ(EMPTY, result.size());
}

TEST_F(EmptyArrayTestSuite, ShouldReturnMaxPossibleSizeOfArray) {
  ASSERT_EQ(MAX_SIZE, sut.max_size());
}

TEST_F(EmptyArrayTestSuite, ShouldThrowWhenTryingToAccessNonExistingElement) {
  ASSERT_THROW(sut.at(0), std::out_of_range);
}

TEST_F(EmptyArrayTestSuite, ShouldCreateEmptyArray) {
  ASSERT_TRUE(EMPTY_ARRAY.empty());
  ASSERT_EQ(EMPTY, sut.size());
  ASSERT_EQ(EMPTY_ARRAY, sut);
}

TEST_F(EmptyArrayTestSuite,
       ShouldThrowOutOfRangeExeptionWhenTryingToAccessFrontElementOfArray) {
  ASSERT_THROW(sut.front(), std::out_of_range);
}

TEST_F(EmptyArrayTestSuite, ShouldThrowWhenTryingAccessLastElement) {
  ASSERT_THROW(sut.back(), std::out_of_range);
}

TEST_F(EmptyArrayTestSuite,
       ShouldReturnNullPointerWhenTryingAccessUnderlyingData) {
  ASSERT_FALSE(sut.data());
}

TEST_F(EmptyArrayTestSuite, ShouldNotFillEmptyArray) {
  sut.fill(DEFAULT_VALUE);
  ASSERT_EQ(EMPTY_ARRAY, sut);
}

}  // namespace containers::ut
