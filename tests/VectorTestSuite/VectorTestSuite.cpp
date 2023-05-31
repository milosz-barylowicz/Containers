#include <gtest/gtest.h>
#include "Vector.hpp"

namespace
{
constexpr int DEFAULT_VALUE = 100;
constexpr size_t DEFAULT_CAPACITY = 2;
const containers::Vector<int> reversed{DEFAULT_VALUE + 1, DEFAULT_VALUE};

containers::Vector<int> BuildDefaultFilledVecotr() {
    return { DEFAULT_VALUE, DEFAULT_VALUE + 1, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE };
}

} // namespace anonymous

namespace containers::ut {

using namespace ::testing;

class VectorTestSuite : public Test {
public:
    Vector<int> sut {DEFAULT_VALUE, DEFAULT_VALUE + 1};
};

TEST_F(VectorTestSuite, ShouldChangeSizeCapacityAndFillVectorWithPassedValueWhenResizing) {
    sut.resize(5, DEFAULT_VALUE);

    EXPECT_EQ(5, sut.size());
    EXPECT_EQ(5, sut.capacity());
    ASSERT_EQ(BuildDefaultFilledVecotr(), sut);
}

TEST_F(VectorTestSuite, ShouldChangeCapacityButDoNotChangeSizeWhenResizing) {
    Vector<int> expected{ DEFAULT_VALUE, DEFAULT_VALUE + 1, 0, 0, 0 };
    sut.resize(5);

    EXPECT_EQ(5, sut.size());
    EXPECT_EQ(5, sut.capacity());
    ASSERT_EQ(expected, sut);
}

TEST_F(VectorTestSuite, ShouldSwapWithNonEmptyVector) {
    Vector<int> res{ DEFAULT_VALUE, DEFAULT_VALUE + 1, DEFAULT_VALUE + 2 };
    sut.swap(res);

    ASSERT_EQ(3, sut.size());
}

TEST_F(VectorTestSuite, ShouldSwapWithEmptyVector) {
    Vector<int> empty;
    sut.swap(empty);
    Vector<int> res{ DEFAULT_VALUE, DEFAULT_VALUE + 1 };

    ASSERT_EQ(empty, res);
    ASSERT_TRUE(sut.empty());
}

TEST_F(VectorTestSuite, ShouldReplaceValuses) {
    sut.assing(7, DEFAULT_VALUE);

    ASSERT_FALSE(sut.empty());
    ASSERT_EQ(7, sut.size());
}

TEST_F(VectorTestSuite, ShouldReverseVectorsContent) {
    sut.reverse();
    ASSERT_EQ(reversed, sut);
}

TEST_F(VectorTestSuite, ShouldChangeCapacityOnlyToCurrentlyExistingElements) {
    sut.shrink_to_fit();
    ASSERT_EQ(sut.size(), sut.capacity());
}

TEST_F(VectorTestSuite, ShouldClearIt) {
    sut.clear();

    ASSERT_TRUE(sut.empty());
}

TEST_F(VectorTestSuite, ShouldAccessFirstElementAndCouldModifyItWhenCallingBack) {
    auto last = sut.back();
    ASSERT_EQ(DEFAULT_VALUE + 1, *last);

    *last += 2;
    ASSERT_EQ(DEFAULT_VALUE + 3, sut[1]);
}

TEST_F(VectorTestSuite, ShouldAccessFirstElementAndCouldModifyItWhenCallingFront) {
    auto first = sut.front();
    ASSERT_EQ(DEFAULT_VALUE, *first);

    *first += 2;
    ASSERT_EQ(DEFAULT_VALUE + 2, sut[0]);
}

TEST_F(VectorTestSuite, ShouldAccessEndWithIterator) {
    const auto end = sut.end();
    ASSERT_EQ(DEFAULT_VALUE + 1, *end);
}

TEST_F(VectorTestSuite, ShouldAccessBeginWithIterator) {
    const auto first = sut.begin();
    ASSERT_EQ(DEFAULT_VALUE, *first);
}

TEST_F(VectorTestSuite, ShouldEmplaceBackNewElement) {
    const auto size = sut.size();
    const auto value = DEFAULT_VALUE;
    sut.emplace_back(std::move(value + 5));
    ASSERT_EQ(size + 1, sut.size());
    ASSERT_EQ(DEFAULT_VALUE + 5, sut[size]);
}

TEST_F(VectorTestSuite, ShouldPopLastElementFormNonEmptyVector) {
    EXPECT_EQ(2, sut.size());
    sut.pop_back();

    ASSERT_EQ(1, sut.size());
    ASSERT_THROW(sut.at(1), std::out_of_range);
    ASSERT_EQ(sut.at(0), DEFAULT_VALUE);
}

TEST_F(VectorTestSuite, ShouldThrowWhenTryingToAccessOutOfRange) {
    ASSERT_THROW(sut.at(sut.size() + 1), std::out_of_range);
}

TEST_F(VectorTestSuite, ShouldAccessAndBeAbleToModyfiElementsInrange) {
    int& value = sut.at(1);
    ASSERT_EQ(value, DEFAULT_VALUE + 1);

    value++;
    ASSERT_EQ(sut.at(1), DEFAULT_VALUE + 2);
}

TEST_F(VectorTestSuite, ShouldCreateNonEmptyVector) {
    ASSERT_FALSE(sut.empty());
}

TEST_F(VectorTestSuite, ShouldIncreaseCapacityWhenThereArevectorResizeInvoked) {
    for (size_t i = 0; i < DEFAULT_CAPACITY; ++i) {
        sut.push_back(DEFAULT_VALUE);
    }

    ASSERT_EQ(DEFAULT_CAPACITY * 10, sut.capacity());
}

TEST_F(VectorTestSuite, ShouldCreateVectorWithDefaultCapacity) {
    ASSERT_EQ(DEFAULT_CAPACITY, sut.capacity());
}

TEST_F(VectorTestSuite, ShouldModifyElementUsingAccessOperator) {
    sut[1]++;
    ASSERT_EQ(DEFAULT_VALUE + 2, sut[1]);
}

TEST_F(VectorTestSuite, ShouldAssingNonEmptyVectorWithDifferentSize) {
    Vector<int> result {DEFAULT_VALUE + 10, DEFAULT_VALUE + 20, DEFAULT_VALUE + 30};

    sut = result;

    ASSERT_EQ(result.size(), sut.size());
    ASSERT_EQ(result, sut);
}

TEST_F(VectorTestSuite, ShouldAssignTwoVectorsWithTheSameSizeButDifferentValues) {
    Vector<int> result {DEFAULT_VALUE + 10, DEFAULT_VALUE + 20};

    sut = result;

    ASSERT_EQ(result, sut);
}

TEST_F(VectorTestSuite, ShouldAddNewElement) {
    sut.push_back(DEFAULT_VALUE + 2);
    ASSERT_EQ(DEFAULT_VALUE + 2, sut[2]);
}

TEST(VectorTest, ShouldCreateMoreThen10ElementsInVector) {
    Vector<int> sut {DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE,
        DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE + 1};
    ASSERT_EQ(12, sut.size());
    ASSERT_EQ(DEFAULT_VALUE + 1, sut[11]);
}

} // namespace containers::ut
