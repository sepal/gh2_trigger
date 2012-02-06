
#ifndef _TIME_SET_ACTION_H_
#define _TIME_SET_ACTION_H_

#include "LCD.h"
#include "Touchpad.h"
#include "TouchpadHandler.h"
#include "MenuAction.h"

#define TIME_SETTER_INPUT_TIMER 0.15f
#define TIME_SETTER_INPUT_DELAY 0.8f

/**
 * This MenuAction class is used to allow users to set time fields like the interval of timelapses 
 * shots.
 */
class TimeSetAction : public MenuAction
{
public:
  /**
   * Constructor which initializes the parent class MenuAction as well as all variables.
   */
  TimeSetAction(const char* label, ExtendedHandler* parentHandler, long time) : MenuAction(label, parentHandler)
  {
    cMinutes = time / 60000;
    cSeconds = (time - cMinutes * 60000) / 1000;
    cMillis = time - cSeconds * 1000 - cMinutes * 60000;
    pos = 4;
  }
  
  /**
   * Overrides MenuAction::printStuff();
   */
  virtual void printStuff()
  {
    LCD.setPosition(0, 1);
    LCD.clearEOL();
    LCD.print(label);
    LCD.print(":");
    LCD.setPosition(7, 1);
    LCD.printFormatedNumber(cMinutes, 10);
    LCD.print(":");
    LCD.printFormatedNumber(cSeconds, 10);
    LCD.print(".");
    LCD.printFormatedNumber(cMillis, 100);
  }
  
  /**
   * Overrides TouchpadEventHandler::enter();
   */
  virtual void enter()
  {
    Touchpad.setHandler(this);
    LCD.setPosition(11, 1);
    LCD.startBlinkingBox();
    pos = 4;
  }
  
  /**
   * Overrides MenuAction::updateInput();
   */
  virtual void updateInput() {
    modTime();
  }
  
  /**
   * Overrides TouchpadEventHandler::upChanged();
   */
  virtual void upChanged(bool pressed)
  {
    if (pressed) {
      inputTimer.start(TIME_SETTER_INPUT_TIMER, TIME_SETTER_INPUT_DELAY);
      LCD.stopBlinkingBox();
      add = 1;
      modTime();
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
      inputTimer.start(TIME_SETTER_INPUT_TIMER, TIME_SETTER_INPUT_DELAY);
      LCD.stopBlinkingBox();
      add = -1;
      modTime();
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
    if (pressed) {
      switch (pos) {
        case 1:
        case 4:
        case 7:
        case 8:
          pos--;
          LCD.setPosition(7+pos, 1);
          break;
        case 3:
        case 6:
          pos-=2;
          LCD.setPosition(7+pos, 1);
          break;
      }
    }
  }
  
  /**
   * Overrides TouchpadEventHandler::rightChanged();
   */
  virtual void rightChanged(bool pressed)
  {
    if (pressed) {
      switch (pos) {
        case 0:
        case 3:
        case 6:
        case 7:
          pos++;
          LCD.setPosition(7+pos, 1);
          break;
        case 1:
        case 4:
          pos+=2;
          LCD.setPosition(7+pos, 1);
      }
    }
  }
  
  /**
   * Returns the time which was set by the user.
   */
  long getTime() 
  {
    return cMinutes*60000+cSeconds*1000+cMillis;
  }
protected:
  int pos;
  int cMinutes, cSeconds, cMillis;
  
  /**
   * Change the correct member dependend on the current cursor position.
   */
  void modTime() {
    switch (pos) {
      case 0:
        modifyTime(&cMinutes, 10, 7, 59);
        break;
      case 1:
        modifyTime(&cMinutes, 1, 7, 59);
        break;
        
      case 3:
        modifyTime(&cSeconds, 10, 10, 59);
        break;
      case 4:
        modifyTime(&cSeconds, 1, 10, 59);
        break;
        
      case 6:
        modifyTime(&cMillis, 100, 13, 999);
        break;
      case 7:
        modifyTime(&cMillis, 10, 13, 999);
        break;
      case 8:
        modifyTime(&cMillis, 1, 13, 999);
        break;
    }
  }
  
  /**
   * Add or subtract a value of variable and print it.
   * this function is used to to modify the members cMinute, cSecond and cMillis.
   */
  void modifyTime(int *var, int times, int lcdPos, int max) {
    (*var)+=add*times;
    if ((*var) > max) {
      (*var) -= (max+1);
    } else if((*var) < 0) {
      (*var) = max;
    }
    byte orgPos = LCD.getPosition();
    LCD.setPosition(lcdPos, 1);
    LCD.printFormatedNumber((*var), 10);
    LCD.setPosition(orgPos, 1);
  }
};
#endif//_TIME_SET_ACTION_H_
