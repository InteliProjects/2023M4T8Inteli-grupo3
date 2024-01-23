// Inclui o cabeçalho compartilhado e o cabeçalho da classe RFID
#include "shared.h"
#include "RFID.h"

// Construtor da classe RFID: inicializa os pinos e a flag de inicialização
RFID::RFID(int entry_pin, int exit_pin, bool definidor_em_transito) : entryPin(entry_pin), exitPin(exit_pin), definidorEmTransito(definidor_em_transito), initialized(false) {}

// Método para inicializar os pinos
void RFID::init()
{
  // Se já foi inicializado, não faz nada
  if (!initialized)
  {
    // Configura os pinos para os modos apropriados
    pinMode(entryPin, INPUT_PULLUP);
    pinMode(exitPin, OUTPUT);

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

// Verifica a leitura do botão e ajusta o status de trânsito
void RFID::check_scan()
{
  // Se estiver inicializado e o botão foi pressionado
  if (initialized && read_button())
  {
    // Define o status de trânsito com base no flag
    IN_TRANSIT = definidorEmTransito;

    // Espera até que o botão seja liberado
    while (read_button())
    {
      delay(100);
    }
  }
}
