#include <Wire.h>;
#include <LiquidCrystal_I2C.h>;
 //teste Victor Emanuel
// Define o endereço utilizado pelo Adaptador I2C cc
LiquidCrystal_I2C lcd(0x27,20,4);

#include <WiFi.h>,
#include <PubSubClient.h>,
#include <DHT.h> //Biblioteca para funcionamento do sensor de temperatura e umidade DHT11
//Parametros de conexão
const char* ssid = "CYACONQUISTA"; // REDE
const char* password = "Pin202020"; // SENHA

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
WiFiClient espClient;
PubSubClient client(espClient);

//Prototipos
bool connectMQTT();
void callback(char *topic, byte * payload, unsigned int length);

DHT dht(DHTPIN, DHTTYPE); //Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

float temperatura; //variável para armazenar a temperatura
float umidade; //Variável para armazenar a umidade
void enviaDHT(){
  char MsgTempMQTT[10];
  temperatura = dht.readTemperature();  //Realiza a leitura da temperatura
  umidade = dht.readHumidity(); //Realiza a leitura da umidade
  Serial.print("Temperatura: ");
  Serial.print(temperatura); //Imprime no monitor serial o valor da temperatura lida
  Serial.println(" ºC");
  Serial.print("Umidade: ");
  Serial.print(umidade); //Imprime no monitor serial o valor da umidade lida
  Serial.println(" %");
  delay(1000);

  sprintf(MsgTempMQTT,"%f",temperatura);
  client.publish("messiasdedeus@hotmail.com/topico1",MsgTempMQTT);
}

void setup(void)
{
  Serial.begin(9600);
  dht.begin(); //Inicializa o sensor DHT11
  lcd.init(); //Inicializa a comunicação com o display já conectado
  lcd.clear(); //Limpa a tela do display
  lcd.backlight(); //Aciona a luz de fundo do display
  lcd.setCursor(0, 0);
  lcd.print("CHOC TOBIAS");
  // Conectar
  WiFi.begin(ssid, password);
  delay(2000);
  //Aguardando conexão
  Serial.println();
  Serial.print("INICIANDO CONEXÃO");
  lcd.setCursor(0, 1);
  lcd.print("Buscando rede"); //Exibe a mensagem na primeira linha do display
  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.print(".");
    lcd.print("SEM CONEXÃO");
  }
  Serial.println("");
  Serial.println("WiFi connected");
   //Limpa a tela do display
   lcd.setCursor(0, 2);
  lcd.print("CONECTION SENSORES"); //Exibe a mensagem na primeira linha do display
  delay(1000);
  //Envia IP através da UART
  Serial.println(WiFi.localIP());
  lcd.setCursor(0, 3); //Coloca o cursor do display na coluna 1 e linha 2
  lcd.print("IP:");  //Exibe a mensagem na segunda linha do display
  lcd.print(WiFi.localIP());
  mqttStatus =  connectMQTT();
  delay(5000);
}

void loop() {
  lcd.clear(); //Limpa a tela do display
  lcd.setCursor(0, 0); //Coloca o cursor do display na coluna 1 e linha 1
  lcd.print("CHOCK TOBIAS"); //Exibe a mensagem na primeira linha do display
  lcd.setCursor(0, 1); //Coloca o cursor do display na coluna 1 e linha 2
  lcd.print("IP LOCAl:");  //Exibe a mensagem na segunda linha do display
  lcd.print(WiFi.localIP());
  lcd.setCursor(0, 2);
  lcd.print("CYACONQUISTA");
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



bool connectMQTT() {
  byte tentativa = 0;
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  do {
    String client_id = "BOBSIEN-";
    client_id += String(WiFi.macAddress());

    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Exito na conexão:");
      Serial.printf("Cliente %s conectado ao broker\n", client_id.c_str());
    } else {
      Serial.print("Falha ao conectar: ");
      Serial.print(client.state());
      Serial.println();
      Serial.print("Tentativa: ");
      Serial.println(tentativa);
      delay(2000);
    }
    tentativa++;
  } while (!client.connected() && tentativa < 5);

  if (tentativa < 5) {
    // publish and subscribe   
    //client.publish("messiasdedeus@hotmail.com/topico1",MsgTempMQTT); 
    client.subscribe(topic);
    return 1;
  } else {
    Serial.println("Não conectado");    
    return 0;
  }
}

void callback(char *topic, byte * payload, unsigned int length) {
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
