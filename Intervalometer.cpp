
#include "Intervalometer.h"
#include "StorageHandler.h"

Intervalometer::Intervalometer(const char* label, MenuEntry *prevEntry) : MenuEntryCamTrigger(label, prevEntry, 0), 
  intervalSetAction("Intvl", this, Storage.loadLong(STORAGE_INTERVAL_INTERVAL)), 
  lengthSetAction("Length", this, Storage.loadLong(STORAGE_INTERVAL_LENGTH)), 
  exposureTime("Ex Tm", this, Storage.loadLong(STORAGE_INTERVAL_EXPOSURE))
{
  pinMode(13, OUTPUT);
  position = ACTION_START;
  active = false;
  wipeDetection = false;
  
  shutterOffTimer.setTime(exposureTime.getTime());
  intervalTimer.setTime(intervalSetAction.getTime());
  frames = INTERVALOMETER_FPS*lengthSetAction.getTime()/1000;
  framesMade = 0;
}

void Intervalometer::enter()
{
  LCD.clear();
  LCD.setPosition(0,0);
  LCD.print(label);
  switch (position) {
    case ACTION_START:
      LCD.setPosition(0,1);
      LCD.print("TL: [C] to start");
      break;
    case ACTION_INTERVAL:
      intervalSetAction.printStuff();
      break;
    case ACTION_LENGTH:
      lengthSetAction.printStuff();
      break;
    case ACTION_EXPOSURE:
      exposureTime.printStuff();
    case ACTION_SAVE:
        printSave();
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
      case ACTION_INTERVAL:
        LCD.setPosition(0,1);
        LCD.print("TL: [C] to start");
        position--;
        break;
      case ACTION_LENGTH:
        intervalSetAction.printStuff();
        position--;
        break;
      case ACTION_EXPOSURE:
        lengthSetAction.printStuff();
        position--;
        break;
      case ACTION_SAVE:
        exposureTime.printStuff();
        position--;
        break;
    }
  }
}

void Intervalometer::rightChanged(bool pressed)
{
  if (pressed && !active) {
    switch (position) {
      case ACTION_START :
        position++;
        intervalSetAction.printStuff();
        break;
      case ACTION_INTERVAL:
        position++;
        lengthSetAction.printStuff();
        break;
      case ACTION_LENGTH:
        position++;
        exposureTime.printStuff();
        break;
      case ACTION_EXPOSURE:
        position++;
        printSave();
        break;
    }
  }
}

void Intervalometer::centerChanged(bool pressed)
{
  if (pressed) {
    switch (position) {
      case ACTION_START:
        if (active) {
          LCD.setPosition(0,1);
          LCD.clearEOL();
          LCD.print("TL: [C] to start");
          intervalTimer.stop();
          active = false;
        } else {
          LCD.setPosition(0,1);
          LCD.clearEOL();
          LCD.print("TL:     ");
          LCD.printAndStay("00:00.00");
          intervalTimer.start();
          active = true;
          framesMade = 0;
        }
        break;
      case ACTION_INTERVAL:
        Touchpad.setHandler(&intervalSetAction);
        intervalSetAction.enter();
        break;
      case ACTION_LENGTH:
        Touchpad.setHandler(&lengthSetAction);
        lengthSetAction.enter();
        break;
      case ACTION_EXPOSURE:
        Touchpad.setHandler(&exposureTime);
        exposureTime.enter();
        break;
      case ACTION_SAVE:
        storeDefaults();
        break;
    }
  }
}

void Intervalometer::restoreHandler()
{
  Touchpad.setHandler(this);
  switch (position) {
    case ACTION_INTERVAL:
      dataModified();
      intervalTimer.setTime(intervalSetAction.getTime());
      break;
    case ACTION_LENGTH:
      dataModified();
      frames = INTERVALOMETER_FPS*lengthSetAction.getTime()/1000;
      break;
    case ACTION_EXPOSURE:
      dataModified();
      shutterOffTimer.setTime(exposureTime.getTime());
      break;
      
  }
}

void Intervalometer::loop()
{
  switch (position) {
    case ACTION_START:
      if (intervalTimer.ready()) {
        trigger();
      }
      break;
    case ACTION_INTERVAL:
      intervalSetAction.update();
      break;
    case ACTION_LENGTH:
      lengthSetAction.update();
      break;
    case ACTION_EXPOSURE:
      exposureTime.update();
      break;
  }
}

void Intervalometer::triggered(bool on)
{
  if (on) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
    framesMade++;
    if (framesMade >= frames && frames != 0) {
      intervalTimer.stop();
      LCD.setPosition(0,1);
      LCD.print("TL: [C] to start");
      active = false;
      framesMade = 0;
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

void Intervalometer::saveData()
{
  Storage.save(STORAGE_INTERVAL_INTERVAL, intervalSetAction.getTime());
  Storage.save(STORAGE_INTERVAL_LENGTH, lengthSetAction.getTime());
  Storage.save(STORAGE_INTERVAL_EXPOSURE, exposureTime.getTime());
}
