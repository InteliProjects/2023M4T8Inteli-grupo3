// Inclui o cabeçalho da classe RFID
#include "RFID.h"

// Construtor da classe RFID: inicializa os pinos e a flag de inicialização
RFID::RFID(int entry_pin, int exit_pin, int confirm_led) : entryPin(entry_pin), exitPin(exit_pin), confirmLed(confirm_led), initialized(false) {}

// Método para inicializar os pinos
void RFID::init()
{
  // Se já foi inicializado, não faz nada
  if (initialized)
  {
    return;
  }
  else
  {
    // Configura os pinos para os modos apropriados
    pinMode(entryPin, INPUT_PULLUP);
    pinMode(exitPin, OUTPUT);
    pinMode(confirmLed, OUTPUT);

    // Marca como inicializado
    initialized = true;
  }
}

// Lê o estado do botão de entrada
bool RFID::read_button()
{
  // Se não estiver inicializado, retorna falso
  if (!initialized)
  {
    return false;
  }
  else
  {
    // Retorna verdadeiro se o botão estiver pressionado
    return digitalRead(entryPin) == 0;
  }
}

// Verifica a leitura do botão e, se pressionado, retorna uma string aleatória
String RFID::check_scan()
{
  // Se não estiver inicializado, retorna string vazia
  if (!initialized)
  {
    return "";
  }
  else
  {
    // Se o botão foi pressionado
    if (read_button())
    {
      // Aciona o LED de confirmação
      flash_led();

      // Espera até que o botão seja liberado
      while (read_button())
      {
        delay(100);
      }

      // Retorna uma string aleatória de 15 caracteres
      return generate_random_string(15);
    }
    else
    {
      return "";
    }
  }
}

// Gera uma string aleatória de um comprimento especificado
String RFID::generate_random_string(size_t length)
{
  // Caracteres possíveis para a string aleatória
  const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  String result = "";

  // Constrói a string caractere por caractere
  for (size_t i = 0; i < length; ++i)
  {
    int randomValue = random(0, sizeof(characters) - 1);
    result += characters[randomValue];
  }
  return result;
}

// Método para acionar o LED de confirmação
void RFID::flash_led()
{
  // Se estiver inicializado, acende e apaga o LED
  if (initialized)
  {
    digitalWrite(confirmLed, HIGH);
    delay(500);
    digitalWrite(confirmLed, LOW);
  }
}
