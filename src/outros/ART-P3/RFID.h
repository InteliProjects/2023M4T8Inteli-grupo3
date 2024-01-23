#ifndef RFID_H
#define RFID_H

#include <Arduino.h> // for String and other Arduino functionalities
#include "ChoiceButton.h"
#include "LCD.h"

class RFID {
public:
  RFID(int entry_pin, int exit_pin, ChoiceButton& confirm, ChoiceButton& deny);
  void init();
  void check_scan();
  bool block_until_done(int ammount_of_items);

private:
  int entryPin;
  int exitPin;
  bool initialized = false; 
  bool read_button();
  ChoiceButton& yes;
  ChoiceButton& no;
  bool confirm_item();
  String generate_random_string(size_t length);
};

#endif
