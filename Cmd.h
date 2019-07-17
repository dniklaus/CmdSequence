/*
 * Cmd.h
 *
 *  Created on: 10.03.2014
 *      Author: niklausd
 */

#ifndef CMDHANDLER_H_
#define CMDHANDLER_H_

class CmdSequence;

class Cmd
{
protected:
  Cmd(CmdSequence* cmdSeq, unsigned int timeMillis, const char* name);

public:
  virtual ~Cmd();

  void setTime(unsigned int millis);
  unsigned int getTime();

  virtual void execute() = 0;

  Cmd* next();
  void setNext(Cmd* next);

  const char* getName();

  CmdSequence* cmdSequence();

private:
  CmdSequence*  m_cmdSeq;
  unsigned int  m_timeMillis;
  const char*   m_name;
  Cmd*   m_next;

private: // forbidden default functions
  Cmd& operator = (const Cmd& src); // assignment operator
  Cmd(const Cmd& src);              // copy constructor
};

//-----------------------------------------------------------------------------

class CmdStop : public Cmd
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
