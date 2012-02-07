
#ifndef _INTERVALOMETER_H_
#define _INTERVALOMETER_H_

#include "LCD.h"
#include "Menu.h"
#include "Touchpad.h"
#include "MenuEntryCamTrigger.h"
#include "TimeSetAction.h"
#include "IntSetAction.h"

#define INTERVALOMETER_FPS 24

/**
 * An active menu entry which makes a certain amount of photos with certain time inbetween.
 */
class Intervalometer : public MenuEntryCamTrigger
{
public:
  /**
   * Creates SimpleTimer menu entry with the given laben and parent entry.
   */
  Intervalometer(const char* label, MenuEntry *parentEntry);
  
  /**
   * Overrides MenuEntry::enter().
   */
  virtual void enter();
  
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
   * Overrides ExtendedHandler::restoreHandler().
   */
  virtual void restoreHandler();
  
protected:
  /**
   *  Overrides MenuEntryCamTrigger::loop(). 
   */
  virtual void loop();
  
  /**
   * Overrides MenuEntryCamTrigger::triggered(bool on).
   */
  virtual void triggered(bool on);
  
  SoftTimer intervalTimer;
  long delay;
 
  int position;
  int active;
  long frames, framesMade;
  bool dataSaved;
  
  TimeSetAction intervalSetAction;
  TimeSetAction lengthSetAction;
  TimeSetAction exposureTime;;
  
};

#endif//_INTERVALOMETER_H_
