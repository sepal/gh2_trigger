
#include "MenuAction.h"

MenuAction::MenuAction(const char* label, ExtendedHandler* parentHandler)
{
  this->parentHandler = parentHandler;
  this->label = label;
  wipeDetection = false;
}

void MenuAction::update()
{
  if (inputTimer.ready()) {
    updateInput();
  }
}

void MenuAction::centerChanged(bool pressed)
{
  if (pressed) {
    LCD.stopBlinkingBox();
    parentHandler->restoreHandler();
  }
}
