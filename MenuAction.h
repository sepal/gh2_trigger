#ifndef _MENUACTION_H_
#define _MENUACTION_H_

#include "LCD.h"
#include "Touchpad.h"
#include "TouchpadHandler.h"
#include "ExtendedHandler.h"

class MenuAction : public TouchpadEventHandler
{
public:
  MenuAction(const char* label, ExtendedHandler* parentHandler)
  {
    this->parentHandler = parentHandler;
    this->label = label;
    wipeDetection = false;
  }
  
  virtual void printStuff() = 0;
  virtual void enter() = 0;
  virtual void updateInput() = 0;
  
  virtual void update()
  {
    if (inputTimer.ready()) {
      updateInput();
    }
  }
  
  virtual void centerChanged(bool pressed)
  {
    if (pressed) {
      LCD.stopBlinkingBox();
      parentHandler->restoreHandler();
    }
  }
protected:
  const char* label;
  SoftTimer inputTimer;
  int add;
  ExtendedHandler* parentHandler;

};

#endif//_MENUACTION_H_
