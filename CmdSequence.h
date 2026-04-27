/*
 * CmdSequence.h
 *
 *  Created on: 10.03.2014
 *      Author: niklausd
 */

#ifndef CMDSEQUENCE_H_
#define CMDSEQUENCE_H_

#include <stdbool.h>

class CmdSeqTimer;
class Cmd;
class CmdAdapter;

class CmdSequence
{
public:
  static const int32_t WaitForever;   /**< wait "forever" */
  static const int32_t DoNotWait;     /**< do not wait */

  CmdSequence();
  virtual ~CmdSequence();

  /**
   * @brief Start the command sequence.
   */
  void start();
  
  /**
   * @brief Stop the command sequence.
   */
  void stop();

  /**
   * @brief Check if the command sequence is running.
   * @return True if the sequence is running, false otherwise.
   */ 
  bool isRunning();

  /**
   * @brief Return the pointer to the currently active command if the sequence is running.
   * @details When the sequence has been stopped, this function returns the command that was last active.
   * @return Cmd* Pointer to the currently active command, or last active command when stopped.
   */
  Cmd* currentCmd();

  /**
   * @brief Conclude the current command and proceed to the next command. 
   * @details Normally called by the timer expiry event (and also by the CmdSequence::start() function). 
   *          This command can be called by the user / client and either overrides the timeout of the currently active command or ends a "waiting forever" command.
   *          Stops the timer for the case when the current command has not been finished by timeout, but by an explicit call to this function.
   *          Calls the current command's leave() function, makes the next command the current one, then starts the timer and calls the execute() function of the current command and then runs the next command's preExec() function.
   */
  void execNextCmd();

  /**
   * @brief Attach a Cmd object at the end of the sequence.
   * @param cmd Pointer to the Cmd object.
   */
  void attach(Cmd* cmd);

  /**
   * @brief Detach a Cmd object from the sequence.
   * @param cmd Pointer to the Cmd object.
   */
  void detach(Cmd* cmd);

  /**
   * @brief Assign a concrete CmdAdapter implementation to the sequence.
   * @param adapter Pointer to the CmdAdapter object.
   */
  void assignAdapter(CmdAdapter* adapter);

  /**
   * @brief Get the pointer to the currently assigned CmdAdapter object.
   * @return CmdAdapter* Pointer to the currently assigned CmdAdapter object.
   */
  CmdAdapter* adapter() { return m_adapter; }

  /**
   * @brief Assign a concrete CmdSeqTimer implementation to the sequence.
   * @param timer Pointer to the CmdSeqTimer object.
   */
  void assignTimer(CmdSeqTimer* timer);

  /**
   * @brief Get the pointer to the currently assigned CmdSeqTimer object.
   * @return CmdSeqTimer* Pointer to the currently assigned CmdSeqTimer object.
   */
  CmdSeqTimer* timer() { return m_timer; }

  /**
   * @brief Get the first command in the sequence.
   * @return Cmd* Pointer to the first command in the sequence.
   */
  Cmd* getFirstCmd();

  /**
   * @brief Get the pointer to the next Cmd object owned by the sequence relative to the internally set iterator.
   * @details Sets the internal iterator pointer to the next Cmd object in the list.
   * @return Cmd* Pointer to the next command in the sequence.
   */
  Cmd* getNextCmd();

private:
  /**
   * @brief Execute the current command.
   * @details Reads out the time of the current command and starts the timer, 
   *          then calls the command's execute() function.
   *          If the current command's time  value is set to wait forever (time < 0), the timer will not be started.
   */
  void execCmd();

private:
  bool          m_isRunning;    /**< Indicates if the sequence is running. */
  Cmd*          m_firstCmd;     /**< Pointer to the first command in the sequence. */ 
  Cmd*          m_currentCmd;   /**< Pointer to the currently active command. */
  Cmd*          m_nextCmd;      /**< Pointer to the next command to execute. */
  Cmd*          m_cmdListIter;  /**< Iterator for traversing the command list. */
  CmdAdapter*   m_adapter;      /**< Pointer to the command adapter. */
  CmdSeqTimer*  m_timer;        /**< Pointer to the assigned sequence timer. */

private: // forbidden default functions
  CmdSequence& operator = (const CmdSequence& );  // assignment operator
  CmdSequence(const CmdSequence& src);            // copy constructor
};

#endif /* CMDSEQUENCE_H_ */
