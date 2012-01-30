
#ifndef _MENY_ENTRY_CAM_TRIGGER_H_
#define _MENY_ENTRY_CAM_TRIGGER_H_

#include "MenuEntry.h"
#include "TouchpadHandler.h"
#include "SoftTimer.h"
#include "ExtendedHandler.h"

#define PIN_SHUTTER 4

class MenuEntryCamTrigger : public MenuEntry, public ExtendedHandler
{
public:

  MenuEntryCamTrigger(const char* label);

  MenuEntryCamTrigger(const char* label, MenuEntry *prevEntry);

  /**
   * Create a menu entry and sets the prev item.
   * @param label The label which should be shown to the user.
   * @param prevEntry The new element will be set as next for the prev and the prev as previous for this.
   * @param subEntry The entry to which should be entered. 
   */
  MenuEntryCamTrigger(const char* label, MenuEntry *prevEntry, MenuEntry *parentEntry);
  

  virtual void update();
  
  virtual bool blocking();
protected:
  /**
   * Triggers the shutter for the given time.
   * @param time The time that the virual should be pressed in seocnds.
   */
  void trigger();
  void trigger(float seconds);
  virtual void loop() = 0;
  virtual void triggered(bool on) = 0;
  
  // Timer which deaktives the shutter.
  bool block;
  
  SoftTimer shutterOffTimer;
};
  

#endif//_MENY_ENTRY_CAM_TRIGGER_H_
