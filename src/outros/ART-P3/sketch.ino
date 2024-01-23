#include "shared.h"
#include "StartButton.h"
#include "RFID.h"
#include "ChoiceButton.h"

LCD lcd;
ChoiceButton confirmar(25, 26, true);
ChoiceButton cancelar(27, 14, false);
RFID escanear(32, 33, confirmar, cancelar);
StartButton iniciar(16, 17, escanear);

void init() {
  lcd.init();
  cancelar.init();
  confirmar.init();
  escanear.init();
  iniciar.init();
}

void setup() {
  init();
}

void loop() {
  // put your main code here, to run repeatedly:
  bool status = iniciar.loop_once();
  delay(100); // this speeds up the simulation
}
