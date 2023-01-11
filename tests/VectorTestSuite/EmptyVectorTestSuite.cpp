/*
 * Author: Milosz Barylowicz
 * Date:   2023
 */

#include <gtest/gtest.h>
#include "Vector.hpp"

namespace
{
constexpr int DEFAULT_VALUE = 100;
} // namespace anonymous

namespace containers::ut
{
using namespace ::testing;

class EmptyVectorTestSuite : public Test
{
public:
	Vector<int> sut;
};

TEST_F(EmptyVectorTestSuite, ShouldAddNewElement)
{
	sut.push_back(DEFAULT_VALUE);
	ASSERT_EQ(DEFAULT_VALUE, sut[0]);
}

} // namespace containers::ut
