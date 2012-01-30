
#ifndef _SIMPLE_TIMER_H_
#define _SIMPLE_TIMER_H_

#include "LCD.h"
#include "Menu.h"
#include "Touchpad.h"
#include "MenuEntryCamTrigger.h"
#include "TimeSetAction.h"


class SimpleTimer : public MenuEntryCamTrigger
{
public:
  SimpleTimer(const char* label, MenuEntry *parentEntry) : MenuEntryCamTrigger(label, 0, parentEntry), delaySetAction("Delay", 3000, this), gapSetAction("Gap", 10000, this)
  {
    pinMode(13, OUTPUT);
    shutterOffTimer.setTime(0.5f);
    wipeDetection = false;
    photos = 5;
    gapTimer.setTime(10.0f);
    delay = 3;
    position = 0;
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
  {}
  
  virtual void downChanged(bool pressed)
  {
    if (pressed) {
      switch (position) {
        case 0:
          break;
        case 1:
          Touchpad.setHandler(&delaySetAction);
          delaySetAction.enter();
          break;
        case 2:
          Touchpad.setHandler(&gapSetAction);
          gapSetAction.enter();
          break;
      }
    }
  }
  
  virtual void leftChanged(bool pressed)
  {
    if (pressed) {
      switch (position) {
        case 1:
          LCD.setPosition(0,1);
          LCD.clearEOL();
          LCD.print("Shutter: ");
          LCD.printAndStay("Off");
          position--;
          break;
        case 2:
          delaySetAction.printStuff();
          position--;
          break;
      }
    }
  }
  
  virtual void rightChanged(bool pressed)
  {
    if (pressed) {
      switch (position) {
        case 0 :
          delaySetAction.printStuff();
          position++;
          break;
        case 1:
          position++;
          gapSetAction.printStuff();
          break;
        case 2:
          break;
      }
    }
  }
  
  virtual void centerChanged(bool pressed)
  {
    if (pressed) {
      Menu.returnToMenu();
    }
  }
  
  virtual void restoreHandler() {
    Touchpad.setHandler(this);
    switch (position) {
      case 1:
        delay = delaySetAction.getTime();
        break;
      case 2:
        gapTimer.setTime(gapSetAction.getTime());
        break;
    }
  }
  
protected:
  virtual void loop()
  {
    switch (position) {
      case 1:
        delaySetAction.update();
        break;
      case 2:
        delaySetAction.update();
        break;
    }
  }
  
  virtual void triggered(bool on)
  {
    if (on) {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }
  }
  
  SoftTimer gapTimer;
  int photos;
  long delay;
 
  int position;
  
  TimeSetAction delaySetAction;
  TimeSetAction gapSetAction;
};

#endif//_SIMPLE_TIMER_H_
