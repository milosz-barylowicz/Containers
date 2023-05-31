#include <gtest/gtest.h>
#include "List.hpp"

namespace containers::ut {

using namespace ::testing;

class ListTestSuite : public Test {
public:
	List<int> sut;
};

TEST_F(ListTestSuite, EmptyTestSuite) {

}

} // namespace containers::ut
