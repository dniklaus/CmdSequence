/*
 * CmdSequence.cpp
 *
 *  Created on: 10.03.2014
 *      Author: niklausd
 */

#include "Timer.h"
#include "CmdAdapter.h"
#include "CmdSequence.h"
#include "Cmd.h"

//-----------------------------------------------------------------------------

class CmdSeqTimerAdapter : public TimerAdapter
{
public:
  CmdSeqTimerAdapter(CmdSequence* cmdSeq)
  : m_cmdSeq(cmdSeq)
  { }

  void timeExpired()
  {
    if (0 != m_cmdSeq)
    {
      m_cmdSeq->execNextCmd();
    }
  }

private:
  CmdSequence* m_cmdSeq;
};

//-----------------------------------------------------------------------------

CmdSequence::CmdSequence(CmdAdapter* adapter)
: m_isRunning(false)
, m_firstCmd(0)
, m_currentCmd(0)
, m_cmdListIter(0)
, m_adapter(adapter)
, m_timer(new Timer(new CmdSeqTimerAdapter(this), Timer::IS_NON_RECURRING))
{ }

CmdSequence::~CmdSequence()
{
  delete m_timer->adapter();
  m_timer->attachAdapter(0);

  delete m_timer;
  m_timer = 0;
}

void CmdSequence::attachAdapter(CmdAdapter* adapter)
{
  m_adapter = adapter;
}

void CmdSequence::start()
{
  if (!isRunning())
  {
    m_currentCmd = m_firstCmd;
    execCmd();
  }
}

void CmdSequence::stop()
{
  m_timer->cancelTimer();
  if (0 != adapter())
  {
    adapter()->stopAction();
  }
  m_isRunning = false;
}

bool CmdSequence::isRunning()
{
  return m_isRunning;
}

Cmd* CmdSequence::currentCmd()
{
  return m_currentCmd;
}

void CmdSequence::execNextCmd()
{
  m_currentCmd->leave();  // leave the current command
  m_currentCmd = m_currentCmd->next(); // proceed to the next command
  execCmd();
}

void CmdSequence::execCmd()
{
  if ((0 != m_currentCmd) && (0 != m_timer))
  {
    m_isRunning = true;
    if (m_currentCmd->getTime() >= 0)
    {
      // time = 0: do not wait, immediately proceed to the next command of the sequence since the timer will expire immediately
      // time > 0: wait in this command the specified time [ms]
      unsigned long int currentCmdTime = static_cast<unsigned long int>(m_currentCmd->getTime());

      m_timer->startTimer(currentCmdTime);
    }
    // else
    // {
    //   // time < 0: wait forever in this command, since the timer is not started,
    //   //           which would make the sequence proceed to the next command when expired.
    // }
    m_currentCmd->execute();
  }
  else
  {
    m_isRunning = false;
    if (0 != m_timer)
    {
      m_timer->cancelTimer();
    }
    m_currentCmd = m_firstCmd;
  }
}

void CmdSequence::attach(Cmd* cmd)
{
  cmd->assign(this);
  if (0 == m_firstCmd)
  {
    m_firstCmd = cmd;
  }
  else
  {
    Cmd* next = m_firstCmd;
    while (next->next() != 0)
    {
      next = next->next();
    }
    next->setNext(cmd);
  }
}

void CmdSequence::detach(Cmd* cmd)
{
  if (m_firstCmd == cmd)
  {
    m_firstCmd = cmd->next();
  }
  else
  {
    Cmd* next = m_firstCmd;
    while ((next != 0) && next->next() != cmd)
    {
      next = next->next();
    }
    if (next != 0)
    {
      next->setNext(cmd->next());
    }
  }
}

Cmd* CmdSequence::getFirstCmd()
{
  m_cmdListIter = m_firstCmd;
  return m_cmdListIter;
}

Cmd* CmdSequence::getNextCmd()
{
  m_cmdListIter = m_cmdListIter->next();
  return m_cmdListIter;
}
