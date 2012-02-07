
#include "StorageHandler.h"
#include <EEPROM.h>

void StorageHandler::save(StorageAddresses address, const long value)
{
  union LongConversion data;
  data.l = value;
  saveBytes(address, data.buffer, 4);
}

void StorageHandler::save(StorageAddresses address, const int value)
{
  union IntConversion data;
  data.i = value;
  saveBytes(address, data.buffer, 2);
}


long StorageHandler::loadLong(StorageAddresses address)
{
  union LongConversion data;
  loadBytes(address, data.buffer, 4);
  return data.l;
}

int StorageHandler::loadInt(StorageAddresses address)
{
  union IntConversion data;
  loadBytes(address, data.buffer, 2);
  return data.i;
}

void StorageHandler::saveBytes(StorageAddresses address, unsigned char *byte, int length)
{
  for (int i=0; i < length; i++)
    EEPROM.write(address+i, byte[i]);
}

void StorageHandler::loadBytes(StorageAddresses address, unsigned char *byte, int length)
{
  for (int i=0; i < length; i++)
    byte[i] = EEPROM.read(address+i);
}

StorageHandler Storage;