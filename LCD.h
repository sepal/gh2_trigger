
#ifndef _LCD_H_
#define _LCD_H_

#include "Arduino.h";
#include <SoftwareSerial.h>

class LCDHandler
{
public:
  LCDHandler();

  void initialize(SoftwareSerial *serial);
  
  void clear();
  
  void clearCurrentLine();
  
  void print(String s);
  void print(char c);
  
  /**
   * Prints something and moves the cursor to the previous position
   */
  void printAndStay(String s);
  
  /**
   * Sets the cursor.
   * @param pos A value between 0 and 15 representing the horizontal position.
   * @param line A value between 0 and 1 representing the line position.
   */
  void setPosition(byte pos, byte line);
  
  void moveRight();
  
  void moveLeft();
  
  void scrollRight();
  
  void scrollLeft();
  
  void startBlinking();
  
  void stopBlinking();
  
  /**
   * Sets backlight brightness of display.
   * @param brightness A value between 0(off) and 29(full).
   */
  void setBrightness(byte brightness);
protected:
  SoftwareSerial *serial;
  byte pos;
  byte line;
};

extern LCDHandler LCD;

#endif//_LCD_H_
