#ifndef _MENU_ENTRY_H_
#define _MENU_ENTRY_H_

#include "Arduino.h"


/*
 * This Menu system works essentially like a stack:
 * A MenuEntry can have a previous and a next entry. You start with a pointer to one 
 * between the entries by MenuEntry getting the pointer with next() or previous().
 * Parent- und sub-menus work essentially the same: with sub or parent() you can go 
 * up or down in the hirachy. The main difference to the horizontal approach is that,
 * when cicle left or right in your menu system, the parent entry will be passed to
 * new entry so that 
 * 1stly: You can always go up with out setting the parent entry for every sub menu.
 * 2ndly: When return to the submenu, you get menu you where last on.
 */


class MenuEntry
{
public:
  /**
   * Create a menu.
   * @param label The label which should be shown to the user.
   */
  MenuEntry(const char* label);

  MenuEntry(const char* label, MenuEntry *prevEntry);

  /**
   * Create a menu entry and sets the prev item.
   * @param label The label which should be shown to the user.
   * @param prevEntry The new element will be set as next for the prev and the prev as previous for this.
   * @param subEntry The entry to which should be entered. 
   */
  MenuEntry(const char* label, MenuEntry *prevEntry, MenuEntry *parentEntry);
  
  /**
   * Sets the previous element without manipulating the given parameter.
   * @param prev The element which should be set as previous element.
   */
  void setPrev(MenuEntry *prev);
  
  /**
   * Sets the next element without manipulating the given parameter.
   * @param prev The element which should be set as next element.
   */
  void setNext(MenuEntry *next);

  /**
   * Sets the parent element.
   */
  void setParent(MenuEntry *parent);

  /**
   * Sets the parent element.
   */
  void setSub(MenuEntry *sub);

  void setHorizontalCircle(MenuEntry *next);

  void setVerticalCircle(MenuEntry *parent);

  /**
   * Returns the previous element or if null the current.
   */
  MenuEntry* previous();

  /**
   * Returns the next element or if null the current.
   */
  MenuEntry* next();

  /**
   * Returns the element above.
   */
  MenuEntry* parent();


  /**
   * Returns the element below.
   */
  MenuEntry* sub();
  
  /**
   * Returns the label of the menu entry.
   */
  const char* getLabel();
  
  /**
   * Called when the menu system wants to pass the touchpad handling to the current menu entry.
   */
  virtual void enter() {}
  
  /**
   * Called when the menu entry is updatet(which is every loop iteration).
   */
  virtual void update() {}
  
  /**
   * If true, blocks the rest of the programm.
   */   
  virtual bool blocking() {return false;}
  
  /**
   * Should return true if enter is overriden, so that the menu handler knows it can call enter.
   */
  virtual bool hasActions() {return false;}

protected:
  const char* label;
  MenuEntry *subElement;
  MenuEntry *nextElement;
  MenuEntry *previousElement;
  MenuEntry *parentElement;
};
  

#endif//_MENU_ENTRY_H_
