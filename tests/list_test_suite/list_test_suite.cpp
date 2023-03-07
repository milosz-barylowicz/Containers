#include <gtest/gtest.h>
#include "list.hpp"

namespace {

constexpr int DEFAULT_VALUE = 123;
constexpr size_t SIZE = 1;

containers::List<int> BuildListWithOneAdditionalElemet() {
	containers::List<int> result;
	result.push_back(DEFAULT_VALUE);
	result.push_back(DEFAULT_VALUE + 1);

	return result;
}
} // namespace

namespace containers::ut {

using namespace ::testing;

class ListTestSuite : public Test {
public:
	ListTestSuite() {
		sut.push_back(DEFAULT_VALUE);
	}

	List<int> sut;
};

TEST_F(ListTestSuite, ShouldPopLastElementOfNonEmptyList) {
	auto result = BuildListWithOneAdditionalElemet();
	result.pop_back();

	ASSERT_EQ(result, sut);
}

TEST_F(ListTestSuite, ShouldAddNewElementToExistingList) {
	EXPECT_EQ(sut.size(), SIZE);
	sut.push_back(DEFAULT_VALUE + 1);

	ASSERT_EQ(sut.size(), SIZE + 1);
	ASSERT_EQ(sut.back(), DEFAULT_VALUE + 1);
	ASSERT_EQ(sut, BuildListWithOneAdditionalElemet());
}

} // namespace containers::ut
