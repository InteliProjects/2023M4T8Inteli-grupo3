// Inclusão de bibliotecas necessárias para o funcionamento do código.
#include <SPI.h>               // SPI para comunicação serial.
#include <MFRC522.h>           // Biblioteca para o módulo RFID MFRC522.
#include <WiFi.h>              // Biblioteca para conectar o ESP32 à rede Wi-Fi.
#include <PubSubClient.h>      // Biblioteca para comunicação com o MQTT.
#include <HTTPClient.h>        // Biblioteca para realizar requisições HTTP.
#include <Wire.h>              // Biblioteca para o display LCD.
#include <LiquidCrystal_I2C.h> // Biblioteca para o display LCD.
#include <ArduinoJson.h>       // Biblioteca para manipulação de JSON.
#include <vector>              // Biblioteca para manipulação de vetores.
#include <iostream>            // Biblioteca para entrada e saída de dados.
#include <typeinfo>            // Biblioteca para obter informações de tipo em tempo de execução.
#include <map>                 // Biblioteca para manipulação de mapas (associação chave-valor).
#include <string>              // Biblioteca para manipulação de strings.

// Criação e configuração do display LCD.
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definições de constantes para a conexão Wi-Fi.
#define WIFI_SSID "nome da sua rede"                           // Substitua pelo nome do seu Wi-Fi.
#define WIFI_PASSWORD "senha da sua rede"                      // Substitua pela senha do seu Wi-Fi.
const char *mqttIP = "IP do seu Broker MQTT";                  // Substitua pelo seu IP do Broker MQTT.
int mqttPort = 1883;                                           // Substitua pela sua porta do Broker MQTT.
const char *mqttUser = "nome do seu usuário";                  // Substitua pelo seu usuário do Broker MQTT.
const char *mqttPassword = "senha do seu Broker MQTT";         // Substitua pela senha do seu Broker MQTT.
const char *topicoMQTT = "nome do tópico do Broker MQTT";      // Substitua pelo nome do seu tópico usado no Broker MQTT.
int leitor_id = 1;                                             // ID do leitor.
String receivedBoardFullName;                                  // Nome completo do dispositivo recebido.

String receivedMessage; // Mensagem recebida.

// Inicialização do módulo RFID.
MFRC522 rfid; // Objeto para manipulação do módulo RFID.

// Definição da classe BUTTON para gerenciamento de botões.
class BUTTON
{
public:
  static bool globalState; // Variável estática global para estado do botão.
  int currentState;        // Estado atual do botão físico.
  // Construtor para definir o pino e configurar como entrada.
  BUTTON(int pin) : pin(pin), lastButtonState(true)
  {
    pinMode(pin, INPUT_PULLUP); // Configura o pino como entrada com resistor de pull-up.
  }

  // Verifica se o botão foi pressionado e atualiza o estado.
  void checkButton()
  {
    // Leia o estado atual do botão físico.
    currentState = digitalRead(pin);

    // Verifica se o botão foi pressionado.
    if (currentState == LOW && !lastButtonState)
    {
      // Inverte o estado global.
      // Aguarde até que o botão seja solto.
      while (digitalRead(pin) == LOW)
      {
        vTaskDelay(pdMS_TO_TICKS(100)); // Aguarda 100 ms.
      }
    }

    // Atualiza o último estado do botão.
    lastButtonState = (currentState == LOW);
  }

  // Aguarda até que o botão seja solto e retorna um sinal.
  void GlobalButton()
  {
    // Leia o estado atual do botão físico.
    currentState = digitalRead(pin);

    // Verifica se o botão foi pressionado.
    if (currentState == LOW && !lastButtonState)
    {
      // Inverte o estado global.
      toggleState();
      // Aguarde até que o botão seja solto.
      while (digitalRead(pin) == LOW)
      {
        vTaskDelay(pdMS_TO_TICKS(100)); // Aguarda 100 ms.
      }
    }

    // Atualiza o último estado do botão.
    lastButtonState = (currentState == LOW);
  }

  // Função para alternar o estado do botão.
  void toggleState()
  {
    // Inverte o estado global.
    globalState = !globalState;
  }

private:
  bool lastButtonState; // Estado do botão na iteração anterior.
  int pin;              // Pino ao qual o botão está conectado.
};

