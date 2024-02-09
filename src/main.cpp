/* Projeto :Chocadeira - Choc tobias
    Autor: Manoel Messias Pereira de Deus
    Cidade: Vitoria da Conquista
    Data da ultima solicitação:  04/08/2023
    Versão 2.0
    Alterações feitas:*/
#include <SPI.h>;
#include <Wire.h>;
#include <LiquidCrystal_I2C.h>; // Define o endereço utilizado pelo Adaptador I2C cc
#include <MQTT/connectMQTT.cpp>
#include <Sensores/temperatura.cpp>
#include <conection/Bluettoth_conection.cpp>
#include <conection/wifi_conection.cpp>
#include <controles/ligar_motor.cpp>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <WiFi.h>,
#include <PubSubClient.h>,
#include <DHT.h> //Biblioteca para funcionamento do sensor de temperatura e umidade DHT11
// Parametros de conexão

// Paramentros DHT11(Variaveis)ddd
#define DHTPIN 26     // Pino digital D2 (GPIO5) conectado ao DHT11
#define DHTTYPE DHT11 // Tipo do sensor DHT11

#define col 16    // Define o número de colunas do display utilizado
#define lin 4     // Define o número de linhas do display utilizado
#define ende 0x27 // Define o endereço do display
int umidificado = 25;
// MQTT Broker


// Variáveis
bool mqttStatus = 0;

// Objetos

// Prototipos

void setup(void)
{
  pinMode(umidificado,OUTPUT);
  digitalWrite(umidificado,HIGH);
  digitalWrite(rele, HIGH);
  inicio();

  conectawifimanager() ;
  //conectawifi();
  Serial.begin(9600);
  dht.begin();     // Inicializa o sensor DHT11
  lcd.init();      // Inicializa a comunicação com o display já conectado
  lcd.clear();     // Limpa a tela do display
  lcd.backlight(); // Aciona a luz de fundo do display
  lcd.setCursor(0, 0);
  lcd.print("CHOC TOBIAS");
  // Conectar
  delay(2000);
  // Aguardando conexão
  Serial.println();
  Serial.print("INICIANDO CONEXÃO");
  lcd.setCursor(0, 1);
  lcd.print("Buscando rede"); // Exibe a mensagem na primeira linha do display

  Serial.println("");
  Serial.println("WiFi connected");
  // Limpa a tela do display
  lcd.setCursor(0, 2);
  lcd.print("CONECTADO A REDE"); // Exibe a mensagem na primeira linha do display
  delay(1000);
  // Envia IP através da UART
  Serial.println(WiFi.localIP());
  lcd.setCursor(0, 3); // Coloca o cursor do display na coluna 1 e linha 2
  lcd.print("IP:");    // Exibe a mensagem na segunda linha do display
  lcd.print(WiFi.localIP());
  setMqtt();
  mqttStatus = connectMQTT(mqtt_broker, mqtt_port, mqtt_username, mqtt_password, topic);
  delay(5000);
}

void envia_MQTT()
{
  Temperatura dados_sensor = enviaDHT();
  static long long pooling = 0;
  if (mqttStatus)
  {

    if (millis() > pooling + 3000)
    {
      pooling = millis();
      String msg = ("temperatura:" + String(dados_sensor.temperatura) + "Umidade:" + String(dados_sensor.umidade));
      client.publish(topic, msg.c_str());
     
    }
  }
}
void acionar_umidificado()
{
  Temperatura dados_sensor = enviaDHT();
  if (dados_sensor.umidade <60 )
  {
    digitalWrite(umidificado,LOW);
    Serial.println("Umidade baixa");
  }
   if (dados_sensor.umidade >60 )
  {
    digitalWrite(umidificado,HIGH);
    Serial.println("Umidade alta");
  }
}


void loop()
{

  Temperatura dados_sensor = enviaDHT();
  

  bluetooth.print(dados_sensor.temperatura);
  String client_id = "BROKER-";
  client_id += String(WiFi.macAddress());
  lcd.clear();            // Limpa a tela do display
  lcd.setCursor(0, 0);    // Coloca o cursor do display na coluna 1 e linha 1
  lcd.print(client_id);   // Exibe a mensagem na primeira linha do display
  lcd.setCursor(0, 1);    // Coloca o cursor do display na coluna 1 e linha 2
  lcd.print("IP LOCAl:"); // Exibe a mensagem na segunda linha do display
  lcd.print(WiFi.localIP());
  // lcd.setCursor(0, 2);
  // lcd.print("Temperatura:");
  // lcd.print(dados_sensor.temperatura);
  // lcd.setCursor(0, 3);
  // lcd.print("Umidade:");
  // lcd.print(dados_sensor.umidade);
  if (!client.connected())
  {
    lcd.clear();
    lcd.setCursor(0, 0);    // Coloca o cursor do display na coluna 1 e linha 1
    lcd.print("SEM CONEXAO WIFI");
    lcd.setCursor(0, 1);    // Coloca o cursor do display na coluna 1 e linha 2
    lcd.print("PERDA DE CONEXAO");
    lcd.setCursor(0, 2);
    lcd.print("RECONECTANDO");
  }
  
  manter_conexao();
  bluetooth2();
  if (isnan(dados_sensor.umidade) || isnan(dados_sensor.temperatura)){
    lcd.clear();
    lcd.print("FALHA SENSOR");
    lcd.setCursor(0, 2);    // Coloca o cursor do display na coluna 1 e linha 2
    lcd.print("FALHA TEMPERATURA");
    lcd.setCursor(0, 3);
    lcd.print("FALHA UMIDADE");    
  }
  else if (dados_sensor.umidade_atual !=dados_sensor.umidade || dados_sensor.temperatura_atual != dados_sensor.temperatura)
  {
    dados_sensor.umidade_atual =dados_sensor.umidade;
    dados_sensor.temperatura_atual =dados_sensor.temperatura;
    lcd.setCursor(0, 2);
    lcd.print("Temperatura:");
    lcd.print(dados_sensor.temperatura);
    lcd.setCursor(0, 3);
    lcd.print("Umidade:");
    lcd.print(dados_sensor.umidade);
  }
  
 
  viragem();
  envia_MQTT();
  acionar_umidificado();
  client.loop();
}

void callback2(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
  // while Update -y sudo su a
}