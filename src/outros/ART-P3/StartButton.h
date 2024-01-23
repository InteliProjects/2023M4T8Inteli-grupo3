#ifndef StartButton_H
#define StartButton_H

#include "RFID.h"
#include "LCD.h"

class StartButton {
public:
  StartButton(int entry_pin, int exit_pin, RFID& scan_button);
  void init();
  void check_scan();
  bool loop_once();

private:
  int entryPin;
  int exitPin;
  bool initialized = false; 
  bool read_button();
  RFID& scanButton;
};

#endif