// Definição da classe LED para gerenciamento de LEDs.
class LED
{
public:
  // Construtor para definir o pino e configurar como saída.
  LED(int pin) : pin(pin)
  {
    pinMode(pin, OUTPUT); // Configura o pino como saída.
  }
  // Métodos para controlar o LED: ligar, desligar e piscar.
  void on()
  {
    digitalWrite(pin, HIGH); // Liga o LED.
  }
  void off()
  {
    digitalWrite(pin, LOW); // Desliga o LED.
  }
  void blink()
  {
    // Pisca o LED 4 vezes com um intervalo de 200ms entre cada piscada de duração 200ms.
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(pin, LOW);
      vTaskDelay(pdMS_TO_TICKS(200)); // Aguarda 200 ms.
      digitalWrite(pin, HIGH);
      vTaskDelay(pdMS_TO_TICKS(200)); // Aguarda 200 ms.
    }
  }

private:
  // Variável privada para armazenar o pino do LED.
  int pin;
};

// Definição da classe WifiManager para gerenciar a conexão Wi-Fi.
class WifiManager
{
public:
  // Construtor para inicializar com o SSID e a senha.
  WifiManager(const char *ssid, const char *password) : ssid(ssid), password(password) {}

  // Método para iniciar a conexão Wi-Fi.
  void begin()
  {
    // Inicializa a conexão Wi-Fi.
    WiFi.begin(ssid, password);
    lcd.clear(); // Limpa a LCD.
    while (WiFi.status() != WL_CONNECTED)
    {                                  // Aguarda a conexão Wi-Fi ser estabelecida, imprimindo na LCD o status da conexão.
      vTaskDelay(pdMS_TO_TICKS(1000)); // Aguarda 1 segundo.
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Conectando");
      lcd.setCursor(0, 1);
      lcd.print("ao WiFi");
    }
    // Limpa a LCD quando a conexão Wi-Fi for estabelecida.
    lcd.clear();
  }

  // Método para obter um objeto WiFiClient.
  WiFiClient getWiFiClient()
  {
    return WiFiClient();
  }

private:
  // Variáveis privadas para armazenar o SSID e a senha.
  const char *ssid;
  const char *password;
};

// Definição da classe RFIDManager para gerenciar o módulo RFID.
// Classe para gerenciar operações RFID.
class RFIDManager
{
public:
  // Construtor para inicializar com a referência do objeto MFRC522.
  RFIDManager(MFRC522 &rfidModule) : rfid(rfidModule) {}
  std::vector<String> rfidList;

