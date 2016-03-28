/*
 * CmdSequence.cpp
 *
 *  Created on: 10.03.2014
 *      Author: niklausd
 */

#include "Timer.h"
#include "CmdHandler.h"
#include "CmdAdapter.h"
#include "CmdSequence.h"

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

CmdSequence::CmdSequence(CmdAdapter* adapter)
: m_isRunning(false)
, m_firstCmd(0)
, m_currentCmd(0)
, m_cmdListIter(0)
, m_adapter(adapter)
, m_timer(new Timer(new CmdSeqTimerAdapter(this), Timer::IS_NON_RECURRING))
{ }

CmdSequence::~CmdSequence()
{ }

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

CmdHandler* CmdSequence::currentCmd()
{
  return m_currentCmd;
}

void CmdSequence::execNextCmd()
{
  m_currentCmd = m_currentCmd->next();
  execCmd();
}

void CmdSequence::execCmd()
{
  if ((0 != m_currentCmd) && (0 != m_timer))
  {
    m_isRunning = true;
    m_timer->startTimer(m_currentCmd->getTime());
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

void CmdSequence::attach(CmdHandler* cmd)
{
  if (0 == m_firstCmd)
  {
    m_firstCmd = cmd;
  }
  else
  {
    CmdHandler* next = m_firstCmd;
    while (next->next() != 0)
    {
      next = next->next();
    }
    next->setNext(cmd);
  }
}

void CmdSequence::detach(CmdHandler* cmd)
{
  if (m_firstCmd == cmd)
  {
    m_firstCmd = cmd->next();
  }
  else
  {
    CmdHandler* next = m_firstCmd;
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

CmdHandler* CmdSequence::getFirstCmd()
{
  m_cmdListIter = m_firstCmd;
  return m_cmdListIter;
}

CmdHandler* CmdSequence::getNextCmd()
{
  m_cmdListIter = m_cmdListIter->next();
  return m_cmdListIter;
}
