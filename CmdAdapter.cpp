/*
 * CmdAdapter.cpp
 *
 *  Created on: 11.03.2014
 *      Author: niklausd
 */

#include "CmdSequence.h"
#include "CmdAdapter.h"

void CmdAdapter::assignCmdSequence(CmdSequence* cmdSeq)
{
  m_seq = cmdSeq;
}       

CmdSequence* CmdAdapter::cmdSequence() const
{
  return m_seq;
}
