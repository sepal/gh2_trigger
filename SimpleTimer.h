
#ifndef _SIMPLE_TIMER_H_
#define _SIMPLE_TIMER_H_

#include "LCD.h"
#include "Menu.h"
#include "Touchpad.h"
#include "MenuEntryCamTrigger.h"
#include "TimeSetAction.h"
#include "IntSetAction.h"


class SimpleTimer : public MenuEntryCamTrigger
{
public:
  SimpleTimer(const char* label, MenuEntry *parentEntry) : MenuEntryCamTrigger(label, 0, parentEntry), delaySetAction("Delay", this, 1000), gapSetAction("Gap", this, 3000), photosSetAction("Pictures", this, 5)
  {
    pinMode(13, OUTPUT);
    shutterOffTimer.setTime(0.5f);
    wipeDetection = false;
    photos = 5;
    gapTimer.setTime(gapSetAction.getTime());
    delay = delaySetAction.getTime();
    position = 0;
  }
  
  virtual void enter()
  {
    LCD.clear();
    LCD.setPosition(0,0);
    LCD.print("Touch Trigger");
    switch (position) {
      case 0:
        LCD.setPosition(0,1);
        LCD.print("Timer: ");
        LCD.printAndStay("Off");
        break;
      case 1:
        delaySetAction.printStuff();
        break;
      case 2:
        gapSetAction.printStuff();
        break;
      case 3:
        photosSetAction.printStuff();
        break;
    }
    Touchpad.setHandler(this);
  }
  
  virtual void upChanged(bool pressed)
  {}
  
  virtual void downChanged(bool pressed)
  {
    if (pressed) {
      switch (position) {
        case 0:
          if (gapTimer.isStarted()) {
            LCD.setPosition(0,1);
            LCD.clearEOL();
            LCD.print("Timer: ");
            LCD.printAndStay("Off");
            gapTimer.stop();
          } else {
            LCD.setPosition(0,1);
            LCD.clearEOL();
            LCD.print("Timer: ");
            LCD.printAndStay("On");
            gapTimer.startWithDelay(delay);
          }
          break;
        case 1:
          Touchpad.setHandler(&delaySetAction);
          delaySetAction.enter();
          break;
        case 2:
          Touchpad.setHandler(&gapSetAction);
          gapSetAction.enter();
          break;
        case 3:
          Touchpad.setHandler(&photosSetAction);
          photosSetAction.enter();
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
        case 3:
          gapSetAction.printStuff();
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
          position++;
          photosSetAction.printStuff();
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
      case 3:
        photos = photosSetAction.getValue();
        break;
    }
  }
  
protected:
  virtual void loop()
  {
    switch (position) {
      case 0:
        if (gapTimer.isStarted()) {
          Serial.println(gapTimer.until());
        }
        if (gapTimer.ready()) {
          gapTimer.stop();
          trigger();
        }
        break;
      case 1:
        delaySetAction.update();
        break;
      case 2:
        gapSetAction.update();
        break;
      case 3:
        photosSetAction.update();
        break;
    }
  }
  
  virtual void triggered(bool on)
  {
    if (on) {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
      gapTimer.start();
    }
  }
  
  SoftTimer gapTimer;
  int photos;
  long delay;
 
  int position;
  
  TimeSetAction delaySetAction;
  TimeSetAction gapSetAction;
  IntSetAction photosSetAction;
};

#endif//_SIMPLE_TIMER_H_
