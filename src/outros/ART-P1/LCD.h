#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal_I2C.h>

class LCD
{
public:
  LCD();
  void init();
  void displayMessage(String line1, String line2);

private:
  LiquidCrystal_I2C lcd;
  bool isAvailable;
};
// Definição de guarda para evitar inclusões múltiplas do cabeçalho
#ifndef LCD_H
#define LCD_H

// Inclui a biblioteca para comunicação com displays LCD via I2C
#include <LiquidCrystal_I2C.h>

// Classe LCD para encapsular a funcionalidade do display LCD
class LCD
{
public:
  // Construtor padrão da classe
  LCD();

  // Inicializa o display LCD
  void init();

  // Exibe duas linhas de mensagem no display LCD
  void displayMessage(String line1, String line2);

private:
  // Objeto da biblioteca LiquidCrystal_I2C para interagir com o LCD
  LiquidCrystal_I2C lcd;

  // Flag para verificar se o display LCD está disponível para uso
  bool isAvailable;
};

// Fim da definição de guarda
#endif

#endif
