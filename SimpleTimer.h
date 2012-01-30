
#ifndef _SIMPLE_TIMER_H_
#define _SIMPLE_TIMER_H_

#include "LCD.h"
#include "Menu.h"
#include "Touchpad.h"
#include "MenuEntryCamTrigger.h"
#include "TimeSetter.h"


class SimpleTimer : public MenuEntryCamTrigger
{
public:
  SimpleTimer(const char* label, MenuEntry *parentEntry) : MenuEntryCamTrigger(label, 0, parentEntry), delaySetter("Delay", 3000, this), gapSetter("Gap", 10000, this)
  {
    pinMode(13, OUTPUT);
    shutterOffTimer.setTime(0.5f);
    wipeDetection = false;
    photos = 5;
    gapTimer.setTime(10.0f);
    delay = 3;
  }
  
  virtual void enter()
  {
    LCD.clear();
    LCD.setPosition(0,0);
    LCD.print("Touch Trigger");
    LCD.setPosition(0,1);
    LCD.print("Shutter: ");
    LCD.printAndStay("Off");
    position = 0;
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
          Touchpad.setHandler(&delaySetter);
          delaySetter.enter();
          break;
        case 2:
          Touchpad.setHandler(&gapSetter);
          gapSetter.enter();
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
          delaySetter.printStuff();
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
          delaySetter.printStuff();
          position++;
          break;
        case 1:
          position++;
          gapSetter.printStuff();
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
        delay = delaySetter.getTime();
        break;
      case 2:
        gapTimer.setTime(gapSetter.getTime());
        break;
    }
  }
  
protected:
  virtual void loop()
  {
    switch (position) {
      case 1:
        delaySetter.loop();
        break;
      case 2:
        delaySetter.loop();
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
  
  TimeSetter delaySetter;
  TimeSetter gapSetter;
};

#endif//_SIMPLE_TIMER_H_
