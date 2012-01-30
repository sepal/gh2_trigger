#ifndef _EXTENDED_HANDLER_H_
#define _EXTENDED_HANDLER_H_


#include "Touchpad.h"
#include "TouchpadHandler.h"

class ExtendedHandler : public TouchpadEventHandler
{
public:
  virtual void restoreHandler() = 0;
};

#endif//_EXTENDED_HANDLER_H_
