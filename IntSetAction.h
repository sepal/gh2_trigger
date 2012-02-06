
#ifndef _INT_SET_ACTION_H_
#define _INT_SET_ACTION_H_

#include "LCD.h"
#include "Touchpad.h"
#include "TouchpadHandler.h"

#define INT_SETTER_INPUT_TIMER 0.08f
#define INT_SETTER_INPUT_DELAY 0.8f

class IntSetAction : public MenuAction
{
public:
  /**
   * Constructor which initializes the parent class MenuAction as well as all variables.
   */
  IntSetAction(const char* label, ExtendedHandler* parentHandler, int defaultValue) : MenuAction(label, parentHandler)
  {
    pos = 6;
    value = defaultValue;
  }
  
  /**
   * Overrides MenuAction::printStuff();
   */
  void printStuff()
  {
    LCD.setPosition(0, 1);
    LCD.clearEOL();
    LCD.print(label);
    LCD.print(':');
    LCD.setPosition(11, 1);
    LCD.printFormatedNumber(value, 10000); 
  }
    
  /**
   * Overrides TouchpadEventHandler::enter();
   */
  virtual
  void enter()
  {
    Touchpad.setHandler(this);
    LCD.setPosition(15, 1);
    LCD.startBlinkingBox();
    pos = 6;
  }

  /**
   * Overrides MenuAction::updateInput();
   */
  virtual void updateInput() {
    modValue();
  }
  
  void modValue() {
    value+=add;
    if (value<0) {
      value = 0;
    }
    LCD.setPosition(11, 1);
    LCD.printFormatedNumber(value, 10000);
    LCD.setPosition(15, 1);
  }
  
  /**
   * Overrides TouchpadEventHandler::upChanged();
   */
  virtual void upChanged(bool pressed)
  {
    if (pressed) {
      inputTimer.start(INT_SETTER_INPUT_TIMER, INT_SETTER_INPUT_DELAY);
      LCD.stopBlinkingBox();
      add = 1;
      modValue();
    } else {
      inputTimer.stop();
      LCD.startBlinkingBox();
    }
  }
  
  /**
   * Overrides TouchpadEventHandler::downChanged();
   */
  virtual void downChanged(bool pressed)
  {
    if (pressed) {
      inputTimer.start(INT_SETTER_INPUT_TIMER, INT_SETTER_INPUT_DELAY);
      LCD.stopBlinkingBox();
      add = -1;
      modValue();
    } else {
      inputTimer.stop();
      LCD.startBlinkingBox();
    }
  }
  
  /**
   * Overrides TouchpadEventHandler::leftChanged();
   */
  virtual void leftChanged(bool pressed)
  {
  }
  
  /**
   * Overrides TouchpadEventHandler::downChanged();
   */
  virtual void rightChanged(bool pressed)
  {
  }
  
  /**
   * Returns the value which was set by the user.
   */
  int getValue() 
  {
    return value;
  }
protected:
  int pos;
  int value;
  
};
#endif//_INT_SET_ACTION_H_
