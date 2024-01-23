// Define a guarda para evitar inclusão múltipla do cabeçalho
#ifndef GPS_H
#define GPS_H

// Inclui o cabeçalho da classe LCD
#include "LCD.h"

// Classe GPS para simular a funcionalidade de um módulo GPS
class GPS
{
public:
  // Construtor: inicializa o objeto GPS
  GPS();

  // Atualiza as coordenadas GPS com valores aleatórios
  bool update();

  // Retorna a latitude atual
  float getLatitude();

  // Retorna a longitude atual
  float getLongitude();

private:
  // Armazena a latitude atual
  float latitude;

  // Armazena a longitude atual
  float longitude;

  // Flag para verificar se os dados GPS estão disponíveis
  bool isAvailable;

  // Gera uma latitude aleatória
  float generate_random_latitude();

  // Gera uma longitude aleatória
  float generate_random_longitude();

  // Instância da classe LCD (não utilizada neste contexto)
  LCD lcd;
};

// Fim da definição de guarda
#endif
