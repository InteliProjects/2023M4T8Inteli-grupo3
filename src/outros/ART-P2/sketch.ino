// Inclui os cabeçalhos das classes compartilhadas e dos dispositivos
#include "shared.h"
#include "LCD.h"
#include "GPS.h"
#include "RFID.h"

// Define os pinos dos LEDs
#define ledSair 23
#define ledParar 25

// Variáveis globais para controlar o estado de trânsito
bool IN_TRANSIT = false;
bool LOCAL_IN_TRANSIT = false;

// Cria instâncias das classes LCD, GPS e RFID
LCD lcd;
GPS gps;
RFID sair(32, 33, true);
RFID parar(26, 27, false);

// Função para inicializar os dispositivos e configurar os pinos
void init()
{
  lcd.init();
  sair.init();
  parar.init();
  pinMode(ledSair, OUTPUT);
  pinMode(ledParar, OUTPUT);
}

// Função de delay que verifica mudanças no estado de trânsito
void awareDelay(int milliseconds, int checkInterval = 100)
{
  const bool old_state = IN_TRANSIT;

  for (int i = 0; i < milliseconds; i += checkInterval)
  {
    // Interrompe o delay se o estado de trânsito mudar
    if (IN_TRANSIT != old_state)
    {
      break;
    }
    delay(checkInterval);
    sair.check_scan();
    parar.check_scan();
  }
}

// Função setup, executada uma vez na inicialização
void setup()
{
  Serial.begin(9600);
  init();

  // Configura os LEDs e exibe a mensagem inicial no LCD
  digitalWrite(ledSair, LOW);
  digitalWrite(ledParar, HIGH);
  lcd.displayLine("Fora de transito...", 0);
  lcd.displayLine("Aperte um dos botoes", 1);
  lcd.displayLine("Para mudar o estado", 2);
  lcd.displayLine("Do ESP32", 3);
}

// Função loop, executada repetidamente após o setup
void loop()
{
  // Verifica o estado de trânsito e atualiza o LCD com as coordenadas GPS
  if (IN_TRANSIT)
  {
    if (gps.update())
    {
      float latitude = gps.getLatitude();
      float longitude = gps.getLongitude();
      String latitude_message = "Latitude: " + String(latitude);
      String longitude_message = "Longitude: " + String(longitude);
      lcd.displayLine(latitude_message, 2);
      lcd.displayLine(longitude_message, 3);
    }
    else
    {
      lcd.displayLine("GPS sem sinal", 1);
    }
    awareDelay(15000);
  }
  else
  {
    sair.check_scan();
    parar.check_scan();
    delay(100);
  }

  // Verifica mudanças no estado de trânsito e atualiza o LCD e os LEDs
  if (LOCAL_IN_TRANSIT != IN_TRANSIT)
  {
    LOCAL_IN_TRANSIT = IN_TRANSIT;
    if (IN_TRANSIT)
    {
      digitalWrite(ledSair, HIGH);
      digitalWrite(ledParar, LOW);
      lcd.clear();
      lcd.displayLine("Transf. completa", 0);
      delay(2000);
      lcd.displayLine("Em transito...", 0);
      lcd.displayLine("Localizacao Atual:", 1);
    }
    else
    {
      digitalWrite(ledSair, LOW);
      digitalWrite(ledParar, HIGH);
      lcd.displayLine("Fora de transito...", 0);
      lcd.displayLine("Ultima localizacao:", 1);
      delay(2000);
      lcd.displayLine("Transf. completa", 0);
      lcd.displayLine("", 1);
      lcd.displayLine("", 2);
      lcd.displayLine("", 3);
    }
  }
}
