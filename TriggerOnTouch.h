
#ifndef _TRIGGER_ON_TOUCH_H_
#define _TRIGGER_ON_TOUCH_H_

#include "LCD.h"
#include "Menu.h"
#include "Touchpad.h"
#include "MenuEntryCamTrigger.h"

/**
 * 
 */
class TriggerOnTouch : MenuEntryCamTrigger
{
public:
  TriggerOnTouch(const char* label, MenuEntry *parentEntry) : MenuEntryCamTrigger(label, 0, parentEntry)
  {
    pinMode(13, OUTPUT);
    shutterOffTimer.setTime(0.5f);
    wipeDetection = false;
  }
  
  virtual void enter()
  {
    LCD.clear();
    LCD.setPosition(0,0);
    LCD.print("Touch Trigger");
    LCD.setPosition(0,1);
    LCD.print("Shutter: ");
    LCD.printAndStay("Off");
    Touchpad.setHandler(this);
  }
  
  virtual void upChanged(bool pressed)
  {
    if (pressed) {
      Menu.returnToMenu();
    }
  }
  
  virtual void downChanged(bool pressed)
  {}
  
  virtual void leftChanged(bool pressed)
  {}
  
  virtual void rightChanged(bool pressed)
  {}
  
  virtual void centerChanged(bool pressed)
  {
    if (pressed) {
      trigger();
    }
  }
  
protected:
  
  virtual void loop()
  {}
  
  virtual void triggered(bool on)
  {
    if (on) {
      LCD.clearEOL();
      LCD.printAndStay("On");
      digitalWrite(13, HIGH);
    } else {
      LCD.printAndStay("Off");
      digitalWrite(13, LOW);
    }
  }
};

#endif//_TRIGGER_ON_TOUCH_H_
