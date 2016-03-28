/*
 * CmdSequence.h
 *
 *  Created on: 10.03.2014
 *      Author: niklausd
 */

#ifndef CMDSEQUENCE_H_
#define CMDSEQUENCE_H_

class Timer;
class CmdHandler;
class CmdAdapter;

class CmdSequence
{
public:
  CmdSequence(CmdAdapter* adapter);
  virtual ~CmdSequence();

  void start();
  void stop();

  bool isRunning();

  CmdHandler* currentCmd();

  void execNextCmd();

  void attach(CmdHandler* cmd);
  void detach(CmdHandler* cmd);

  void attachAdapter(CmdAdapter* adapter);
  CmdAdapter* adapter() { return m_adapter; }

  CmdHandler* getFirstCmd();
  CmdHandler* getNextCmd();

private:
  void execCmd();

private:
  bool        m_isRunning;
  CmdHandler*        m_firstCmd;
  CmdHandler*        m_currentCmd;
  CmdHandler*        m_cmdListIter;
  CmdAdapter* m_adapter;
  Timer*      m_timer;

private: // forbidden default functions
  CmdSequence& operator = (const CmdSequence& );  // assignment operator
  CmdSequence(const CmdSequence& src);            // copy constructor
};

#endif /* CMDSEQUENCE_H_ */
