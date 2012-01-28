
#ifndef _SIMPLE_TIMER_H_
#define _SIMPLE_TIMER_H_

#include "LCD.h"
#include "Menu.h"
#include "Touchpad.h"
#include "MenuEntryCamTrigger.h"

class SimpleTimer : MenuEntryCamTrigger
{
public:
  SimpleTimer(const char* label, MenuEntry *parentEntry) : MenuEntryCamTrigger(label, 0, parentEntry)
  {
    pinMode(13, OUTPUT);
    shutterOffTimer.setTime(0.5);
    wipeDetection = false;
    started = false;
    minutes = 0;
    seconds = 0;
    photos = 0;
    setting = false;
  }
  
  virtual void enter()
  {
    Touchpad.setHandler(this);
    currentMode = MODE_DISPLAY_STATE;
    LCD.clear();
    LCD.setPosition(0,0);
    LCD.print("Simple Timer");
    LCD.setPosition(0,1);
    LCD.print("State: ");
    LCD.printAndStay("Off");
  }
  
  virtual void upChanged(bool pressed)
  {
  }
  
  virtual void downChanged(bool pressed)
  {
    if (pressed) {
      // Cancel the current set mode in which the user is.
      switch (currentMode)
      {
      case MODE_DISPLAY_DELAY:
        break;
      case MODE_DISPLAY_GAP:
        break;
      case MODE_DISPLAY_PHOTOS:
        break;
      }
      updateDisplay();
    }
  }
  
  virtual void leftChanged(bool pressed)
  {
    if (pressed && !started) {
      switch (currentMode)
      {
      case MODE_DISPLAY_DELAY:
      case MODE_DISPLAY_GAP:
      case MODE_DISPLAY_PHOTOS:
        currentMode--;
        updateDisplay();
        break;
      case MODE_SET_DELAY:
      case MODE_SET_GAP:
        if (setting) {
        } else {
        }
        break;
      case MODE_SET_PHOTOS:
        if (!setting) {
        }
        break;
      }
    }
  }
  
  virtual void rightChanged(bool pressed)
  {
    if (pressed && !started) {
      switch (currentMode)
      {
      case MODE_DISPLAY_STATE:
      case MODE_DISPLAY_DELAY:
      case MODE_DISPLAY_GAP:
        currentMode++;
        updateDisplay();
        break;
      case MODE_SET_DELAY:
      case MODE_SET_GAP:
        if (setting) {
        } else {
        }
        break;
      case MODE_SET_PHOTOS:
        if (!setting) {
        }
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
protected:
  void setCTime(long time)
  {
    cMinutes = time/60000;
    cSeconds = (time - cMinutes*60000)/1000;
    cMicro = (time - cSeconds*1000 - cMinutes*60000);
  }
  
  long getLongCTime()
  {
    return cMinutes * 60000 + cSeconds * 1000 + cMicro;
  }
  
  void updateTimeDisplay(long time)
  {
    int minutes = time/60000;
    int seconds = (time - minutes*60000)/1000;
    int micros = (time - seconds*1000 - minutes*60000);
    
    LCD.setPosition(7,1);
    LCD.printFormatedNumber(minutes, 10);
    LCD.print(":");
    LCD.printFormatedNumber(seconds, 10);
    LCD.print(".");
    LCD.printFormatedNumber(micros, 100);
  }
  
  void updateDisplay()
  {
      switch (currentMode)
      {
      case MODE_DISPLAY_STATE:
        LCD.setPosition(0,1);
        LCD.clearEOL();
        LCD.print("State: ");
        LCD.print("Off");
        break;
      case MODE_DISPLAY_DELAY:
      case MODE_SET_DELAY:
        LCD.setPosition(0,1);
        LCD.clearEOL();
        LCD.print("Delay:");
        updateTimeDisplay(delay.getTimeAsLong());
        break;
      case MODE_DISPLAY_GAP:
      case MODE_SET_GAP:
        LCD.setPosition(0,1);
        LCD.clearEOL();
        LCD.print("Gap:");
        updateTimeDisplay(gap.getTimeAsLong());
        break;
      case MODE_DISPLAY_PHOTOS:
      case MODE_SET_PHOTOS:
        LCD.setPosition(0,1);
        LCD.clearEOL();
        LCD.print("# of Pics: ");
        LCD.printFormatedNumber(photos, 10000);
        break;
      }
  }
  
  virtual void loop()
  {}
  
  virtual void triggered(bool on)
  {
    if (on) {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }
  }
  
  enum Mode
  {
    MODE_DISPLAY_STATE,
    MODE_DISPLAY_DELAY,
    MODE_DISPLAY_GAP,
    MODE_DISPLAY_PHOTOS,
    MODE_SET_DELAY,
    MODE_SET_GAP,
    MODE_SET_PHOTOS,
  };
  
  enum TimePos
  {
    TIMEPOS_MINUTES,
    TIMEPOS_SECONDS,
    TIMEPOS_MICRO,
  }
  
  Mode currentMode;
  TimePos timePos;
  
  bool started;
  SofTimer delay;
  SoftTimer gap;
  int photos;
  
  bool setting;
  // Temporal variables. Only if center was pressed, the settings will be set, pressing down, will cancel the operation and the original
  // states will be set.
  int cMinute, cSecond, cMicro, cPhotos;
};

#endif//_SIMPLE_TIMER_H_