  // Método para inicializar o módulo RFID.
  void init()
  {
    // Inicializa o módulo RFID.
    SPI.begin();
    rfid.PCD_Init();
    // Limpa a LCD e imprime a mensagem de aguardando cartão RFID para o Serial e LCD, indicando que o módulo RFID está pronto para leitura.
    lcd.clear();
    lcd.print(" Aguardando...");
  }
  // Método para ler o ID do cartão RFID.
  String readRFID()
  {
    MFRC522::MIFARE_Key key;         // Cria uma chave para autenticação.
    byte nuidPICC[4] = {0, 0, 0, 0}; // Cria um buffer para armazenar o ID do cartão RFID.

    // Para cada byte da chave, define o valor como 0xFF.
    for (byte i = 0; i < 6; i++)
    {
      key.keyByte[i] = 0xFF;
    }

    if (!rfid.PICC_IsNewCardPresent())
      return ""; // Verifica se há um cartão RFID próximo ao módulo RFID.
    if (!rfid.PICC_ReadCardSerial())
      return ""; // Verifica se o cartão RFID foi lido corretamente.

    // Para cada byte do ID do cartão RFID, armazena no buffer.
    for (byte i = 0; i < 4; i++)
    {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }

    return printDec(nuidPICC, 4); // Retorna o ID do cartão RFID como string.
  }
  // Método para escrever dados no cartão RFID.
  void writeRFID(String data, LED success, LED fail)
  {
    MFRC522::MIFARE_Key key;         // Cria uma chave para autenticação.
    byte nuidPICC[4] = {0, 0, 0, 0}; // Cria um buffer para armazenar o ID do cartão RFID.

    // Para cada byte da chave, define o valor como 0xFF.
    for (byte i = 0; i < 6; i++)
    {
      key.keyByte[i] = 0xFF;
    }
    if (!rfid.PICC_IsNewCardPresent())
      return;                      // Verifica se há um cartão RFID próximo ao módulo RFID.
    Serial.println("primeiro IF"); // Prints para debug.
    if (!rfid.PICC_ReadCardSerial())
      return;                     // Verifica se o cartão RFID foi lido corretamente.
    Serial.println("segundo IF"); // Prints para debug.

    // Para cada byte do ID do cartão RFID, armazena no buffer.
    for (byte i = 0; i < 4; i++)
    {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }

    // Autenticação do cartão para acesso de escrita.
    MFRC522::StatusCode status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(rfid.uid));
    if (status != MFRC522::STATUS_OK)
    { // Verifica se a autenticação foi bem sucedida.
      Serial.print("Falha na autenticação para escrita: ");
      Serial.println(rfid.GetStatusCodeName(status)); // Imprime o status da autenticação no Serial.
      fail.blink();                                   // Pisca o LED vermelho para indicar falha na autenticação.
      return;
    }
    // Escrita de dados no cartão.
    status = rfid.MIFARE_Write(1, (byte *)data.c_str(), data.length());
    if (status != MFRC522::STATUS_OK)
    { // Verifica se a escrita foi bem sucedida.
      Serial.print("Falha na escrita do bloco: ");
      Serial.println(rfid.GetStatusCodeName(status)); // Imprime o status da escrita no Serial.
      fail.blink();                                   // Pisca o LED vermelho para indicar falha na escrita.
      return;
    }
    else
    { // Caso a escrita tenha sido bem sucedida.
      Serial.println("Dados escritos com sucesso no bloco");
      success.blink(); // Pisca o LED verde para indicar sucesso na escrita.
      return;
    }
  }
  // Método para converter o buffer de bytes em uma string.
  String printDec(byte *buffer, byte bufferSize)
  {
    String id = "";
    for (byte i = 0; i < bufferSize; i++)
    {
      id += String(buffer[i], DEC);
    }
    return id;
  }

  void addToRFIDList(String id)
  {
    // Adiciona o ID à lista.
    rfidList.push_back(id);

    // Imprime o ID adicionado para fins de debug (opcional).
    Serial.print("ID adicionado à lista: ");
    Serial.println(id);
    // Serial.println(rfidList[0]);
  }

private:
  // Variável privada para armazenar a referência do objeto MFRC522.
  MFRC522 &rfid;
};

// Classe para gerenciar a conexão com o MQTT e operações relacionadas a RFID.
class PostgresManager
{
public:
  // Variáveis para configuração da conexão MQTT.
  const char *mqttIP;
  int mqttPort;
  const char *mqttUser;
  const char *mqttPassword;

  // Referências para o gerenciamento de RFID e Wi-Fi.
  RFIDManager &rfidManager;
  WifiManager &wifiManager;

  // Cliente para conexão Wi-Fi e MQTT.
  WiFiClient wifiClient;
  PubSubClient mqttClient;

  // Construtor da classe.
  PostgresManager(const char *mqttIP, int mqttPort, const char *mqttUser, const char *mqttPassword, RFIDManager &rfidManager, WifiManager &wifiManager)
      : mqttIP(mqttIP), mqttPort(mqttPort), mqttUser(mqttUser), mqttPassword(mqttPassword), rfidManager(rfidManager), wifiManager(wifiManager), wifiClient(), mqttClient(wifiClient)
  {
    // Este construtor inicializa os membros da classe com os valores fornecidos.
  }

  // Método para obter informações e enviar via MQTT.
  String getInfoAndSendMQTT(String id)
  {
    // Limpa o display LCD e imprime a mensagem de leitura do RFID.
    lcd.clear();
    lcd.print("  Pesquisando");
    lcd.setCursor(0, 1);
    lcd.print("ativo");

    // Criação de um documento JSON para armazenar os dados do RFID.
    DynamicJsonDocument jsonDoc(1024);
    jsonDoc["rfid"] = id;     // Armazena o ID do RFID.
    jsonDoc["leitor_id"] = 1; // Define o ID do leitor.

    // Serializa o JSON para uma string que será enviada via MQTT.
    String mqttPayload;
    serializeJson(jsonDoc, mqttPayload);
    Serial.println(mqttPayload.c_str());
    String teste = mqttPayload.c_str();
    return teste;
  }

