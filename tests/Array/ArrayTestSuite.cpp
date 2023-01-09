/*
 * Author: Milosz Barylowicz
 * Date:   2022-2023
 */

#include <gtest/gtest.h>
#include "Array.hpp"

namespace containers::ut
{

namespace
{
constexpr size_t MAX_SIZE = std::numeric_limits<size_t>::max();
constexpr size_t EMPTY = 0;
constexpr size_t NON_EMPTY = 5;
const Array<int, EMPTY> EMPTY_ARRAY;
constexpr int FIRST_ELEMENT = 1;
const Array<int, NON_EMPTY> NON_EMPTY_ARRAY
	{ FIRST_ELEMENT, FIRST_ELEMENT + 1, FIRST_ELEMENT + 2, FIRST_ELEMENT + 3, FIRST_ELEMENT + 4 };

void ExpectThatArrayWillBeFilledUpWithZeros(const Array<int, 2>& res)
{
	for (size_t i = 0; i < 2; ++i)
	{
		ASSERT_EQ(EMPTY, res[i]);
	}
}
} // namespace anonymous

using namespace ::testing;

class EmptyArrayTestSuite : public Test
{
public:
	Array<int, EMPTY> sut;
};

TEST_F(EmptyArrayTestSuite, ShouldReturnMaxPossibleSizeOfArray)
{
	ASSERT_EQ(MAX_SIZE, sut.max_size());
}

TEST_F(EmptyArrayTestSuite, ShouldThrowWhenTryingToAccessNonExistingElement)
{
	ASSERT_THROW(sut.at(0), std::out_of_range);
}

TEST_F(EmptyArrayTestSuite, ShouldCreateEmptyArray)
{
	ASSERT_TRUE(EMPTY_ARRAY.empty());
	ASSERT_EQ(EMPTY, sut.size());
	ASSERT_EQ(EMPTY_ARRAY, sut);
}

TEST_F(EmptyArrayTestSuite, ShouldThrowOutOfRangeExeptionWhenTryingToAccessFrontElementOfArray)
{
	ASSERT_THROW(sut.front(), std::out_of_range);
}

class ArrayTestSuite : public Test
{
public:
	Array<int, NON_EMPTY> sut
		{ FIRST_ELEMENT, FIRST_ELEMENT + 1, FIRST_ELEMENT + 2, FIRST_ELEMENT + 3, FIRST_ELEMENT + 4 };
};

TEST_F(ArrayTestSuite, ShouldReturnMaxPossibleSizeOfArray)
{
	ASSERT_EQ(MAX_SIZE, sut.max_size());
}

TEST_F(ArrayTestSuite, ShouldAccessFirstElement)
{
	ASSERT_EQ(FIRST_ELEMENT, sut.front());
}

TEST_F(ArrayTestSuite, ShouldModifySpecificElementOfArray)
{
	auto value = sut[1];
	EXPECT_EQ(FIRST_ELEMENT + 1, value);

	value++;
	EXPECT_EQ(FIRST_ELEMENT + 2, value);
}

TEST_F(ArrayTestSuite, ShouldAccessSpecificElementOfArray)
{
	EXPECT_EQ(FIRST_ELEMENT + 1, sut[1]);
}

TEST_F(ArrayTestSuite, ShouldModifySpecificElementOfArrayUsingAtMethod)
{
	auto value = sut.at(1);
	EXPECT_EQ(FIRST_ELEMENT + 1, value);

	value++;
	EXPECT_EQ(FIRST_ELEMENT + 2, value);
}

TEST_F(ArrayTestSuite, ShouldAccessSpecificElementOfArrayUsingAtMethod)
{
	EXPECT_EQ(FIRST_ELEMENT + 1, sut.at(1));
}

TEST_F(ArrayTestSuite, ShouldModifyFirstElementOfArray)
{
	auto value = sut.front();
	EXPECT_EQ(FIRST_ELEMENT, value);
	
	value->get() = FIRST_ELEMENT + 1;
	ASSERT_EQ(FIRST_ELEMENT + 1, value);
}

TEST_F(ArrayTestSuite, ShouldCreateNonEmptyArray)
{
	ASSERT_FALSE(sut.empty());
	ASSERT_EQ(NON_EMPTY, sut.size());
	ASSERT_EQ(NON_EMPTY_ARRAY, sut);
}

TEST_F(ArrayTestSuite, ShouldCreateDefultArrayFilledWithZeros)
{
	Array<int, 2> result;
	ExpectThatArrayWillBeFilledUpWithZeros(result);
}

} // namespace containers::ut
