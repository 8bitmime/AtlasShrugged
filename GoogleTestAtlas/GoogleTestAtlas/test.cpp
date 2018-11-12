#include "pch.h"
#include "../../AtlasPrototype/AtlasPrototype/Header1.h"
TEST(MyFirstTestCase, MyFirstTest) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
  doNothing();
  EXPECT_EQ(returnSeven(), 7);
  EXPECT_EQ(returnEight(), 8);
  EXPECT_NE(returnSeven(), 8);
}

TEST(MyFirstTestCase, MySecondTest) {
	EXPECT_EQ(1, 1);
	doNothing();
	EXPECT_NE(returnEight(), returnSeven());
}


class ActionObjectTest : public ::testing::Test {
	protected:
		void SetUp() {
			ao1.minSuccess = 5;
		}

		ActionObject ao1;
};

TEST_F(ActionObjectTest, MinLoops) {
	EXPECT_EQ(ao1.minSuccess, 5);
}
