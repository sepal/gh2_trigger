
#ifndef _SIMPLE_TIMER_H_
#define _SIMPLE_TIMER_H_

#include "LCD.h"
#include "Menu.h"
#include "Touchpad.h"
#include "MenuEntryCamTrigger.h"
#include "TimeSetAction.h"
#include "IntSetAction.h"

/**
 * An active menu entry which makes a certain amount of photos with certain time inbetween.
 */
class SimpleTimer : public MenuEntryCamTrigger
{
public:
  /**
   * Creates SimpleTimer menu entry with the given laben and parent entry.
   */
  SimpleTimer(const char* label, MenuEntry *parentEntry);
  
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
  
  /**
   * Overrides MenuEntryCamTrigger::saveData(bool on).
   */
  virtual void saveData();
  
  enum Actions
  {
    ACTION_TRIGGER,
    ACTION_DELAY,
    ACTION_GAP,
    ACTION_PHOTOS,
    ACTION_SAVE,
  };
  
  SoftTimer gapTimer;
  int photos;
  int photosMade;
  long delay;
 
  int position;
  int active;
  
  TimeSetAction delaySetAction;
  TimeSetAction gapSetAction;
  IntSetAction photosSetAction;
};

#endif//_SIMPLE_TIMER_H_
