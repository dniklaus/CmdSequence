#ifndef TESTCMDTIMER_H
#define TESTCMDTIMER_H

#pragma once

//#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CmdSeqTimer.h"

class TestCmdSeqTimer : public CmdSeqTimer
{
public:
    TestCmdSeqTimer() { }
    virtual ~TestCmdSeqTimer() { }

    MOCK_METHOD(void, start, (uint32_t timeMicros), (override));
    MOCK_METHOD(void, cancel, (), (override));
    MOCK_METHOD(bool, isExpired, (), (const, override));
};

#endif