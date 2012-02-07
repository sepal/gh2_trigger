#ifndef _STORAGE_HANDLER_H_
#define _STORAGE_HANDLER_H_

#include "Arduino.h"

enum StorageAddresses
{
  // Reserve the first 16 bytes for other stuff.
  STORAGE_SIMPLE_TIMER_DELAY  = 0x10,
  STORAGE_SIMPLE_TIMER_GAP    = STORAGE_SIMPLE_TIMER_DELAY+4,
  STORAGE_SIMPLE_TIMER_PHOTOS = STORAGE_SIMPLE_TIMER_GAP+4,
  STORAGE_INTERVAL_INTERVAL   = STORAGE_SIMPLE_TIMER_PHOTOS+4,
  STORAGE_INTERVAL_LENGTH     = STORAGE_INTERVAL_INTERVAL+4,
  STORAGE_INTERVAL_EXPOSURE  = STORAGE_INTERVAL_LENGTH+4,
};

/**
 *
 */
class StorageHandler
{
public:
  void save(StorageAddresses address, const long value);
  
  void save(StorageAddresses address, const int value);
  
  long loadLong(StorageAddresses address);
  
  int loadInt(StorageAddresses address);
protected:
  void saveBytes(StorageAddresses address, unsigned char *byte, int length);
  void loadBytes(StorageAddresses address, unsigned char *byte, int length);
  
  byte dataLens[];

  union IntConversion
  {
    int i;
    unsigned char buffer[2];
  };

  union LongConversion
  {
    int l;
    unsigned char buffer[4];
  };
};

extern StorageHandler Storage;
#endif//_STORAGE_HANDLER_H_
