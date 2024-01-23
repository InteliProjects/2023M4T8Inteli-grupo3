#include "ChoiceButton.h"
#include "shared.h"

ChoiceButton::ChoiceButton(int entry_pin, int exit_pin, bool Choice) : entryPin(entry_pin), exitPin(exit_pin), choice(Choice), initialized(false) {}


void ChoiceButton::init() {
  if (!initialized) {
    pinMode(entryPin, INPUT_PULLUP);
    pinMode(exitPin, OUTPUT);
    initialized = true;
  }
  return;
}


bool ChoiceButton::read_button() {
  if (!initialized) {
    return false;
  } else {
    return digitalRead(entryPin) == 0;
  }
}