
#ifndef _MENU_H_
#define _MENU_H_

#include "MenuEntry.h"
#include "TouchpadHandler.h"

class MenuSystem : public TouchpadEventHandler
{
public:
  MenuSystem();
  void initialize(MenuEntry* entry);
  virtual void upChanged(bool pressed);
  virtual void downChanged(bool pressed);
  virtual void leftChanged(bool pressed);
  virtual void rightChanged(bool pressed);
  virtual void centerChanged(bool pressed);
  
  void returnToMenu();
private:
  MenuEntry* current;
  void updateDisplay();
};

extern MenuSystem Menu; 

#endif//_MENU_H_
