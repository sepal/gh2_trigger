
#include "MenuEntryCamTrigger.h"
#include "LCD.h"


MenuEntryCamTrigger::MenuEntryCamTrigger(const char* label) : MenuEntry(label)
{
  block = false;
  
}

MenuEntryCamTrigger::MenuEntryCamTrigger(const char* label, MenuEntry *prevEntry) : MenuEntry(label, prevEntry)
{
  block = false;
}

MenuEntryCamTrigger::MenuEntryCamTrigger(const char* label, MenuEntry *prevEntry, MenuEntry *parentEntry) : MenuEntry(label, prevEntry, parentEntry)
{
  block = false;
}

void MenuEntryCamTrigger::update()
{
  if (shutterOffTimer.ready()) {
    shutterOffTimer.stop();
    digitalWrite(PIN_SHUTTER, LOW);
    triggered(false);
    block = false;
  }
  loop();
}

bool MenuEntryCamTrigger::blocking()
{
  return block;
}

bool MenuEntryCamTrigger::hasActions()
{
  return true;
}

void MenuEntryCamTrigger::trigger()
{
  digitalWrite(PIN_SHUTTER, HIGH);
  shutterOffTimer.start();
  triggered(true);
  block = true;
}

void MenuEntryCamTrigger::trigger(float seconds)
{
  digitalWrite(PIN_SHUTTER, HIGH);
  shutterOffTimer.start(seconds);
  triggered(true);
  block = true;
}

void MenuEntryCamTrigger::printSave()
{
  LCD.setPosition(0,1);
  LCD.print((dataSaved) ? "Data is saved.  " : "Save as default?");
}
  
void MenuEntryCamTrigger::storeDefaults()
{
  if (!dataSaved)  {
    LCD.setPosition(0,1);
    LCD.printAndStay("Saving data...  ");
    saveData();
    LCD.printAndStay("Data is saved.  ");
    dataSaved = true;
  }
}

void MenuEntryCamTrigger::dataModified()
{
  dataSaved = false;
}