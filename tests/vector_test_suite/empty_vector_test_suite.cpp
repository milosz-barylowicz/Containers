#include "vector.hpp"
#include <gtest/gtest.h>

namespace {

constexpr int DEFAULT_VALUE = 100;
constexpr size_t DEFAULT_CAPACITY = 10;

const containers::Vector<int> NON_EMPTY_VECTOR{1, 2, 3, 4, 5};
const containers::Vector<int> FILLED_WITH_ZEROS{0, 0, 0, 0, 0};

containers::Vector<int> BuildDefaultFilledVector() {
  return {DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE,
          DEFAULT_VALUE};
}

}  // namespace

namespace containers::ut {

using namespace ::testing;

class EmptyVectorTestSuite : public Test {
 public:
  Vector<int> sut;
};

TEST_F(EmptyVectorTestSuite,
       ShouldChangeCapacitySizeAndFillVectorWithPassedValue) {
  sut.resize(5, DEFAULT_VALUE);

  EXPECT_EQ(5, sut.size());
  EXPECT_EQ(5, sut.capacity());
  ASSERT_EQ(BuildDefaultFilledVector(), sut);
}

TEST_F(EmptyVectorTestSuite,
       ShouldChangeCapacityButDoNotChangeSizeWhenResizing) {
  sut.resize(5);

  EXPECT_EQ(5, sut.size());
  EXPECT_EQ(5, sut.capacity());
  ASSERT_EQ(FILLED_WITH_ZEROS, sut);
}

TEST_F(EmptyVectorTestSuite, ShouldSwapWithNonEmptyVector) {
  Vector<int> other{1, 2, 3, 4, 5};
  sut.swap(other);

  EXPECT_FALSE(sut.empty());
  ASSERT_EQ(sut, NON_EMPTY_VECTOR);
}

TEST_F(EmptyVectorTestSuite, ShouldSwapWithEmptyVector) {
  Vector<int> other;
  sut.swap(other);
  ASSERT_EQ(sut, other);
}

TEST_F(EmptyVectorTestSuite, ShouldFillEmptyVector) {
  sut.assing(7, DEFAULT_VALUE);

  ASSERT_FALSE(sut.empty());
  ASSERT_EQ(7, sut.size());
}

TEST_F(EmptyVectorTestSuite, ShouldNotReverse) {
  sut.reverse();
  ASSERT_TRUE(sut.empty());
}

TEST_F(EmptyVectorTestSuite,
       ShouldChangeCapacityOnlyToCurrentlyExistingElements) {
  sut.shrink_to_fit();
  ASSERT_EQ(sut.size(), sut.capacity());
}

TEST_F(EmptyVectorTestSuite, ShouldStayEmptyWhenCleared) {
  sut.clear();
  ASSERT_TRUE(sut.empty());
}

TEST_F(EmptyVectorTestSuite, ShouldNotAccessBackElement) {
  ASSERT_EQ(std::nullopt, sut.back());
}

TEST_F(EmptyVectorTestSuite, ShouldNotAccessFrontElement) {
  ASSERT_EQ(std::nullopt, sut.front());
}

TEST_F(EmptyVectorTestSuite, ShouldReturnEmptyPtrWhenAccessingEndOfData) {
  ASSERT_EQ(nullptr, sut.end());
}

TEST_F(EmptyVectorTestSuite, ShouldReturnEmptyPtrWhenAccessingBeginOfData) {
  ASSERT_EQ(nullptr, sut.begin());
}

TEST_F(EmptyVectorTestSuite, ShouldEmplaceBackNewElement) {
  sut.emplace_back(std::move(DEFAULT_VALUE));

  ASSERT_EQ(1, sut.size());
  ASSERT_EQ(DEFAULT_VALUE, sut[0]);
}

TEST_F(EmptyVectorTestSuite, ShouldNotPopElemetns) {
  EXPECT_TRUE(sut.empty());
  sut.pop_back();
  ASSERT_TRUE(sut.empty());
}

TEST_F(EmptyVectorTestSuite, ShouldThrowWhenAccessingElements) {
  ASSERT_THROW(sut.at(0), std::out_of_range);
  ASSERT_THROW(sut.at(10), std::out_of_range);
}

TEST_F(EmptyVectorTestSuite, ShouldCreateEmptyVector) {
  ASSERT_TRUE(sut.empty());
}

TEST_F(EmptyVectorTestSuite, ShouldCreateEmptyVectorWIthDefaultCapacity) {
  ASSERT_EQ(DEFAULT_CAPACITY, sut.capacity());
}

TEST_F(EmptyVectorTestSuite,
       ShouldPushBackNewElementsEvenWhenBasicCapacityWillBeCrossed) {
  for (size_t i = 0; i < DEFAULT_CAPACITY + 2; ++i) {
    sut.push_back(DEFAULT_VALUE);
  }

  ASSERT_EQ(DEFAULT_CAPACITY + 2, sut.size());
}

TEST_F(EmptyVectorTestSuite, ShouldAssingNonEmptyVector) {
  sut = NON_EMPTY_VECTOR;

  ASSERT_EQ(NON_EMPTY_VECTOR.size(), sut.size());
  ASSERT_EQ(NON_EMPTY_VECTOR, sut);
}

TEST_F(EmptyVectorTestSuite, ShouldAddNewElement) {
  sut.push_back(DEFAULT_VALUE);
  ASSERT_EQ(DEFAULT_VALUE, sut[0]);
}

TEST(EmptyVectorTester, ShouldCreateNewVectorFromExistingOne) {
  Vector<int> sut(NON_EMPTY_VECTOR);

  ASSERT_EQ(NON_EMPTY_VECTOR.size(), sut.size());
  ASSERT_EQ(NON_EMPTY_VECTOR, sut);
}

TEST(EmptyVectorTester, ShouldCreateNewVectorFromMovedOne) {
  auto result = NON_EMPTY_VECTOR;
  Vector<int> sut(std::move(NON_EMPTY_VECTOR));

  ASSERT_EQ(result.size(), sut.size());
  ASSERT_EQ(result, sut);
}

}  // namespace containers::ut
