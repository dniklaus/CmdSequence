/*
 * CmdSequence.h
 *
 *  Created on: 10.03.2014
 *      Author: niklausd
 */

#ifndef CMDSEQUENCE_H_
#define CMDSEQUENCE_H_

class Timer;
class Cmd;
class CmdAdapter;

class CmdSequence
{
public:
  CmdSequence(CmdAdapter* adapter);
  virtual ~CmdSequence();

  void start();
  void stop();

  bool isRunning();

  Cmd* currentCmd();

  void execNextCmd();

  void attach(Cmd* cmd);
  void detach(Cmd* cmd);

  void attachAdapter(CmdAdapter* adapter);
  CmdAdapter* adapter() { return m_adapter; }

  Cmd* getFirstCmd();
  Cmd* getNextCmd();

private:
  void execCmd();

private:
  bool        m_isRunning;
  Cmd*        m_firstCmd;
  Cmd*        m_currentCmd;
  Cmd*        m_cmdListIter;
  CmdAdapter* m_adapter;
  Timer*      m_timer;

private: // forbidden default functions
  CmdSequence& operator = (const CmdSequence& );  // assignment operator
  CmdSequence(const CmdSequence& src);            // copy constructor
};

#endif /* CMDSEQUENCE_H_ */
