#include <gtest/gtest.h>


TEST(MyLibTest, AddTest)
{
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-1, 1), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}