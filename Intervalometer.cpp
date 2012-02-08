
#include "Intervalometer.h"
#include "StorageHandler.h"

Intervalometer::Intervalometer(const char* label, MenuEntry *prevEntry) : MenuEntryCamTrigger(label, prevEntry, 0), 
  intervalSetAction("Intvl", this, Storage.loadLong(STORAGE_INTERVAL_INTERVAL)), 
  lengthSetAction("Length", this, Storage.loadLong(STORAGE_INTERVAL_LENGTH)), 
  exposureTime("Ex Tm", this, Storage.loadLong(STORAGE_INTERVAL_EXPOSURE))
{
  pinMode(13, OUTPUT);
  position = 0;
  active = false;
  wipeDetection = false;
  dataSaved = false;
  
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
      exposureTime.printStuff();
    case 4:
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
      case 1:
        LCD.setPosition(0,1);
        LCD.print("TL: [C] to start");
        position--;
        break;
      case 2:
        intervalSetAction.printStuff();
        position--;
        break;
      case 3:
        lengthSetAction.printStuff();
        position--;
        break;
      case 4:
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
      case 0 :
        position++;
        intervalSetAction.printStuff();
        break;
      case 1:
        position++;
        lengthSetAction.printStuff();
        break;
      case 2:
        position++;
        exposureTime.printStuff();
        break;
      case 3:
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
      case 0:
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
      case 1:
        Touchpad.setHandler(&intervalSetAction);
        intervalSetAction.enter();
        break;
      case 2:
        Touchpad.setHandler(&lengthSetAction);
        lengthSetAction.enter();
        break;
      case 3:
        Touchpad.setHandler(&exposureTime);
        exposureTime.enter();
        break;
    case 4:
      storeDefaults();
      break;
    }
  }
}

void Intervalometer::restoreHandler()
{
  Touchpad.setHandler(this);
  switch (position) {
    case 1:
      dataSaved = false;
      intervalTimer.setTime(intervalSetAction.getTime());
      break;
    case 2:
      dataSaved = false;
      frames = INTERVALOMETER_FPS*lengthSetAction.getTime()/1000;
      break;
    case 3:
      dataSaved = false;
      shutterOffTimer.setTime(exposureTime.getTime());
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
