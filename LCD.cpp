
#include "LCD.h"

LCDHandler::LCDHandler(byte pinRX, byte pinTX) : serial(pinRX, pinTX)
{
  pos = 0;
  line = 0;
}

void LCDHandler::initialize(int baudRate)
{
  serial.begin(baudRate);
  clear();
  setBrightness(29);
  delay(500);
}


void LCDHandler::clear()
{
  serial.write(254); 
  serial.write(1);
}

void LCDHandler::clearEOL()
{
  String s = "";
  for (int i=0; i<16-pos; i++)
    s += " ";
  printAndStay(s);
}
  
void LCDHandler::print(String s)
{
  serial.print(s);
  pos += s.length();
}
  
void LCDHandler::print(char c)
{
  serial.print(c);
  pos++;
}

void LCDHandler::printFormatedNumber(int number, int digitRepresenter)
{
  for (int i=digitRepresenter; i>number+1; i=i/10) {
    print('0');
  }
  print(String(number));
}

void LCDHandler::printFormatedNumber(int number, int digitRepresenter, int character)
{
  for (int i=digitRepresenter; i>number+1; i=i/10) {
    print(character);
  }
  print(String(number));
}

void LCDHandler::printAndStay(String s)
{
  serial.print(s);
  setPosition(pos, line);
}

void LCDHandler::setPosition(byte pos, byte line)
{
  serial.write(254);
  this->pos = pos;
  this->line = (line > 1 ? 1 : line);
  serial.write(128 + pos + (64 * this->line ));
}

void LCDHandler::moveRight()
{
  serial.write(254);
  serial.write(0x14);
}

void LCDHandler::moveLeft()
{
  serial.write(254);
  serial.write(0x10);
  
}

void LCDHandler::scrollRight()
{
  serial.write(254);
  serial.write(0x1C);
}

void LCDHandler::scrollLeft()
{
  serial.write(254);
  serial.write(0x18);
}

void LCDHandler::startBlinkingBox()
{
  serial.write(254);
  serial.write(0x0D);
}

void LCDHandler::stopBlinkingBox()
{
  serial.write(254);
  serial.write(0x0C);
}

void LCDHandler::setBrightness(byte brightness)
{      
  serial.write(124);
  serial.write(128+brightness);
}

byte LCDHandler::getPosition()
{
  return pos;
}

LCDHandler LCD(LCD_PIN_RX, LCD_PIN_TX);
