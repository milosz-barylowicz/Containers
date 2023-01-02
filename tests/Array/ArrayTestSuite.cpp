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
constexpr size_t EMPTY = 0;
const Array<int, EMPTY> EMPTY_ARRAY;
} // namespace anonymous

using namespace ::testing;
class ArrayTestSuite : public Test
{
public:
	Array<int, 0> sut;
};

TEST_F(ArrayTestSuite, ShouldCreateDefultArrayFilledWithZeros)
{
	Array<int, 2> result;
	ASSERT_EQ(0, result[0]);
	ASSERT_EQ(0, result[1]);
}

TEST_F(ArrayTestSuite, ShouldCreateEmptyArray)
{
	ASSERT_EQ(EMPTY, sut.size());
	ASSERT_EQ(EMPTY_ARRAY, sut);
}

TEST_F(ArrayTestSuite, ShouldCreateArrayFromEmelemntsList)
{
	Array<int, 5> result {1, 2 , 3, 4, 5};
	ASSERT_EQ(5, result.size());
}

} // namespace containers::ut
