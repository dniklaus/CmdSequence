/*
 * CmdHandler.h
 *
 *  Created on: 10.03.2014
 *      Author: niklausd
 */

#ifndef CMDHANDLER_H_
#define CMDHANDLER_H_

class CmdSequence;

class CmdHandler
{
protected:
  CmdHandler(CmdSequence* cmdSeq, unsigned int timeMillis, const char* name);

public:
  virtual ~CmdHandler();

  void setTime(unsigned int millis);
  unsigned int getTime();

  virtual void execute() = 0;

  CmdHandler* next();
  void setNext(CmdHandler* next);

  const char* getName();

  CmdSequence* cmdSequence();

private:
  CmdSequence*  m_cmdSeq;
  unsigned int  m_timeMillis;
  const char*   m_name;
  CmdHandler*   m_next;

private: // forbidden default functions
  CmdHandler& operator = (const CmdHandler& src); // assignment operator
  CmdHandler(const CmdHandler& src);              // copy constructor
};

//-----------------------------------------------------------------------------

class CmdStop : public CmdHandler
{
public:
  CmdStop(CmdSequence* cmdSeq, unsigned int timeMillis);
  virtual ~CmdStop() { }
  virtual void execute();

private: // forbidden default functions
  CmdStop& operator = (const CmdStop& src); // assignment operator
  CmdStop(const CmdStop& src);              // copy constructor
};

//-----------------------------------------------------------------------------

#endif /* CMDHANDLER_H_ */
