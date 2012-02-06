#ifndef _TOUCHPAD_H_
#define _TOUCHPAD_H_

#include <Wire.h>
#include <I2Cdev.h>
#include <MPR121.h>
#include "Arduino.h"
#include "TouchpadHandler.h"

/**
 * Handles all the stuff which has to todo with the touchpad and relays the events to a 
 * TouchpadEventHandler object.
 * This class uses the i2cdev(https://github.com/jrowberg/i2cdevlib) and especially the mpr121 lib.
 */
class TouchpadHandler
{
public:
  /**
   * Initializes the variables.
   */
  TouchpadHandler();
  
  /**
   * Initializes the mpr object.
   */
  void initialize();
  
  /**
   * Updates the mpr121 and the touchpad event handler.
   */
  void update();
  
  /**
   * Sets the currrent touchpad event handler which should receive touch events.
   */
  void setHandler(TouchpadEventHandler* handler);
  
private:
  /**
   * Checks if there was a wipe from one pad to another
   */
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
