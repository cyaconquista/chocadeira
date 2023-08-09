/* Projeto :Chocadeira - Choc tobias 
    Autor: Manoel Messias Pereira de Deus
    Cidade: Vitoria da Conquista
    Data da ultima solicitação:  04/08/2023
    Versão 2.0
    Alterações feitas:*/

#include <Wire.h>;
#include <LiquidCrystal_I2C.h>;// Define o endereço utilizado pelo Adaptador I2C cc
#include <MQTT/connectMQTT.cpp>
#include <Sensores/temperatura.cpp>
#include <conection/Bluettoth_conection.cpp>
#include <conection/wifi_conection.cpp>

LiquidCrystal_I2C lcd(0x27,20,4);

#include <WiFi.h>,
#include <PubSubClient.h>,
#include <DHT.h> //Biblioteca para funcionamento do sensor de temperatura e umidade DHT11
//Parametros de conexão


//Paramentros DHT11(Variaveis)ddd
#define DHTPIN 26 //Pino digital D2 (GPIO5) conectado ao DHT11
#define DHTTYPE DHT11 //Tipo do sensor DHT11


#define col  16 //Define o número de colunas do display utilizado
#define lin   4 //Define o número de linhas do display utilizado
#define ende  0x27 //Define o endereço do display

// MQTT Broker
const char *mqtt_broker = "maqiatto.com";  //Host do broket
const char *topic = "messiasdedeus@hotmail.com/topico1";            //Topico a ser subscrito e publicado
const char *mqtt_username = "messiasdedeus@hotmail.com";         //Usuario
const char *mqtt_password = "chocadeira";         //Senha
const int mqtt_port = 1883;             //Porta

//Variáveis
bool mqttStatus = 0;

//Objetos

//Prototipos




void setup(void)
{
  inicio();
  conectawifi();
  Serial.begin(9600);
  dht.begin(); //Inicializa o sensor DHT11
  lcd.init(); //Inicializa a comunicação com o display já conectado
  lcd.clear(); //Limpa a tela do display
  lcd.backlight(); //Aciona a luz de fundo do display
  lcd.setCursor(0, 0);
  lcd.print("CHOC TOBIAS");
  // Conectar
  delay(2000);
  //Aguardando conexão
  Serial.println();
  Serial.print("INICIANDO CONEXÃO");
  lcd.setCursor(0, 1);
  lcd.print("Buscando rede"); //Exibe a mensagem na primeira linha do display

  
  Serial.println("");
  Serial.println("WiFi connected");
   //Limpa a tela do display
  lcd.setCursor(0, 2);
  lcd.print("CONECTADO A REDE"); //Exibe a mensagem na primeira linha do display
  delay(1000);
  //Envia IP através da UART
  Serial.println(WiFi.localIP());
  lcd.setCursor(0, 3); //Coloca o cursor do display na coluna 1 e linha 2
  lcd.print("IP:");  //Exibe a mensagem na segunda linha do display
  lcd.print(WiFi.localIP());
  mqttStatus =  connectMQTT(mqtt_broker,mqtt_port,mqtt_username,mqtt_password,topic);
  delay(5000);
}

void loop() {
  
  float temperatura =enviaDHT();
  bluetooth2();
  bluetooth.print(temperatura);
  lcd.clear(); //Limpa a tela do display
  lcd.setCursor(0, 0); //Coloca o cursor do display na coluna 1 e linha 1
  lcd.print("CHOCK TOBIAS"); //Exibe a mensagem na primeira linha do display
  lcd.setCursor(0, 1); //Coloca o cursor do display na coluna 1 e linha 2
  lcd.print("IP LOCAl:");  //Exibe a mensagem na segunda linha do display
  lcd.print(WiFi.localIP());
  lcd.setCursor(0, 2);
  lcd.print("REDE:"); 
  lcd.print(WiFi.SSID());
  lcd.setCursor(0, 3);
  lcd.print("Temperatura:");
  lcd.print(temperatura);
    delay(1000);

  char MsgTempMQTT[10];
  enviaDHT();

 static long long pooling  = 0;
  if ( mqttStatus){
    
    client.loop();    

    if (millis() > pooling +1000){
      pooling = millis();
     // client.publish(topic, MsgTempMQTT);
    }
       
  }
}





void callback2(char *topic, byte * payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
  //while Update -y sudo su a
}