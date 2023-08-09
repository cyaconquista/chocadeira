#ifndef Bluettoth
#define Bluettoth
#include<BluetoothSerial.h>

BluetoothSerial bluetooth;

void inicio(){
    Serial.begin(115200);
    bluetooth.begin("RedChocadeira");
    bluetooth.begin(9600); //Inicia a serial do bluetooth
    bluetooth.print("$"); //Inicia a serial do bluetooth
    bluetooth.print("$"); //Inicia a serial do bluetooth
    bluetooth.print("$"); //Inicia a serial do bluetooth
}
void bluetooth2(){
    char dadoBluetooth = bluetooth.read();
    char serial = Serial.read();
    bluetooth.print("Temp1|");
 
}

#endif