  // Método para compilar uma lista de IDs RFID em um JSON.
  String compileList(const std::vector<String> &rfidList)
  {
    // Cria um documento JSON.
    DynamicJsonDocument jsonDoc(1024);
    JsonObject jsonObj = jsonDoc.to<JsonObject>();

    // Verifica se a lista tem pelo menos 2 elementos.
    if (rfidList.size() < 2)
    {
      Serial.println("Lista de RFID vazia. Não é possível determinar o esp_tag.");
      return "ERROR";
    }
    else
    {
      // Define o primeiro elemento da lista como a tag GPS.
      jsonObj["esp_tag"] = rfidList[0];
    }

    // Cria um array JSON para armazenar os ativos.
    JsonArray listaAtivos = jsonDoc.createNestedArray("lista_ativos");

    // Adiciona os IDs RFID restantes na lista de ativos.
    for (size_t i = 1; i < rfidList.size(); ++i)
    {
      listaAtivos.add(rfidList[i]);
    }

    // Serializa e retorna a lista de ativos como uma string.
    String mqttPayload;
    serializeJson(jsonObj, mqttPayload);
    return mqttPayload;
  }

  // Método para reconectar ao servidor MQTT, se necessário.
  void reconnect()
  {
    // Tenta se reconectar enquanto não estiver conectado.
    while (!mqttClient.connected())
    {
      Serial.print("Tentando se reconectar ao MQTT...");

      // Tenta estabelecer a conexão MQTT.
      if (mqttClient.connect("ESP32Client"))
      {
        Serial.println("Conectado");
      }
      else
      {
        // Informa falha e tenta novamente após 5 segundos.
        Serial.print("Falhou, rc=");
        Serial.print(mqttClient.state());
        Serial.println(" Tentando novamente em 5 segundos");

        vTaskDelay(pdMS_TO_TICKS(5000));
      }
    }
  }

private:
  // Membros privados, se houver, viriam aqui.
};

// Inicialização das classes para gerenciar Wi-Fi, RFID, Firebase e LEDs.
WifiManager wifiManager(WIFI_SSID, WIFI_PASSWORD);                                                   // Instância do gerenciador Wi-Fi com SSID e senha.
RFIDManager rfidManager(rfid);                                                                       // Instância do gerenciador de RFID.
WiFiClient wifiClient;                                                                               // Cliente Wi-Fi para a conexão.
PubSubClient mqttClient(wifiClient);                                                                 // Cliente MQTT usando o cliente Wi-Fi.
PostgresManager postgresManager(mqttIP, mqttPort, mqttUser, mqttPassword, rfidManager, wifiManager); // Instância do gerenciador Postgres.

// Instâncias de LEDs para sinalização.
LED red(25);
LED blue(26);
LED yellow(27);

// Instâncias de botões para interação com o usuário.
BUTTON next(15);
BUTTON botaoConfirmacao(16);
BUTTON botaoCancelamento(17);
BUTTON botaoFinalizar(14);

// Estado global do botão, usado para controle de fluxo.
bool BUTTON::globalState = false;

// Função de callback chamada quando uma mensagem MQTT chega.
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");

  // se chegar mensagem no tópico do MQTT
  if (strcmp(topic, topicoMQTT) == 0)
  {
    // Printa a mensagem que chegou uma mensagem em tal tópicp
    Serial.print("Received on topic: ");

    // limpa a variável para guardar a mensagem que chegou
    receivedMessage = "";

    for (unsigned int i = 0; i < length; i++)
    {
      // adiciona cada carácter no final da variavel
      receivedMessage += (char)payload[i];
    }

    Serial.println(receivedMessage);

    // interpreta a mensagem como um Json
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, receivedMessage);

    // Extrai a mensagem que contem relacionada a leitor_id
    int leitor_id_message = doc["leitor_id"];

    // verifica se o id que chegou da mensagem é igual ao id do microcontrolador
    if (leitor_id_message == leitor_id)
    {
      // extrai o nome do ativo 
      String receivedBoardFullName = doc["boardFullName"];

      // limpa o LCD
      lcd.clear();

      // mostra os 16 primeiros caracteres na primeira linha
      lcd.setCursor(0, 0);
      lcd.print(receivedBoardFullName.substring(0, 16));

      // se tiver mais de 16 caracteres, ele mostra o resto na segunda linha
      if (receivedBoardFullName.length() > 16)
      {
        lcd.setCursor(0, 1);
        lcd.print(receivedBoardFullName.substring(16));
      }

      vTaskDelay(pdMS_TO_TICKS(3000));
    }
    else
    {
      Serial.println("Invalid leitor_id. Ignoring message.");
    }
  }
  else
  {
    Serial.println("Ignoring message for other topics.");
  }
}

