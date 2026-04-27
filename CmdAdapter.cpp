/*
 * CmdAdapter.cpp
 *
 *  Created on: 11.03.2014
 *      Author: niklausd
 */

#include "CmdAdapter.h"

CmdAdapter::CmdAdapter()
{ }

CmdAdapter::~CmdAdapter()
{ }

CmdAdapter::assignCmdSequence(CmdSequence* cmdSeq)
{
  m_seq = cmdSeq;
}       