
#include "Menu.h"
#include "LCD.h"
#include "Touchpad.h"

MenuSystem::MenuSystem()
{
  wipeDetection = false;
}

void MenuSystem::initialize(MenuEntry* startEntry)
{
  this->current = startEntry;
  updateDisplay();
}

void MenuSystem::upChanged(bool pressed)
{
  if (pressed) {
    this->current = current->parent();
    LCD.clear();
    LCD.setPosition(0,0);
    updateDisplay();
  }
}

void MenuSystem::downChanged(bool pressed)
{
  if (pressed) {
    if (current != current->sub()) {
      this->current = current->sub();
      LCD.setPosition(0,1);
      LCD.print('-');
      updateDisplay();
    }
  }
}

void MenuSystem::leftChanged(bool pressed)
{
  if (pressed) {
    this->current = current->previous();
    updateDisplay();
  }
}

void MenuSystem::rightChanged(bool pressed)
{
  if (pressed) {
    this->current = current->next();
    updateDisplay();
  }
}

void MenuSystem::centerChanged(bool pressed)
{
  if (pressed) {
    current->enter();
  }
}

void MenuSystem::update()
{
    current->update();
}

bool MenuSystem::blockSystem()
{
    return current->blocking();
}

void MenuSystem::returnToMenu()
{
  LCD.clear();
  LCD.setPosition(0,0);
  LCD.print(current->parent()->getLabel());
  LCD.setPosition(1,1);
  updateDisplay();
  Touchpad.setHandler(this);
}

void MenuSystem::updateDisplay()
{
  LCD.clearEOL();
  LCD.printAndStay(current->getLabel());
}

MenuSystem Menu; 