// Thread para manter o loop MQTT funcionando.
void mqttLoopThread(void *parameter)
{
  // Loop infinito para manter a conexão MQTT ativa.
  while (true)
  {
    mqttClient.loop();
  };
}

// Função de configuração do Arduino.
void setup()
{
  // Inicializa o display LCD e a comunicação serial.
  lcd.init();
  Serial.begin(115200);
  lcd.clear();
  lcd.backlight();

  // Inicializa os gerenciadores Wi-Fi e RFID, e liga o LED vermelho.
  wifiManager.begin();
  rfidManager.init();
  red.on();

  // Conecta ao Wi-Fi.
  while (WiFi.status() != WL_CONNECTED)
  {
    vTaskDelay(pdMS_TO_TICKS(500));
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  // Configura o cliente MQTT para conexão com o broker.
  mqttClient.setServer(mqttIP, mqttPort);
  mqttClient.setCallback(callback);

  // Conecta ao broker MQTT.
  while (!mqttClient.connected())
  {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (mqttClient.connect(client_id.c_str(), mqttUser, mqttPassword))
    {
      Serial.println("Public emqx mqtt broker connected");
      mqttClient.subscribe(topicoMQTT); // Inscreve-se no tópico MQTT.

      // Inicia a thread para manter o loop do MQTT.
     xTaskCreate(
        mqttLoopThread, /* Function to implement the task */
        "mqttLoopThread", /* Name of the task */
        10000, /* Stack size in words */
        NULL, /* Task input parameter */
        1, /* Priority of the task */
        NULL /* Task handle. */
      );
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(mqttClient.state());
      vTaskDelay(pdMS_TO_TICKS(2000));
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Erro de");
      lcd.setCursor(0, 1);
      lcd.print("Conexão");
    }
  }

  Serial.println("MQTT Connected!");
}

// Função de loop principal do Arduino.
void loop()
{
  // Verifica o estado do botão "next" e atualiza a variável global.
  next.GlobalButton();

  // Processa diferentes estados baseados na variável global globalState.
  if (!BUTTON::globalState)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Escaneie");
    lcd.setCursor(0, 1);
    lcd.print("o RFID");
    red.off();
    blue.on();
    yellow.off();

    // Lê o ID do cartão RFID e realiza ações baseadas nele.
    botaoFinalizar.checkButton();
    String id = rfidManager.readRFID();
    Serial.print(id);
    if (!id.isEmpty())
    {
      String jsom = postgresManager.getInfoAndSendMQTT(id);
      mqttClient.publish("identificador", jsom.c_str());

      botaoConfirmacao.checkButton();
      botaoCancelamento.checkButton();

      // Verifica o estado dos outros botões.
      while (botaoConfirmacao.currentState != LOW && botaoCancelamento.currentState != LOW)
      {
        Serial.println("Checking");
        botaoConfirmacao.checkButton();
        botaoCancelamento.checkButton();
        vTaskDelay(pdMS_TO_TICKS(200));
      }

      // Processa as ações de confirmação ou cancelamento.
      if (botaoConfirmacao.currentState == LOW)
      {
        Serial.println("Confirmado");
        rfidManager.addToRFIDList(id);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ativo registrado");
        lcd.setCursor(0, 1);
        lcd.print("com sucesso");
        vTaskDelay(pdMS_TO_TICKS(1000));
        id = "";
      }
      else if (botaoCancelamento.currentState == LOW)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Cancelado!");
        vTaskDelay(pdMS_TO_TICKS(1000));
        Serial.println("Cancelado");
        id = "";
      }
    }
    // Se o botão "finalizar" for apertado, ele confere se a lista é maior que 1, e se for ele publica a lista no MQTT
    else if (botaoFinalizar.currentState == LOW && rfidManager.rfidList.size() > 1)
    {
      String jsom = postgresManager.compileList(rfidManager.rfidList);
      rfidManager.rfidList.clear();
      mqttClient.publish("finalizar", jsom.c_str());
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enviado com");
      lcd.setCursor(0, 1);
      lcd.print("sucesso!");
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Escreva");
    lcd.setCursor(0, 1);
    lcd.print("no RFID");
    red.off();
    yellow.on();
    blue.off();

    // Executa a escrita de dados no cartão RFID.
    rfidManager.writeRFID("030LNBW0JB003990", yellow, red);
  }
}
