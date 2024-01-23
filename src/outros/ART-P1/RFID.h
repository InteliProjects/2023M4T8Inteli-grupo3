#ifndef RFID_H
#define RFID_H

#include <Arduino.h> // for String and other Arduino functionalities

class RFID {
public:
  RFID(int entry_pin, int exit_pin, int confirm_led);
  void init();
  String check_scan();

private:
  int entryPin;
  int exitPin;
  int confirmLed;
  bool initialized = false; 
  bool read_button();
  String generate_random_string(size_t length);
  void flash_led();
};

#endif
