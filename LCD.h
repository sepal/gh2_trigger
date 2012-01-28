
#ifndef _LCD_H_
#define _LCD_H_

#include "Arduino.h";
#include <SoftwareSerial.h>

#define LCD_PIN_RX 8
#define LCD_PIN_TX 9

/**
 * Handles the communication to a Sparkfun Serial Enabled 16x2 LCD via a software serial line.
 */
class LCDHandler
{
public:
  /**
   * Constructor which also initializes SoftwaresSerial object.
   * @param pinRX Reading pin which is not used.
   * @param pinTX The output pin connected to the display.
   */
  LCDHandler(byte pinRX, byte pinTX);

  /**
   * Initializes and clears the display and sets the position to 0,0.
   * @param baudRate The baudRate on which the lcd runs.
   */
  void initialize(int baudRate);
  
  /**
   * Clears the whole display.
   */
  void clear();
  
  /**
   * Clears the display from the current position until the end of line(by printing spaces).
   */
  void clearEOL();
  
  /**
   * Prints a string.
   * @param str The String which should be printed.
   */
  void print(String str);
  
  /**
   * Prints a character.
   * @param c The character which should be printed.
   */
  void print(char c);
  
  /**
   * Prints the number with a given number of zeros infront (like 03 or 0050).
   * @param number The number to be prented.
   * @param digitRepresenter A 10 based number which reprepesents how many digits you 
   *    want to print(eg. 10 while print one zero + the number, 100 will print 00 + number and so on).
   */
  void printFormatedNumber(int number, int digitRepresenter);
  
  /**
   * Prints the number with a given number of chararacters infront (like P3 or XX5X).
   * @param number The number to be prented.
   * @param digitRepresenter A 10 based number which reprepesents how many digits you 
   *    want to print(eg. 10 while print one zero + the number, 100 will print 00 + number and so on).
   * @param character The character to be printed infront the number.
   */
  void printFormatedNumber(int number, int digitRepresenter, int character);
  
  /**
   * Prints a string and moves the cursor back to the previous position.
   */
  void printAndStay(String s);
  
  /**
   * Sets the cursor.
   * @param pos A value between 0 and 15 representing the horizontal position.
   * @param line A value between 0 and 1 representing the line position.
   */
  void setPosition(byte pos, byte line);
  
  /**
   * Moves the cursor to right by one.
   */
  void moveRight();
  
  /**
   * Moves the cursor to left by one.
   */
  void moveLeft();
  
  /**
   * Scroll text to the right.
   */
  void scrollRight();
  
  /**
   * Scroll text to the left.
   */
  void scrollLeft();
  
  /**
   * Start the blinking cursor box.
   */
  void startBlinkingBox();
  
  /**
   * Stops the blinking cursor box.
   */
  void stopBlinkingBox();
  
  /**
   * Sets backlight brightness of display.
   * @param brightness A value between 0(off) and 29(full).
   */
  void setBrightness(byte brightness);
protected:

  SoftwareSerial serial;
  byte pos;
  byte line;
};

extern LCDHandler LCD;

#endif//_LCD_H_
