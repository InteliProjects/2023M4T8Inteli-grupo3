#include "StartButton.h"
#include "shared.h"

StartButton::StartButton(int entry_pin, int exit_pin, RFID& scan_button) : entryPin(entry_pin), exitPin(exit_pin), scanButton(scan_button), initialized(false) {}


void StartButton::init() {
  if (!initialized) {
    pinMode(entryPin, INPUT_PULLUP);
    pinMode(exitPin, OUTPUT);
    initialized = true;
  }
  return;
}


bool StartButton::read_button() {
  if (!initialized) {
    return false;
  } else {
    return digitalRead(entryPin) == 0;
  }
}


bool StartButton::loop_once() {
  while (!initialized) {
    delay(100);
  }

  int items_to_scan = random(1, 6);

  // waits for the button to be pressed
  lcd.displayLine("Para iniciar, aperte", 0);
  lcd.displayLine("o botao azul.", 1);

  while (!read_button()) {
    delay(100);
  }

  lcd.displayLine("Incializando...", 0);
  lcd.displayLine("", 1);

  delay(2000);

  // starts a RFID internal loop
  bool scan_phase_status = scanButton.block_until_done(items_to_scan);

  // edit the lcd with smth ig
  if (scan_phase_status == true) {
    lcd.displayLine("Ativos escaneados!", 0);
    lcd.displayLine("Aperte o botao azul", 1);
    lcd.displayLine("novamente para", 2);
    lcd.displayLine("encerrar a sessao", 3);

    // waits for self to be pressed again (this is to end the thingamajik)
    while (!read_button()) {
      delay(100);
    }

    lcd.clear();
    lcd.displayLine("Sessao encerrada,", 0);
    lcd.displayLine("muito obrigadx!", 1);

    delay(2000);

    return true;
  }
}