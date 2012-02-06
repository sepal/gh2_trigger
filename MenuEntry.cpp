#include "MenuEntry.h"

MenuEntry::MenuEntry(const char* label)
{
  this->label = label;
  this->previousElement = 0;
  this->nextElement = 0;
  this->subElement = 0;
  this->parentElement = 0;
}

MenuEntry::MenuEntry(const char* label, MenuEntry *prevEntry)
{
  this->label = label;
  this->previousElement = prevEntry;
  this->nextElement = 0;
  this->parentElement = 0;
  this->subElement = 0;

  if (previousElement) {
    previousElement->setNext(this);
  }
}

MenuEntry::MenuEntry(const char* label, MenuEntry *prevEntry, MenuEntry *parentEntry)
{
  this->label = label;
  this->previousElement = prevEntry;
  this->parentElement = parentEntry;
  this->subElement = 0;
  this->nextElement = 0;
  
  if (previousElement)
    previousElement->setNext(this);
  if (parentEntry)
    parentElement->setSub(this);
}


void MenuEntry::setPrev(MenuEntry *prev)
{
  this->previousElement = prev;
}

void MenuEntry::setNext(MenuEntry *next)
{
  this->nextElement = next;
}

void MenuEntry::setParent(MenuEntry *parent)
{
  this->parentElement = parent;
}

void MenuEntry::setSub(MenuEntry *sub)
{
  this->subElement = sub;
}

void MenuEntry::setHorizontalCircle(MenuEntry *next)
{
  this->setNext(next);
  next->setPrev(this);
}

void MenuEntry::setVerticalCircle(MenuEntry *parent)
{
  this->parentElement = parent;
  parent->setSub(this);
}

MenuEntry* MenuEntry::previous()
{
  // Pass the parent to the returned element, so that you easily can go up in the hierarchy.
  if (this->parentElement && nextElement)
    previousElement->setParent(this->parentElement);
  
  return this->previousElement == 0 ? this : this->previousElement;
}

MenuEntry* MenuEntry::next()
{
  // Pass the parent to the returned element, so that you easily can go up in the hierarchy.
  if (this->parentElement && nextElement)
    nextElement->setParent(this->parentElement);
  
  return this->nextElement == 0 ? this : this->nextElement;
}

MenuEntry* MenuEntry::parent()
{
  if (this->parentElement) {
    this->parentElement->setSub(this);
    return this->parentElement;
  }
  return this;
}

MenuEntry* MenuEntry::sub()
{
  return this->subElement == 0 ? this : this->subElement;
}

const char* MenuEntry::getLabel()
{
  return this->label;
}
