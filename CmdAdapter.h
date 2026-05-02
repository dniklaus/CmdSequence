/*
 * CmdAdapter.h
 *
 *  Created on: 11.03.2014
 *      Author: niklausd
 */

#ifndef CMDADAPTER_H_
#define CMDADAPTER_H_

class CmdSequence;
class CmdAdapter
{
public:
  CmdAdapter() = default;
  virtual ~CmdAdapter() = default;
  virtual void stopAction() { }
  void assignCmdSequence(CmdSequence* cmdSeq);
  CmdSequence* cmdSequence() const;

private:
  CmdSequence* m_seq;  /**< Pointer to the assigned command sequence. */

private: // forbidden default functions
  CmdAdapter& operator= (const CmdAdapter& src) = delete;  // assignment operator
  CmdAdapter(const CmdAdapter& src) = delete;              // copy constructor
};

#endif /* CMDADAPTER_H_ */
