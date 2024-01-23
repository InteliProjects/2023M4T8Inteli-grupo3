// Define a guarda para evitar inclusões múltiplas do mesmo cabeçalho
#ifndef LCD_H
#define LCD_H

// Inclui a biblioteca para controle de displays LCD via I2C
#include <LiquidCrystal_I2C.h>

// Classe LCD para gerenciamento de um display LCD
class LCD
{
public:
  // Construtor da classe
  LCD();

  // Inicializa o display LCD
  void init();

  // Exibe uma mensagem em uma linha específica do LCD
  void displayLine(String message, int line);

  // Limpa o display LCD
  void clear();

  // Indica se o display LCD está disponível para uso
  bool isAvailable;

private:
  // Objeto LiquidCrystal_I2C para interagir com o LCD
  LiquidCrystal_I2C lcd;

  // Limpa uma linha específica do display
  void clearLCDLine(int line);
};

// Fim da definição de guarda
#endif
