
#include "MenuAction.h"

MenuAction::MenuAction(const char* label, ExtendedHandler* parentHandler)
{
  this->parentHandler = parentHandler;
  this->label = label;
  wipeDetection = false;
}

virtual void MenuAction::update()
{
  if (inputTimer.ready()) {
    updateInput();
  }
}

virtual void MenuAction::centerChanged(bool pressed)
{
  if (pressed) {
    LCD.stopBlinkingBox();
    parentHandler->restoreHandler();
  }
}