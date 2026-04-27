/*
 * CmdSequence.cpp
 *
 *  Created on: 10.03.2014
 *      Author: niklausd
 */

#include <stdint.h>
#include "CmdSeqTimer.h"
#include "CmdAdapter.h"
#include "Cmd.h"
#include "CmdSequence.h"

const int32_t CmdSequence::WaitForever = -1;   /*<! wait "forever" */
const int32_t CmdSequence::DoNotWait = 0;      /*<! do not wait */

CmdSequence::CmdSequence()
: m_isRunning(false)
, m_firstCmd(0)
, m_currentCmd(0)
, m_nextCmd(0)
, m_cmdListIter(0)
, m_adapter(0)
, m_timer(0)
{ }

CmdSequence::~CmdSequence()
{
  // unassign all attached cmd objects 
  Cmd* cmd = getFirstCmd();
  while(0 != cmd)
  {
      cmd->assign((CmdSequence*)0);
      cmd = getNextCmd();
  }
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
  if (0 != m_timer)
  {
    m_timer->cancel();
  }
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
  if (0 != m_timer)
  {
    m_timer->cancel();      // stop timer for the case the current command has not been finished by timeout
  }
  if (0 != m_currentCmd)
  {
    m_currentCmd->leave();  // leave the current command
    m_currentCmd = m_currentCmd->next(); // proceed to the next command
  }
  execCmd();
}

void CmdSequence::execCmd()
{
  if ((0 != m_currentCmd) && (0 != m_timer))
  {
    int32_t currentCmdTime = m_currentCmd->getTime();
    if (currentCmdTime > WaitForever)
    {
      // time = 0: do not wait, immediately proceed to the next command of the sequence since the timer will expire immediately
      // time > 0: wait in this command the specified time [ms]
      m_timer->start(static_cast<uint32_t>(currentCmdTime));
    }
    // else
    // {
    //   // time < 0: wait forever in this command, since the timer is not started,
    //   //           => this makes the sequence only proceed to the next command on an explicit call to the method CmdSequence::execNextCmd().
    // }

    m_isRunning = true;

    m_nextCmd = m_currentCmd->next();   // prepare for pre-execution of next cmd

    m_currentCmd->execute();            // execute the current command

    if (0 != m_nextCmd)
    {
      m_nextCmd->preExec();             // pre-execute the next command
    }
  }
  else
  {
    // end of the sequence (or no timer error)
    m_isRunning = false;
    if (0 != m_timer)
    {
      m_timer->cancel();
    }
    m_currentCmd = m_firstCmd;
  }
}

void CmdSequence::attach(Cmd* cmd)
{
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

void CmdSequence::assignAdapter(CmdAdapter* adapter)
{
  m_adapter = adapter;
  if (0 != m_adapter)
  {
    m_adapter->assignCmdSequence(this);
  }
}

void CmdSequence::assignTimer(CmdSeqTimer* timer)
{
  m_timer = timer;
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
