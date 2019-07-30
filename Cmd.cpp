/*
 * Cmd.cpp
 *
 *  Created on: 10.03.2014
 *      Author: niklausd
 */

#include "Cmd.h"

#include "CmdAdapter.h"
#include "CmdSequence.h"

Cmd::Cmd(CmdSequence* cmdSeq, long int timeMillis, const char* name)
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

Cmd::~Cmd()
{
  if (0 != m_cmdSeq)
  {
    m_cmdSeq->detach(this);
  }
}

void Cmd::setTime(long int millis)
{
  m_timeMillis = millis;
}

long int Cmd::getTime()
{
  return m_timeMillis;
}

Cmd* Cmd::next()
{
  return m_next;
}

void Cmd::setNext(Cmd* next)
{
  m_next = next;
}

const char* Cmd::getName()
{
  return m_name;
}

CmdSequence* Cmd::cmdSequence()
{
  return m_cmdSeq;
}

void Cmd::assign(CmdSequence* cmdSeq)
{
  m_cmdSeq = cmdSeq;
}

//-----------------------------------------------------------------------------

CmdStop::CmdStop(CmdSequence* cmdSeq, unsigned int timeMillis)
: Cmd(cmdSeq, timeMillis, "CmdStop")
{ }

void CmdStop::execute()
{
  if ((0 != cmdSequence()) && (0 != cmdSequence()->adapter()))
  {
    cmdSequence()->adapter()->stopAction();
  }
}

//-----------------------------------------------------------------------------
