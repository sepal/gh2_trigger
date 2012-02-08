
#include "SimpleTimer.h"
#include "StorageHandler.h"

SimpleTimer::SimpleTimer(const char* label, MenuEntry *parentEntry) : 
  MenuEntryCamTrigger(label, 0, parentEntry),
  delaySetAction("Delay", this, Storage.loadLong(STORAGE_SIMPLE_TIMER_DELAY)),
  gapSetAction("Gap", this, Storage.loadLong(STORAGE_SIMPLE_TIMER_GAP)),
  photosSetAction("Pictures", this, Storage.loadLong(STORAGE_SIMPLE_TIMER_PHOTOS))
{
  pinMode(13, OUTPUT);
  shutterOffTimer.setTime(0.5f);
  wipeDetection = false;
  photos = photosSetAction.getValue();
  gapTimer.setTime(gapSetAction.getTime());
  delay = delaySetAction.getTime();
  position = 0;
  photosMade = 0;
  active = false;
}

void SimpleTimer::enter()
{
  LCD.clear();
  LCD.setPosition(0,0);
  LCD.print(label);
  switch (position) {
    case ACTION_TRIGGER:
      LCD.setPosition(0,1);
      LCD.print("Timer: ");
      LCD.printAndStay("Off");
      break;
    case ACTION_DELAY:
      delaySetAction.printStuff();
      break;
    case ACTION_GAP:
      gapSetAction.printStuff();
      break;
    case ACTION_PHOTOS:
      photosSetAction.printStuff();
      break;
    case ACTION_SAVE:
      printSave();
      break;
  }
  Touchpad.setHandler(this);
}

void SimpleTimer::upChanged(bool pressed)
{
  if (pressed && !active) {
    Menu.returnToMenu();
  }
}

void SimpleTimer::downChanged(bool pressed)
{
}

void SimpleTimer::leftChanged(bool pressed)
{
  if (pressed && !active) {
    switch (position) {
      case ACTION_DELAY:
        LCD.setPosition(0,1);
        LCD.clearEOL();
        LCD.print("Timer: ");
        LCD.printAndStay("Off");
        position--;
        break;
      case ACTION_GAP:
        delaySetAction.printStuff();
        position--;
        break;
      case ACTION_PHOTOS:
        gapSetAction.printStuff();
        position--;
        break;
      case ACTION_SAVE:
        photosSetAction.printStuff();
        position--;
        break;
    }
  }
}

void SimpleTimer::rightChanged(bool pressed)
{
  if (pressed && !active) {
    switch (position) {
      case ACTION_TRIGGER :
        delaySetAction.printStuff();
        position++;
        break;
      case ACTION_DELAY:
        position++;
        gapSetAction.printStuff();
        break;
      case ACTION_GAP:
        position++;
        photosSetAction.printStuff();
        break;
      case ACTION_PHOTOS:
        position++;
        printSave();
        break;
    }
  }
}

void SimpleTimer::centerChanged(bool pressed)
{
  if (pressed) {
    switch (position) {
      case ACTION_TRIGGER:
        if (active) {
          LCD.setPosition(0,1);
          LCD.clearEOL();
          LCD.print("Timer: ");
          LCD.printAndStay("Off");
          gapTimer.stop();
          active = false;
        } else {
          LCD.setPosition(0,1);
          LCD.clearEOL();
          LCD.print("Timer: ");
          LCD.printAndStay("On");
          gapTimer.startWithDelay(delay);
          active = true;
        }
        break;
      case ACTION_DELAY:
        Touchpad.setHandler(&delaySetAction);
        delaySetAction.enter();
        break;
      case ACTION_GAP:
        Touchpad.setHandler(&gapSetAction);
        gapSetAction.enter();
        break;
      case ACTION_PHOTOS:
        Touchpad.setHandler(&photosSetAction);
        photosSetAction.enter();
        break;
      case ACTION_SAVE:
        storeDefaults();
        break;
    }
  }
}

void SimpleTimer::restoreHandler()
{
  Touchpad.setHandler(this);
  switch (position) {
    case ACTION_DELAY:
      dataModified();
      delay = delaySetAction.getTime();
      break;
    case ACTION_GAP:
      dataModified();
      gapTimer.setTime(gapSetAction.getTime());
    case ACTION_PHOTOS:
      dataModified();
      photos = photosSetAction.getValue();
      break;
  }
}

void SimpleTimer::loop()
{
  switch (position) {
    case ACTION_TRIGGER:
      if (gapTimer.ready()) {
        gapTimer.stop();
        trigger();
      }
      break;
    case ACTION_DELAY:
      delaySetAction.update();
      break;
    case ACTION_GAP:
      gapSetAction.update();
      break;
    case ACTION_PHOTOS:
      photosSetAction.update();
      break;
  }
}

void SimpleTimer::triggered(bool on)
{
  if (on) {
    digitalWrite(13, HIGH);
  } else {
    photosMade++;
    if (photosMade < photos || photos == 0) {
      digitalWrite(13, LOW);
      gapTimer.start();
    } else {
      photosMade = 0;
      LCD.setPosition(0,1);
      LCD.print("Timer: ");
      LCD.printAndStay("Off");
      active = false;
    }
  }
}

void SimpleTimer::saveData()
{
  Storage.save(STORAGE_SIMPLE_TIMER_DELAY, delaySetAction.getTime());
  Storage.save(STORAGE_SIMPLE_TIMER_GAP, gapSetAction.getTime());
  Storage.save(STORAGE_SIMPLE_TIMER_PHOTOS, photosSetAction.getValue());
}
