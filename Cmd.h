/*
 * Cmd.h
 *
 *  Created on: 10.03.2014
 *      Author: niklausd
 */

#ifndef CMDHANDLER_H_
#define CMDHANDLER_H_

#include <stdint.h>

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
   * @param cmdSeq Pointer to the Command Sequence object where the current command automatically attaches itself to, no auto-attach will happen if this is 0 (null pointer).
   * @param timeMicros Time to wait [us] (<0: wait forever in this command, 0: do not wait, >0: wait in this command the specified time [us]).
   * @param name Name of the current command.
   * @param branchName Name of the branch command to jump to; if no branching is desired, provide an empty string ("").
   */
  explicit Cmd(CmdSequence* cmdSeq, int32_t timeMicros, const char* name, const char* branchName) = delete;

public:
  virtual ~Cmd();

  /**
   * @brief Assign the given Command Sequence object.
   * @details This Cmd object gets assigned to the given Command Sequence at the end of the linked list of Cmd objects held by the sequence. 
   * @param cmdSeq Pointer to the Command Sequence object to be assigned.
   */
  void assign(CmdSequence* cmdSeq);

  /**
   * @brief Pre-execution hook for the command.
   * @details This method is called once before the command execution starts.
   *          Implement this method in your specific command if you need to do some preparation before the actual execution.
   * @note This function won't be called on the first command of a sequence.
   */
  virtual void preExec() { }

  /**
   * @brief Pure virtual execution method, called by the sequence.
   * @details This method is called to execute the command.
   *          Implement this in your specific command.
   */
  virtual void execute() = 0;

   /**
     * @brief Virtual default empty leave method, called by the sequence when the command time is over or the next command has been started by calling CmdSequence::execNextCmd().
     * @details This method is called once after the command execution ends.
     *          Implement this in your specific command, if you want take some measures on leaving the command.
     */
  virtual void leave() { }

  /**
   * @brief Get the next command from the sequence.
   * @details This method returns the next command to be executed, taking into account any branching conditions, clears the doBranch flag after evaluation.
   * @return Pointer to the next Cmd object in the sequence.
   */
  Cmd* next();

  /**
   * @brief Set time the current command shall wait until the next one would be started.
   * @param timeMicros Time to wait [us] (<0: wait forever in this command, 0: do not wait, >0: wait in this command the specified time [us]).
   */
  void setTime(int32_t timeMicros);
  
  /**
   * @brief Get the time the current command shall wait until the next one would be started.
   * @return timeMicros Time to wait [us] (<0: wait forever in this command, 0: do not wait, >0: wait in this command the specified time [us]).
   */
  int32_t getTime();

  /**
   * @brief Set the Next object in the sequence.
   * @param next Pointer to the Next Cmd object to be set.
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
   * @return true if the Cmd object's name is as the provided parameter, false otherwise.
   */
  bool isName(const char* name);

  /**
   * @brief Get CmdSequence object this command object has been assigned to.
   * @return Pointer to CmdSequence object this command object has been assigned to.
   */
  CmdSequence* cmdSequence();

  /**
   * @brief Get the name of the command to branch to.
   * @return Name of the branch command, empty string if no branch is configured.
   */
  char* (*getBranchName)(Cmd const* const me);

  /**
   * @brief Check if the branch name matches the given name.
   * @param name Name to check.
   * @return true if the given name matches the Cmd object's branch name, false otherwise.
   */
  bool (*isBranchName)(Cmd const* const me, const char* name);

  /**
   * @brief Get the command to branch to.
   * @return Pointer to branch command.
   */
  Cmd* (*branch)(Cmd const* const me);

  /**
   * @brief Set the command to branch to.
   * @param branch Pointer to branch command.
   */
  void (*setBranch)(Cmd* const me, Cmd* branch);

  /**
   * @brief Get the branching status.
   * @return true if branching shall happen, false otherwise.
   */
  bool (*doBranch)(Cmd const* const me);

  /**
   * @brief Set the branching status.
   * @param doBranch New branching status.
   */
  void (*setDoBranch)(Cmd* const me, bool doBranch);

private:
  CmdSequence*  m_cmdSeq;      /**< Pointer to the assigned command sequence. */
  int32_t       m_timeMicros;  /**< <0: wait forever in this command, 0: do not wait, >0: wait in this command the specified time [us]. */
  const char*   m_name;        /**< Name of the command. */
  const char*   m_branchName;  /**< Name of the branch command, if any. */
  Cmd*          m_next;        /**< Pointer to the next command in the sequence. */
  Cmd*          m_branch;      /**< Pointer to the branch command, if any. */
  bool          m_doBranch;    /**< Flag indicating if branching shall happen. */
};

//-----------------------------------------------------------------------------

class CmdStop : public Cmd
{
public:
  CmdStop(CmdSequence* cmdSeq, int32_t timeMicros);
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
  CmdWait(CmdSequence* cmdSeq, int32_t timeMicros);
  virtual ~CmdWait() { }
  virtual void execute();

private: // forbidden default functions
  CmdWait& operator = (const CmdWait& src); // assignment operator
  CmdWait(const CmdWait& src);              // copy constructor
};

//-----------------------------------------------------------------------------

#endif /* CMDHANDLER_H_ */
