#ifndef casa
#define casa

#include <PubSubClient.h>
#include <Arduino.h>
#include <WiFi.h>
#include <conection/wifi_conection.cpp>
const char *mqtt_broker = "maqiatto.com";                // Host do broket
const char *topic = "messiasdedeus@hotmail.com/topico1"; // Topico a ser subscrito e publicado
const char *mqtt_username = "messiasdedeus@hotmail.com"; // Usuario
const char *mqtt_password = "chocadeira";                // Senha
const int mqtt_port = 1883;                              // Porta

WiFiClient espClient;
PubSubClient client(espClient);
#define ID_MQTT "BROKER01" // Informe um ID unico e seu. Caso sejam usados IDs repetidos a ultima conexão irá sobrepor a anterior.

void callba(char *topic, byte *payload, unsigned int length)
{
  String msg = "";
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++)
  {
    msg.concat((char)payload[i]);
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
  // while Update -y sudo su a
}

void setMqtt(){
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callba);
}

bool connectMQTT(const char *mqtt_broker, int mqtt_port, const char *mqtt_username, const char *mqtt_password, const char *topic)
{
  byte tentativa = 0;


  while (!client.connected())
  {
    String client_id = "CYACONQUISTA-";
    client_id += String(WiFi.macAddress());

    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password))
    {
      Serial.println("Exito na conexão:");
      Serial.printf("Cliente %s conectado ao broker\n", client_id.c_str());
    }
    else
    {
      Serial.print("Falha ao conectar: ");
      Serial.print(client.state());
      Serial.println();
      Serial.print("Tentativa: ");
      Serial.println(tentativa);
      delay(2000);
    }
    // tentativa++;
  } 

  // if (tentativa < 5)
  // {
  //   // publish and subscribe

  //   // client.publish(topic, "{teste123,113007042022}");
  //   // client.subscribe(topic);
  //   return 1;
  // }
  // else
  // {
  //   Serial.println("Não conectado");
  //   return 0;
  // }
  return true;
}
void conectaWiFi()
{

  if (WiFi.status() == WL_CONNECTED) return;
  

  WiFi.begin();
  while (WiFi.status() != WL_CONNECTED)
  {

    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado com sucesso, na rede: ");
  Serial.print(WiFi.SSID());
  Serial.print("  IP obtido: ");
  Serial.println(WiFi.localIP());
}

void conectaMQTT()
{
  while (!client.connected())
  {
    Serial.print("Conectando ao Broker MQTT: ");

    if (client.connect(ID_MQTT))
    {
      Serial.println("Conectado ao Broker com sucesso!");
    }
    else
    {
      Serial.println("Noo foi possivel se conectar ao broker.");
      Serial.println("Nova tentatica de conexao em 5s");
      delay(5000);
    }
  }
}
void manter_conexao()
{
  // conectaWiFi();
  // connectMQTT(mqtt_broker, mqtt_port, mqtt_username, mqtt_password, topic);

  if (!client.connected())
  {
   delay(10000);
   Serial.print("Reiniciar");
   ESP.restart();
    
  }
  // se não há conexão com o WiFI, a conexão é refeita
}

#endif