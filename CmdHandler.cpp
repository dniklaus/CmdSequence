/*
 * Cmd.cpp
 *
 *  Created on: 10.03.2014
 *      Author: niklausd
 */

#include <CmdAdapter.h>
#include <CmdHandler.h>
#include <CmdSequence.h>

CmdHandler::CmdHandler(CmdSequence* cmdSeq, unsigned int timeMillis, const char* name)
: m_cmdSeq(cmdSeq)
, m_timeMillis(timeMillis)
, m_name(name)
, m_next(0)
{
  if (0 != cmdSeq)
  {
    cmdSeq->attach(this);
  }
}

CmdHandler::~CmdHandler()
{
  if (0 != m_cmdSeq)
  {
    m_cmdSeq->detach(this);
  }
}

void CmdHandler::setTime(unsigned int timeMillis)
{
  m_timeMillis = timeMillis;
}

unsigned int CmdHandler::getTime()
{
  return m_timeMillis;
}

CmdHandler* CmdHandler::next()
{
  return m_next;
}

void CmdHandler::setNext(CmdHandler* next)
{
  m_next = next;
}

const char* CmdHandler::getName()
{
  return m_name;
}

CmdSequence* CmdHandler::cmdSequence()
{
  return m_cmdSeq;
}

//-----------------------------------------------------------------------------

CmdStop::CmdStop(CmdSequence* cmdSeq, unsigned int timeMillis)
: CmdHandler(cmdSeq, timeMillis, "CmdStop")
{ }

void CmdStop::execute()
{
  if ((0 != cmdSequence()) && (0 != cmdSequence()->adapter()))
  {
    cmdSequence()->adapter()->stopAction();
  }
}

//-----------------------------------------------------------------------------
