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

Cmd::Cmd(CmdSequence* cmdSeq, int32_t timeMicros, const char* name, const char* branchName)
  : m_cmdSeq(cmdSeq)
  , m_timeMicros(timeMicros)
  , m_name(0)
  , m_next(0)
  , m_branch(0)
  , m_doBranch(false)
{
  uint8_t nameLen = strlen(name) + 1;
  m_name = new char[nameLen];
  strncpy(m_name, name, nameLen);

  uint8_t branchNameLen = strlen(branchName) + 1;
  m_branchName = new char[branchNameLen];
  strncpy(m_branchName, branchName, branchNameLen);

  assign(cmdSeq);
}

Cmd::~Cmd()
{
  assign((CmdSequence*)0);

  delete [] m_name;
  m_name = 0;

  delete [] m_branchName;
  m_branchName = 0;
}

void Cmd::assign(CmdSequence* cmdSeq)
{
  if (0 != cmdSeq)
  {
    // attach this Cmd to the cmdSeq
    cmdSeq->attach(this);
  }
  else 
  {
    if (0 != m_cmdSeq)
    {
      // detach this Cmd from the formerly attached cmdSeq
      m_cmdSeq->detach(this);
    }
  }
  m_cmdSeq = cmdSeq;
}

void Cmd::setTime(int32_t timeMicros)
{
  m_timeMicros = timeMicros;
}

int32_t Cmd::getTime()
{
  return m_timeMicros;
}

Cmd* Cmd::next()
{
    bool mustBranch = false;
    // evaluate branch condition
    if (0 == m_branch)
    {
        if (isBranchName("exit"))
        {
            // explicit exit: null ptr is intended!
            mustBranch = m_doBranch;
            m_doBranch = false;      // reset branch condition flag
        }
    }
    else
    {
        mustBranch = m_doBranch;
        m_doBranch = false;          // reset branch condition flag
    }
    
    Cmd* selectedNext = mustBranch ? m_branch : m_next;
    // return semantic next pointer according to branch condition
    return selectedNext;
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

char* Cmd::getBranchName()
{
    return m_branchName;
}

bool Cmd::isBranchName(const char* branchName)
{
    bool isTheSame = false;
    if (strlen(m_branchName) == strlen(branchName))
    {
        if (strncmp(m_branchName, branchName, strlen(branchName)) == 0)
        {
            isTheSame = true;
        }
    }
    return isTheSame;
}

Cmd* Cmd::branch()
{
    return m_branch;
}

void Cmd::setBranch(Cmd* branch)
{
    m_branch = branch;
}

bool Cmd::doBranch() const
{
    return m_doBranch;
}

void Cmd::setDoBranch(bool doBranch)
{
    m_doBranch = doBranch;
}

//-----------------------------------------------------------------------------

CmdStop::CmdStop(CmdSequence* cmdSeq, int32_t timeMicros)
: Cmd(cmdSeq, timeMicros, "CmdStop")
{ }

void CmdStop::execute()
{ 
  if ((0 != cmdSequence()) && (0 != cmdSequence()->adapter()))
  {
    cmdSequence()->adapter()->stopAction();
  }
}

//-----------------------------------------------------------------------------

CmdWait::CmdWait(CmdSequence* cmdSeq, int32_t timeMicros)
: Cmd(cmdSeq, timeMicros, "CmdWait")
{ }

void CmdWait::execute()
{ }

//-----------------------------------------------------------------------------
