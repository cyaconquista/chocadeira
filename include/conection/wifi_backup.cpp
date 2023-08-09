#include <WiFi.h>,

const char* ssid = "CYACONQUISTA"; // REDE
const char* password = "Pin202020"; // SENHA

void setup(void)
{
WiFi.begin(ssid, password);


}