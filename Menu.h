
#ifndef _MENU_H_
#define _MENU_H_

#include "MenuEntry.h"
#include "TouchpadHandler.h"

/**
 * This handles all the menus.
 */
class MenuSystem : public TouchpadEventHandler
{
public:
  /**
   * Initializes the variables.
   */
  MenuSystem();
  
  /**
   * Sets the MenuEntry which should be shown first and prints the corresponding stuff to the LCD. 
   */
  void initialize(MenuEntry* entry);
  
  /**
   * Overrides TouchpadEventHandler::upChanged(bool pressed).
   */
  virtual void upChanged(bool pressed);
  
  /**
   * Overrides TouchpadEventHandler::downChanged(bool pressed).
   */
  virtual void downChanged(bool pressed);
  
  /**
   * Overrides TouchpadEventHandler::leftChanged(bool pressed).
   */
  virtual void leftChanged(bool pressed);
  
  /**
   * Overrides TouchpadEventHandler::rightChanged(bool pressed).
   */
  virtual void rightChanged(bool pressed);
  
  /**
   * Overrides TouchpadEventHandler::centerChanged(bool pressed).
   */
  virtual void centerChanged(bool pressed);
  
  /**
   * Updates the current MenuEntry.
   */
  void update();
  
  /**
   * Tells the main loop to block all other systems.
   */
  bool blockSystem();
  
  /**
   * Returns the touchpad handling to this class.
   */
  void returnToMenu();
private:
  MenuEntry* current;

  /**
   * Prints the label for the current menu. 
   */
  void updateDisplay();
};

extern MenuSystem Menu; 

#endif//_MENU_H_
