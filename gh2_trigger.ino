#include <Wire.h>
#include <I2Cdev.h>
#include <MPR121.h>
#include <SoftwareSerial.h>

#include "LCD.h"
#include "Touchpad.h"
#include "Menu.h"

#include "TriggerOnTouch.h"

MenuEntry mnu_trigger("Trigger");
MenuEntry mnu_intervalometer("Intervalometer", &mnu_trigger);
MenuEntry mnu_wlan("WLAN", &mnu_intervalometer);

TriggerOnTouch mnu_trigger_touch("On touch", &mnu_trigger);


void setup()
{
  LCD.initialize(9600);
  Touchpad.initialize();
  Menu.initialize(&mnu_trigger);
  Touchpad.setHandler(&Menu);
}

void loop()
{
  Menu.update();
  if (!Menu.blockSystem()) {
   Touchpad.update();
  }
}
