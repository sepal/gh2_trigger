
#include "MenuEntryCamTrigger.h"


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
