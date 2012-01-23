#ifndef _TOUCHPAD_H_
#define _TOUCHPAD_H_

#include <Wire.h>
#include <I2Cdev.h>
#include <MPR121.h>
#include "Arduino.h"
#include "TouchpadHandler.h"

class TouchpadHandler
{
public:
  TouchpadHandler();
  
  void initialize();
  void update();
  void setHandler(TouchpadEventHandler* handler);
  
private:
  void checkWipes(bool centerState, byte padLeft, byte padRight);
  
  
  MPR121 mpr;
  TouchpadEventHandler* handler;
  int wipes;
  
  enum TOUCHPAD
  {
    TP_NORTH = 1,
    TP_EAST = 0,
    TP_SOUTH = 2,
    TP_WEST = 3,
    TP_CENTER = 4,
  };

  bool lastTouchState[NUM_CHANNELS];
  bool lastPressedTimer[NUM_CHANNELS];
};

extern TouchpadHandler Touchpad;
#endif//_TOUCHPAD_H_
