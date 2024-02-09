#include <DHT.h> //Biblioteca para funcionamento do sensor de temperatura e umidade DHT11

#define DHTPIN 26 //Pino digital D2 (GPIO5) conectado ao DHT11
#define DHTTYPE DHT22 //Tipo do sensor DHT11
struct Temperatura
{
  float temperatura; float umidade;
  float temperatura_atual; float umidade_atual;
};

DHT dht(DHTPIN, DHTTYPE); //Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)
// float temperatura; //variável para armazenar a temperatura
// float umidade; //Variável para armazenar a umidade
Temperatura enviaDHT(){
  char MsgTempMQTT[10];
  float temperatura = dht.readTemperature();  //Realiza a leitura da temperatura
  float umidade = dht.readHumidity(); //Realiza a leitura da umidade
  Serial.print("Temperatura: ");
  Serial.print(temperatura); //Imprime no monitor serial o valor da temperatura lida
  Serial.println(" ºC");
  Serial.print("Umidade: ");
  Serial.print(umidade); //Imprime no monitor serial o valor da umidade lida
  Serial.println(" %");
  delay(1000);

  sprintf(MsgTempMQTT,"%f",temperatura);

  return {temperatura,umidade};
  // Temperatura temp;
  // temp.temperatura = temperatura;
  // temp.umidade = umidade;
  // return temp;
  

}