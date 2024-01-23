// Inclui o cabeçalho da classe LCD
#include "LCD.h"

// Construtor da classe LCD: inicializa o display com endereço I2C 0x27 e configura para 16 colunas e 2 linhas
LCD::LCD() : lcd(0x27, 16, 2)
{
  // Inicialmente, define o display como não disponível
  isAvailable = false;
}

// Método para inicializar o display LCD
void LCD::init()
{
  // Verifica se o display ainda não foi inicializado
  if (!isAvailable)
  {
    // Inicia a comunicação com o LCD, acende o backlight e limpa o display
    lcd.init();
    lcd.backlight();
    lcd.clear();

    // Marca o display como disponível
    isAvailable = true;

    // Exibe uma mensagem padrão
    lcd.print("Aguardando scans");
  }
}

// Método para exibir mensagens no display
void LCD::displayMessage(String line1, String line2)
{
  // Verifica se o display está disponível
  if (isAvailable)
  {
    // Limpa o display e exibe a primeira linha de mensagem
    lcd.clear();
    lcd.print(line1);

    // Move o cursor para a segunda linha e exibe a segunda mensagem
    lcd.setCursor(0, 1);
    lcd.print(line2);
  }
}
