#ifndef _EXTENDED_HANDLER_H_
#define _EXTENDED_HANDLER_H_


#include "Touchpad.h"
#include "TouchpadHandler.h"

/**
 * This class is a helper class used by MenuAction classes to restore the TouchPadEvent handler
 * to the MenuEntry.
 */
class ExtendedHandler : public TouchpadEventHandler
{
public:
  /**
   * Set the ExtendedHandler as TouchpadEventHandler.
   */
  virtual void restoreHandler() = 0;
};

#endif//_EXTENDED_HANDLER_H_
