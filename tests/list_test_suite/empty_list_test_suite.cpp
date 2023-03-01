#include <gtest/gtest.h>
#include "list.hpp"

namespace {

constexpr size_t EMPTY = 0;
constexpr int DEFAULT_VALUE = 100;

containers::List<int> BuildListWithOneElement()
{
	containers::List<int> result;
	result.push_back(DEFAULT_VALUE);

	return result;
}
} // namespace

namespace containers::ut {

using namespace ::testing;

class EmptyListTestSuite : public Test {
public:
	List<int> sut;
};

TEST_F(EmptyListTestSuite, ShouldAddNewElementToEmptyListWhenPushingItBack) {
	EXPECT_EQ(sut.size(), EMPTY);
	sut.push_back(DEFAULT_VALUE);

	ASSERT_EQ(sut.size(), EMPTY + 1);
	ASSERT_EQ(sut.back(), DEFAULT_VALUE);
	ASSERT_EQ(sut, BuildListWithOneElement());
}

TEST_F(EmptyListTestSuite, ShouldNotTakeAnyActionWhenTryingPopUpLastElement) {
	EXPECT_EQ(sut.size(), EMPTY);
	sut.pop_back();

	ASSERT_EQ(sut.size(), EMPTY);
}

} // namespace namespace containers::ut
