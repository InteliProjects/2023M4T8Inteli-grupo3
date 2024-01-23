#ifndef ChoiceButton_H
#define ChoiceButton_H

#include "LCD.h"

class ChoiceButton {
public:
  ChoiceButton(int entry_pin, int exit_pin, bool Choice);
  void init();
  void check_scan();
  bool choice;
  bool read_button();

private:
  int entryPin;
  int exitPin;
  bool initialized = false;
};

#endif
