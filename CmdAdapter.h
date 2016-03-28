/*
 * CmdAdapter.h
 *
 *  Created on: 11.03.2014
 *      Author: niklausd
 */

#ifndef CMDADAPTER_H_
#define CMDADAPTER_H_

class CmdAdapter
{
public:
  CmdAdapter();
  virtual ~CmdAdapter();
  virtual void stopAction() { }

private: // forbidden default functions
  CmdAdapter& operator= (const CmdAdapter& src);  // assignment operator
  CmdAdapter(const CmdAdapter& src);              // copy constructor
};

#endif /* CMDADAPTER_H_ */
