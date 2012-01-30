#include <Wire.h>
#include <I2Cdev.h>
#include <MPR121.h>
#include <SoftwareSerial.h>

#include "LCD.h"
#include "Touchpad.h"
#include "Menu.h"

#include "TriggerOnTouch.h"
#include "SimpleTimer.h"

MenuEntry mnu_trigger("Trigger");
MenuEntry mnu_wlan("WLAN", &mnu_trigger);

//TriggerOnTouch mnu_trigger_touch("On touch", &mnu_trigger);
SimpleTimer mnu_trigger_simple_timer("Simple timer", &mnu_trigger);


void setup()
{
  LCD.initialize(9600);
  LCD.stopBlinkingBox();
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
