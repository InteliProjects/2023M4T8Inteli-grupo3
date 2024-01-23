#include "RFID.h"
#include "ChoiceButton.h"
#include "shared.h"

RFID::RFID(int entry_pin, int exit_pin, ChoiceButton& confirm, ChoiceButton& deny) : entryPin(entry_pin), exitPin(exit_pin), yes(confirm), no(deny), initialized(false) {}


void RFID::init() {
  if (!initialized) {
    pinMode(entryPin, INPUT_PULLUP);
    pinMode(exitPin, OUTPUT);
    initialized = true;
  }
  return;
}


bool RFID::read_button() {
  if (!initialized) {
    return false;
  } else {
    return digitalRead(entryPin) == 0;
  }
}


bool RFID::block_until_done(int ammount_of_items) {
  int local_ammount_of_items = ammount_of_items;
  String initial_message = "Escaneie " + String(ammount_of_items) + " ativos";
  lcd.displayLine(initial_message, 0);
  lcd.displayLine("Para escanear ativos", 1);
  lcd.displayLine("Clique no botao", 2);
  lcd.displayLine("preto a direita", 3);
  while (local_ammount_of_items != 0) {
    // waits for scan to occur / own button to be presseed
    while (!read_button()) {
      delay(100);
    }

    // prompt to confirm
    String fake_rfid = generate_random_string(15);
    lcd.displayLine("Ativo escaneado", 1);
    String confirm_message = "RFID " + fake_rfid;
    lcd.displayLine(confirm_message, 2);
    lcd.displayLine("Confime abaixo...", 3);
    delay(1000);

    if (confirm_item()) { // this waits for any of the two confirm buttons to be pressed
      local_ammount_of_items -= 1;
      lcd.clear();
      lcd.displayLine("Ativo Confirmado!", 0);
      lcd.displayLine("Realizando upload...", 1);
      delay(2000);
      if (local_ammount_of_items == 0) {
        return true;
      }
      String message = "Falta(m) " + String(local_ammount_of_items) + "/" + String(ammount_of_items) + " iten(s)";
      lcd.displayLine(message, 0);
      lcd.displayLine("Para escanear ativos", 1);
      lcd.displayLine("Clique no botao", 2);
      lcd.displayLine("preto a direita", 3);
    } else {
      // edit lcd to scan again, dont change counter.
      lcd.clear();
      lcd.displayLine("Selecao cancelada...", 0);
      lcd.displayLine("Aguarde e realize", 1);
      lcd.displayLine("o escaneamento", 2);
      lcd.displayLine("novamente", 3);
      delay(2000);
      String message = "Falta(m) " + String(local_ammount_of_items) + "/" + String(ammount_of_items) + " iten(s)";
      lcd.displayLine(message, 0);
      lcd.displayLine("Para escanear ativos", 1);
      lcd.displayLine("Clique no botao", 2);
      lcd.displayLine("preto a direita", 3);
    }
  }
}

bool RFID::confirm_item() {
  bool yes_state = false;
  bool no_state = false;
  while (!yes_state && !no_state) {
    yes_state = yes.read_button();
    no_state = no.read_button();
    delay(100);
  }
  if (yes_state) {
    return true;
  } else {
    return false;
  }
} 


String RFID::generate_random_string(size_t length) {
  const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  String result = "";
  for (size_t i = 0; i < length; ++i) {
    int randomValue = random(0, sizeof(characters) - 1);
    result += characters[randomValue];
  }
  return result;
}