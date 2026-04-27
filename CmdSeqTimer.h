/**
 * @file CmdSeqTimer.h
 * @brief Interface for the Command Sequence Timer.
 *
 * Provides an abstract timer interface for command sequences, including
 * virtual function table and inline virtual calls.
 */

#ifndef __CmdSeqTimer_H
#define __CmdSeqTimer_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Command sequence timer Interface. 
 */
class CmdSeqTimer
{
public:
    static const int32_t T1ms;  /**< time constant: 1ms */
    static const int32_t T1s;   /**< time constant: 1s */

    explicit CmdSeqTimer() = default;
    virtual ~CmdSeqTimer() { }

    /**
     * @brief Start the timer
     * @param timeMicros Timeout in microseconds
     */
    virtual void start(uint32_t timeMicros) = 0;

    /**
     * @brief Cancel the timer
     */
    virtual void cancel() = 0;

    /**
     * @brief Check if the timer is expired
     * @return true if the timer is expired, false otherwise
     */
    virtual bool isExpired() const = 0;
};

#endif
