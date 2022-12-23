/*
 * Author: Milosz Barylowicz
 * Date:   2022
 */

#include <gtest/gtest.h>
#include "Array.hpp"

namespace containers::ut
{

namespace
{
constexpr size_t EMPTY = 0;
} // namespace anonymous

using namespace ::testing;
class ArrayTestSuite : public Test
{
public:
	Array<int, 0> sut;
};

TEST_F(ArrayTestSuite, ShouldCreateEmptyArray)
{
	ASSERT_EQ(EMPTY, sut.size());
}

} // namespace containers::ut
