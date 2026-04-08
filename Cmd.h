/*
 * Cmd.h
 *
 *  Created on: 10.03.2014
 *      Author: niklausd
 */

#ifndef CMDHANDLER_H_
#define CMDHANDLER_H_

class CmdSequence;

/**
 * Abstract Command class.
 * Implementations derived from this abstract class can be arranged to a sequence of commands that will be executed in the order how they have been attached to the sequence.
 */
class Cmd
{
protected:
  /**
   * Constructor.
   * @param cmdSeq Pointer to the Command Sequence object where the current command automatically attaches itself to, no auto- will happen if this is 0 (null pointer).
   * @param timeMillis Time to wait [ms] (<0: wait forever in this command, 0: do not wait, >0: wait in this command the specified time [ms]).
   * @param name Name of the current command.
   */
  Cmd(CmdSequence* cmdSeq, long int timeMillis, const char* name);

public:
  virtual ~Cmd();

  /**
   * Assign the given Command Sequence object.
   * @param Pointer to the Command Sequence object to be assigned.
   */
  void assign(CmdSequence* cmdSeq);

  /**
   * Set time the current command shall wait until the next one would be started.
   * @param timeMillis Time to wait [ms] (<0: wait forever in this command, 0: do not wait, >0: wait in this command the specified time [ms]).
   */
  void setTime(long int timeMillis);
  
  /**
   * Get the time the current command shall wait until the next one would be started.
   * @return timeMillis Time to wait [ms] (<0: wait forever in this command, 0: do not wait, >0: wait in this command the specified time [ms]).
   */
  long int getTime();

  /**
   * Pure virtual execution method, called by the sequence.
   * Implement this in your specific command.
   */
  virtual void execute() = 0;

  /**
   * Default empty leave method, called by the sequence when the command time is over.
   * Implement this in your specific command, if you want take some measures on leaving the command.
   */
  virtual void leave() { }

  /**
   * @brief Get the next element from the list.
   * @return Next Cmd object in the List.
   */
  Cmd* next();

  /**
   * @brief Set the Next object in the list.
   * @param next Next Cmd object to be se
   */
  void setNext(Cmd* next);

  /**
   * @brief Get the Name of the Cmd object
   * @return const char* Name of the command object.
   */
  const char* getName();

  /**
   * @brief Check if the Cmd object's name is as the provided parameter.
   * @param name Name to be checked for.
   * @return true The Cmd object's name is as the provided parameter.
   * @return false The Cmd object's name is not as the provided parameter.
   */
  bool isName(const char* name);

  /**
   * @brief Get CmdSequnece object that has been assigned to this command.
   * @return CmdSequence object that has been assigned to this command.
   */
  CmdSequence* cmdSequence();

private:
  CmdSequence*  m_cmdSeq;
  long int m_timeMillis; /// <0: wait forever in this command, 0: do not wait, >0: wait in this command the specified time [ms].
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
  CmdStop(CmdSequence* cmdSeq, long int timeMillis);
  virtual ~CmdStop() { }
  virtual void execute();

private: // forbidden default functions
  CmdStop& operator = (const CmdStop& src); // assignment operator
  CmdStop(const CmdStop& src);              // copy constructor
};

//-----------------------------------------------------------------------------

class CmdWait : public Cmd
{
public:
  CmdWait(CmdSequence* cmdSeq, long int timeMillis);
  virtual ~CmdWait() { }
  virtual void execute();

private: // forbidden default functions
  CmdWait& operator = (const CmdWait& src); // assignment operator
  CmdWait(const CmdWait& src);              // copy constructor
};

//-----------------------------------------------------------------------------

#endif /* CMDHANDLER_H_ */
