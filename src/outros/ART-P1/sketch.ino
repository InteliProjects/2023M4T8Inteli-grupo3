// Inclui os cabeçalhos das classes RFID e LCD
#include "RFID.h"
#include "LCD.h"

// Cria instâncias das classes RFID e LCD com os pinos especificados
RFID rfid_1(32, 33, 25); // RFID 1 com pinos de entrada, saída e LED
RFID rfid_2(26, 27, 17); // RFID 2 com pinos de entrada, saída e LED
LCD lcd;                 // Instância da classe LCD

// Função para inicializar os dispositivos
void init()
{
  // Inicializa o LCD e os dispositivos RFID
  lcd.init();
  rfid_1.init();
  rfid_2.init();
}

// Função setup, chamada uma vez na inicialização do Arduino
void setup()
{
  // Inicia a comunicação serial com a taxa de 9600 bps
  Serial.begin(9600);

  // Chama a função init para inicializar os dispositivos
  init();
}

// Função loop, chamada repetidamente após a inicialização
void loop()
{
  // Verifica se há algum scan no RFID 1
  String rfid_result_1 = rfid_1.check_scan();

  // Verifica se há algum scan no RFID 2
  String rfid_result_2 = rfid_2.check_scan();

  // Se um scan foi detectado no RFID 1, exibe no LCD
  if (rfid_result_1 != "")
  {
    lcd.displayMessage("RFID_1 scan:", rfid_result_1);
  }

  // Se um scan foi detectado no RFID 2, exibe no LCD
  if (rfid_result_2 != "")
  {
    lcd.displayMessage("RFID_2 scan:", rfid_result_2);
  }

  // Breve pausa para estabilização do loop
  delay(50);
}
