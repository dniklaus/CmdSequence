/*
 * Cmd.cpp
 *
 *  Created on: 10.03.2014
 *      Author: niklausd
 */

#include <string.h>
#include "CmdAdapter.h"
#include "CmdSequence.h"
#include "Cmd.h"

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

bool Cmd::isName(const char* name)
{
  bool isTheSame = false;
  if (strlen(m_name) == strlen(name))
  {
    if (strncmp(m_name, name, strlen(name)) == 0)
    {
      isTheSame = true;
    }
  }
  return isTheSame;
}

CmdSequence* Cmd::cmdSequence()
{
  return m_cmdSeq;
}

void Cmd::assign(CmdSequence* cmdSeq)
{
  m_cmdSeq = cmdSeq;
  if (0 != cmdSeq)
  {
    cmdSeq->attach(this);
  }
}

//-----------------------------------------------------------------------------

CmdStop::CmdStop(CmdSequence* cmdSeq, long int timeMillis)
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

CmdWait::CmdWait(CmdSequence* cmdSeq, long int timeMillis)
: Cmd(cmdSeq, timeMillis, "CmdWait")
{ }

void CmdWait::execute()
{ }

//-----------------------------------------------------------------------------
