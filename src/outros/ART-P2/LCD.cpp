// Inclui o cabeçalho da classe LCD
#include "LCD.h"

// Construtor da classe LCD: inicializa o LCD com endereço I2C 0x27 e configuração 20x4
LCD::LCD() : lcd(0x27, 20, 4)
{
  // Inicialmente, define o display como não disponível
  isAvailable = false;
}

// Inicializa o display LCD
void LCD::init()
{
  // Inicia a comunicação com o LCD, acende o backlight e limpa o display
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Marca o display como disponível para uso
  isAvailable = true;
}

// Exibe uma mensagem em uma linha específica do LCD
void LCD::displayLine(String message, int line)
{
  // Limpa a linha antes de exibir a nova mensagem
  clearLCDLine(line);

  // Posiciona o cursor no início da linha e exibe a mensagem
  lcd.setCursor(0, line);
  lcd.print(message);
}

// Limpa uma linha específica do display
void LCD::clearLCDLine(int line)
{
  // Preenche a linha com espaços em branco
  for (int n = 0; n < 20; n++)
  {
    lcd.setCursor(n, line);
    lcd.print(" ");
  }
  // Retorna o cursor para o início da linha
  lcd.setCursor(0, line);
}

// Limpa todo o display LCD
void LCD::clear()
{
  lcd.clear();
}
