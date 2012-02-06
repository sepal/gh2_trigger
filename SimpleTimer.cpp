
#include "SimpleTimer.h"

SimpleTimer::SimpleTimer(const char* label, MenuEntry *parentEntry) : MenuEntryCamTrigger(label, 0, parentEntry), delaySetAction("Delay", this, 1000), gapSetAction("Gap", this, 3000), photosSetAction("Pictures", this, 5)
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
  LCD.print("Touch Trigger");
  switch (position) {
    case 0:
      LCD.setPosition(0,1);
      LCD.print("Timer: ");
      LCD.printAndStay("Off");
      break;
    case 1:
      delaySetAction.printStuff();
      break;
    case 2:
      gapSetAction.printStuff();
      break;
    case 3:
      photosSetAction.printStuff();
      break;
  }
  Touchpad.setHandler(this);
}

void SimpleTimer::upChanged(bool pressed)
{}

void SimpleTimer::downChanged(bool pressed)
{
  if (pressed) {
    switch (position) {
      case 0:
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
      case 1:
        Touchpad.setHandler(&delaySetAction);
        delaySetAction.enter();
        break;
      case 2:
        Touchpad.setHandler(&gapSetAction);
        gapSetAction.enter();
        break;
      case 3:
        Touchpad.setHandler(&photosSetAction);
        photosSetAction.enter();
        break;
    }
  }
}

void SimpleTimer::leftChanged(bool pressed)
{
  if (pressed && !active) {
    switch (position) {
      case 1:
        LCD.setPosition(0,1);
        LCD.clearEOL();
        LCD.print("Shutter: ");
        LCD.printAndStay("Off");
        position--;
        break;
      case 2:
        delaySetAction.printStuff();
        position--;
        break;
      case 3:
        gapSetAction.printStuff();
        position--;
        break;
    }
  }
}

void SimpleTimer::rightChanged(bool pressed)
{
  if (pressed && !active) {
    switch (position) {
      case 0 :
        delaySetAction.printStuff();
        position++;
        break;
      case 1:
        position++;
        gapSetAction.printStuff();
        break;
      case 2:
        position++;
        photosSetAction.printStuff();
        break;
    }
  }
}

void SimpleTimer::centerChanged(bool pressed)
{
  if (pressed && !active) {
    Menu.returnToMenu();
  }
}
void SimpleTimer::restoreHandler()
{
  Touchpad.setHandler(this);
  switch (position) {
    case 1:
      delay = delaySetAction.getTime();
      break;
    case 2:
      gapTimer.setTime(gapSetAction.getTime());
    case 3:
      photos = photosSetAction.getValue();
      break;
  }
}

void SimpleTimer::loop()
{
  switch (position) {
    case 0:
      if (gapTimer.ready()) {
        gapTimer.stop();
        trigger();
      }
      break;
    case 1:
      delaySetAction.update();
      break;
    case 2:
      gapSetAction.update();
      break;
    case 3:
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
    if (photosMade <= photos || photos == 0) {
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
