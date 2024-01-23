// Define a guarda para evitar inclusão múltipla do cabeçalho
#ifndef RFID_H
#define RFID_H

// Inclui funcionalidades básicas do Arduino
#include <Arduino.h>

// Classe RFID para gerenciar a interação com um leitor de RFID
class RFID
{
public:
  // Construtor: inicializa com os pinos de entrada, saída e um flag para definir se está em trânsito
  RFID(int entry_pin, int exit_pin, bool definidor_em_transito);

  // Inicializa os pinos configurados
  void init();

  // Verifica se o botão foi pressionado
  void check_scan();

private:
  // Pinos para entrada e saída
  int entryPin;
  int exitPin;

  // Flag para definir se o objeto está em trânsito
  bool definidorEmTransito;

  // Flag para verificar se a classe foi inicializada
  bool initialized = false;

  // Método privado para ler o estado do botão
  bool read_button();
};

// Fim da definição de guarda
#endif
