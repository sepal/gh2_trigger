
#include "Intervalometer.h"

Intervalometer::Intervalometer(const char* label, MenuEntry *prevEntry) : MenuEntryCamTrigger(label, prevEntry, 0), intervalSetAction("Intvl", this, 10000), lengthSetAction("Length", this, 900000), exposuresSetAction("Exposures", this, 1)
{
  pinMode(13, OUTPUT);
  shutterOffTimer.setTime(0.1f);
  wipeDetection = false;
  intervalTimer.setTime(intervalSetAction.getTime());
  delay = delaySetAction.getTime();
  position = 0;
  photosMade = 0;
  active = false;
}

void Intervalometer::enter()
{
  LCD.clear();
  LCD.setPosition(0,0);
  LCD.print(label);
  switch (position) {
    case 0:
      LCD.setPosition(0,1);
      LCD.print("TL: [C] to start");
      break;
    case 1:
      intervalSetAction.printStuff();
      break;
    case 2:
      lengthSetAction.printStuff();
      break;
    case 3:
      exposuresSetAction.printStuff();
      break;
  }
  Touchpad.setHandler(this);
}

void Intervalometer::upChanged(bool pressed)
{
  if (pressed && !active) {
    Menu.returnToMenu();
  }
}

void Intervalometer::downChanged(bool pressed)
{
}

void Intervalometer::leftChanged(bool pressed)
{
  if (pressed && !active) {
    switch (position) {
      case 1:
        LCD.setPosition(0,1);
        LCD.print("TL: [C] to start");
        position--;
        break;
      case 2:
        lengthSetAction.printStuff();
        position--;
        break;
      case 3:
        intervalSetAction.printStuff();
        position--;
        break;
    }
  }
}

void Intervalometer::rightChanged(bool pressed)
{
  if (pressed && !active) {
    switch (position) {
      case 0 :
        delaySetAction.printStuff();
        position++;
        break;
      case 1:
        position++;
        lengthSetAction.printStuff();
        break;
      case 2:
        position++;
        exposuresSetAction.printStuff();
        break;
    }
  }
}

void Intervalometer::centerChanged(bool pressed)
{
  if (pressed) {
    switch (position) {
      case 0:
        if (active) {
          LCD.setPosition(0,1);
          LCD.clearEOL();
          LCD.print("TL: [C] to start");
          LCD.printAndStay("Off");
          intervalTimer.stop();
          active = false;
        } else {
          LCD.setPosition(0,1);
          LCD.clearEOL();
          LCD.print("TL:     ");
          LCD.printAndStay("00:00.00");
          intervalTimer.start();
          active = true;
        }
        break;
      case 1:
        Touchpad.setHandler(&delaySetAction);
        delaySetAction.enter();
        break;
      case 2:
        Touchpad.setHandler(&lengthSetAction);
        lengthSetAction.enter();
        break;
      case 3:
        Touchpad.setHandler(&exposuresSetAction);
        exposuresSetAction.enter();
        break;
    }
  }
}

void Intervalometer::restoreHandler()
{
  Touchpad.setHandler(this);
  switch (position) {
    case 1:
      intervalTimer.setTime(intervalSetAction.getTime());
      break;
    case 2:
      frames = INTERVALOMETER_FPS*lengthSetAction.getTimeAsLong()/1000;
      break;
  }
}

void Intervalometer::loop()
{
  switch (position) {
    case 0:
      if (intervalTimer.ready()) {
        trigger();
      }
      break;
    case 1:
      intervalSetAction.update();
      break;
    case 2:
      lengthSetAction.update();
      break;
    case 3:
      exposuresSetAction.update();
      break;
  }
}

void Intervalometer::triggered(bool on)
{
  if (on) {
    digitalWrite(13, HIGH);
  } else {
    exposuresMade++;
    if (exposuresMade < exposuresSetAction.getValue()) {
      trigger();
    } else {
      framesMade++;
      exposuresMade = 0;
      if (framesMade >= frames && frames != 0) {
        intervalTimer.stop();
        LCD.setPosition(0,1);
        LCD.print("TL: [C] to start");
        active = false;
      } else {
        int framesCalc = (frames == 0) ? framesMade : (frames-framesMade);

        int seconds = framesCalc/INTERVALOMETER_FPS;
        int frame = framesCalc - (INTERVALOMETER_FPS*seconds);
        int minutes = seconds/60;
        seconds -= (60*minutes);
        
        LCD.setPosition(8, 1);
        LCD.printFormatedNumber(minutes, 10);
        LCD.print(':');
        LCD.printFormatedNumber(seconds, 10);
        LCD.print('.');
        LCD.printFormatedNumber(frame, 10);
      }
    }
  }
}