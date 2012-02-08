
#ifndef _MENY_ENTRY_CAM_TRIGGER_H_
#define _MENY_ENTRY_CAM_TRIGGER_H_

#include "MenuEntry.h"
#include "TouchpadHandler.h"
#include "SoftTimer.h"
#include "ExtendedHandler.h"

#define PIN_SHUTTER 4

/**
 * Abstract class for menu entries that trigger the shutter.
 * The class will pull the resistance low and after a certain time(determand by the shutterOffTimer
 * time) pull it high again.
 */
class MenuEntryCamTrigger : public MenuEntry, public ExtendedHandler
{
public:
  /**
   * Create a menu entry and sets the prev item.
   * @param label The label which should be shown to the user.
   */
  MenuEntryCamTrigger(const char* label);

  /**
   * Create a menu entry and sets the prev item.
   * @param label The label which should be shown to the user.
   * @param prevEntry The new element will be set as next for the prev and the prev as previous for this.
   */
  MenuEntryCamTrigger(const char* label, MenuEntry *prevEntry);

  /**
   * Create a menu entry and sets the prev item.
   * @param label The label which should be shown to the user.
   * @param prevEntry The new element will be set as next for the prev and the prev as previous for this.
   * @param subEntry The entry to which should be entered. 
   */
  MenuEntryCamTrigger(const char* label, MenuEntry *prevEntry, MenuEntry *parentEntry);
  
  /**
   * Updates shutterOffTimer and calls loop().
   */
  virtual void update();
  
  /**
   * Tells the menu system to block the system.
   */
  virtual bool blocking();
  
  /**
   * Overrides MenuEntry::hasAction()
   */
  virtual bool hasActions();
protected:
  /**
   * Triggers the shutter for the given time.
   */
  void trigger();
  
  /**
   * Triggers the shutter for the given time.
   * @param time The time that the virual should be pressed in seocnds.
   */
  void trigger(float seconds);

  /**
   * Called in every loop iteration. 
   */
  virtual void loop() = 0;

  /**
   * Called when the resistors are pulled high or low.
   */
  virtual void triggered(bool on) = 0;
  
  /**
   * Prints the save action label.
   */
  void printSave();
  
  /**
   * Children classes should use this function to store data.
   */
  virtual void saveData() {}
  
  /**
   * Actual function which should be called to save data as default, which will then call saveData() 
   * and print stuff to the LCD.
   */
   virtual void storeDefaults();
  
  
  /**
   * Tell the class that data was modified and can know be stored.
   */
   void dataModified();
   
  // Timer which deaktives the shutter.
  bool block;
  bool dataSaved;
  
  SoftTimer shutterOffTimer;
};
  

#endif//_MENY_ENTRY_CAM_TRIGGER_H_
