#ifndef TESTCMDTIMER_H
#define TESTCMDTIMER_H

#pragma once

#include "CmdSeqTimer.h"

class TestCmdSeqTimer : public CmdSeqTimer
{
public:
    TestCmdSeqTimer() { }
    virtual ~TestCmdSeqTimer() { }

    void start(uint32_t timeMicros) override;
    void cancel() override;
    bool isExpired() const override;
};

#endif