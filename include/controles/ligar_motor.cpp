#include <Wire.h> //INCLUSÃO DA BIBLIOTECA
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA

RTC_DS1307 rtc; //OBJETO DO TIPO RTC_DS1307

int rele = 23;

//DECLARAÇÃO DOS DIAS DA SEMANA
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};

void viragem () {
  pinMode(rele, OUTPUT);

  if (! rtc.begin()) { // SE O RTC NÃO FOR INICIALIZADO, FAZ
    Serial.println("DS1307 não encontrado"); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
  if (! rtc.isrunning()) { //SE RTC NÃO ESTIVER SENDO EXECUTADO, FAZ
    Serial.println("DS1307 rodando!"); //IMPRIME O TEXTO NO MONITOR SERIAL
    //REMOVA O COMENTÁRIO DE UMA DAS LINHAS ABAIXO PARA INSERIR AS INFORMAÇÕES ATUALIZADAS EM SEU RTC
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
    //rtc.adjust(DateTime(2023, 8, 15, 23, 22, 15)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
  }
  delay(100); //INTERVALO DE 100 MILISSEGUNDOS

    DateTime now = rtc.now(); //CHAMADA DE FUNÇÃO
    Serial.print("Data: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(now.day(), DEC); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.month(), DEC); //IMPRIME NO MONITOR SERIAL O MÊS
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.year(), DEC); //IMPRIME NO MONITOR SERIAL O ANO
    Serial.print(" / Dia: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print(" / Horas: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(now.hour(), DEC); //IMPRIME NO MONITOR SERIAL A HORA
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.minute(), DEC); //IMPRIME NO MONITOR SERIAL OS MINUTOS
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.second(), DEC); //IMPRIME NO MONITOR SERIAL OS SEGUNDOS
    Serial.println(); //QUEBRA DE LINHA NA SERIAL
    delay(1000); //INTERVALO DE 1 SEGUNDO
       if ((now.hour() == 00) && (now.minute()==30)&& (now.second()>45)&& (now.second()<51))
  {
    digitalWrite(rele, LOW);
   

    delay(6000);
    digitalWrite(rele, HIGH);
    
  }

         if ((now.hour() == 02) && (now.minute()==30)&& (now.second()>45)&& (now.second()<51))
  {
    digitalWrite(rele, LOW);
   

    delay(6000);
    digitalWrite(rele, HIGH);
    
  }
           if ((now.hour() == 04) && (now.minute()==30)&& (now.second()>45)&& (now.second()<51))
  {
    digitalWrite(rele, LOW);
   

    delay(6000);
    digitalWrite(rele, HIGH);
    
  }
           if ((now.hour() == 06) && (now.minute()==30)&& (now.second()>45)&& (now.second()<51))
  {
    digitalWrite(rele, LOW);
   

    delay(6000);
    digitalWrite(rele, HIGH);
    
  }
           if ((now.hour() == 8) && (now.minute()==30)&& (now.second()>45)&& (now.second()<51))
  {
    digitalWrite(rele, LOW);
   

    delay(6000);
    digitalWrite(rele, HIGH);
    
  }

            if ((now.hour() == 10) && (now.minute()==30)&& (now.second()>45)&& (now.second()<51))
  {
    digitalWrite(rele, LOW);
   

    delay(6000);
    digitalWrite(rele, HIGH);
    
  }

              if ((now.hour() == 12) && (now.minute()==30)&& (now.second()>45)&& (now.second()<51))
  {
    digitalWrite(rele, LOW);
   

    delay(6000);
    digitalWrite(rele, HIGH);
    
  }

                if ((now.hour() == 14) && (now.minute()==30)&& (now.second()>45)&& (now.second()<51))
  {
    digitalWrite(rele, LOW);
   

    delay(6000);
    digitalWrite(rele, HIGH);
    
  }

                if ((now.hour() == 16) && (now.minute()==30)&& (now.second()>45)&& (now.second()<51))
  {
    digitalWrite(rele, LOW);
   

    delay(6000);
    digitalWrite(rele, HIGH);
    
  }
                if ((now.hour() == 18) && (now.minute()==30)&& (now.second()>45)&& (now.second()<51))
  {
    digitalWrite(rele, LOW);
   

    delay(6000);
    digitalWrite(rele, HIGH);
    
  }

                  if ((now.hour() == 20) && (now.minute()==30)&& (now.second()>45)&& (now.second()<51))
  {
    digitalWrite(rele, LOW);
   

    delay(6000);
    digitalWrite(rele, HIGH);
    
  }

                  if ((now.hour() == 22) && (now.minute()==30)&& (now.second()>45)&& (now.second()<51))
  {
    digitalWrite(rele, LOW);
   

    delay(6000);
    digitalWrite(rele, HIGH);
    
  }
  {
    /* code */
  }
  
}