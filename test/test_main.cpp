#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TestCmdSeqTimer.h"

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Cmd_Test, BasicTest)
{
    EXPECT_EQ(1, 1);
}

TEST(Cmd_Test, MockTest)
{
    TestCmdSeqTimer timer;
    EXPECT_CALL(timer, start(CmdSeqTimer::T1s)).Times(1);
    EXPECT_CALL(timer, cancel()).Times(1);
    EXPECT_CALL(timer, isExpired()).WillOnce(testing::Return(false));

    timer.start(CmdSeqTimer::T1s);
    timer.cancel();
    EXPECT_FALSE(timer.isExpired());
}