/*
 * Author: Milosz Barylowicz
 * Date:   2023
 */

#include <gtest/gtest.h>
#include "Vector.hpp"

namespace containers::ut
{
	using namespace ::testing;


class VectorTestSuite : public Test
{
public:
	Vector sut;
};

TEST_F(VectorTestSuite, TestingTest)
{}

} // namespace containers::ut
