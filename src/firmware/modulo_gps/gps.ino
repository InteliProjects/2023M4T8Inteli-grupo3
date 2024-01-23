// Inclusão de bibliotecas necessárias para o funcionamento do código.
#include <TinyGPSPlus.h> // Biblioteca para o GPS

// Instanciação de objetos
TinyGPSPlus gps; // Objeto para o GPS

// Função de configuração do Arduino.
void setup() {
  Serial.begin(9600); // Iniciando a porta serial
  Serial2.begin(9600); // Iniciando a porta serial 2
  delay(3000); // Delay de 3 segundos
}


// Função de loop do Arduino.
void loop() {
  // Enquanto o Serial2 estiver disponível (o GPS estiver enviando dados), o código será executado.
  while (Serial2.available() > 0)
    // Se o GPS estiver enviando dados válidos:
    if (gps.encode(Serial2.read()))
      // Realiza o display das informações do GPS (chama a função displayInfo).
      displayInfo();

  // Se passou 5 segundos e o GPS não enviou dados válidos, algo está errado.
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    //se nao ha resposta/pede para checar a fiação
    Serial.println(F("No GPS detected: check wiring."));
    while (true); // Fica em loop infinito até que o problema seja resolvido.
  }
}


// Função para mostrar as informações extraídas pelo GPS.
void displayInfo() {
  //  Função para mostrar cada uma das infos vindas do gps
  Serial.print(F("Location: "));
  if (gps.location.isValid()){ // Se a localização for válida, printa a latitude e longitude
    Serial.print("Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print("Lng: ");
    Serial.print(gps.location.lng(), 6);
    Serial.println();
  } else { // Caso contrário, printa invalid
    Serial.print(F("INVALID"));
  }
}

// Função para atualizar a porta serial (Nao esta sendo usada por enquanto)
void updateSerial() {
  delay(500); // Delay de 500ms para evitar sobrecarga
  while (Serial.available()) { // Enquanto a porta serial estiver disponível
    Serial2.write(Serial.read()); // Realiza a leitura da porta serial e escreve na porta serial 2
  }

  while (Serial2.available()) { // Enquanto a porta serial 2 estiver disponível
    Serial.write(Serial2.read()); // Realiza a leitura da porta serial 2 e escreve na porta serial
  }
}