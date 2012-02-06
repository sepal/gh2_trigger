#ifndef _MENUACTION_H_
#define _MENUACTION_H_

#include "LCD.h"
#include "Touchpad.h"
#include "TouchpadHandler.h"
#include "ExtendedHandler.h"

/**
 * Abstract class for menu actions.
 * Menu actions are used to set options of menu (for example the interval for Intervalometer) or to
 * to do other stuff in menus.
 */
class MenuAction : public TouchpadEventHandler
{
public:
  /**
   * MenuActions need a label and a parentHandler, which is the Menu which owns this MenuAction.
   */
  MenuAction(const char* label, ExtendedHandler* parentHandler);
  
  /**
   * Update the inputTimer.
   */
  virtual void update();
  
  /**
   * Overrides TouchpadEventHandler::centerChanged(bool pressed) returns the touchpad handler to the
   * parentHandler.
   */
  virtual void centerChanged(bool pressed);
  
  /**
   * Print the label and other stuff to the LCD (used when the parentHandler wants switches to this
   * action).
   */
  virtual void printStuff() = 0;
  
  /**
   * Used when the navigation is set to this class.
   */
  virtual void enter() = 0;
  
  /**
   * Called when the inpuTimer triggers.
   * This can be used to modify(increase/decrease or whatever) a value constantly while the the 
   * touchpad is pressed.
   */
  virtual void updateInput() = 0;
  
protected:
  const char* label;
  SoftTimer inputTimer;
  int add;
  ExtendedHandler* parentHandler;
};

#endif//_MENUACTION_H_
