#include <AltSoftSerial.h>
//#include "timer-api.h"

char* phoneBook[]={}; // Женя К.

AltSoftSerial altSerial;
String str_1  = "", number  = "";

void setup() {
  Serial.begin(9600);
  Serial.println("AltSoftSerial Test Begin");
  altSerial.begin(9600);
  altSerial.println("Hello World");
  pinMode(12, OUTPUT);
  
}
void loop() {
 /* char c;
  
  if (Serial.available()) {
    c = Serial.read();
    altSerial.print(c);
  } 
  if (altSerial.available()) {
    c = altSerial.read();
    Serial.print(c);
  }  */
  if (altSerial.available()) // если пришло что то от GSM модуля, то вызываем обработчик
  {
    response_on_dial();
  }
  digitalWrite(12, HIGH); 
  delay(500);
}
void response_on_dial()
{
  //delay(5000);
  while (altSerial.available())
  {
    char c  = altSerial.read();
    str_1  +=  c;
  }
  // Находим в строке "+79" и выдёргиваем из строки номер телефона
  if (str_1.startsWith("RING", 2))
  {
    int index_number = str_1.lastIndexOf("+79");
    if (index_number != -1)
    {
      number  = str_1.substring(index_number, (index_number + 12));
      altSerial.println("AT+CHUP");
      // Пришел вызов в номера "number", далее пишем, что делаем
      String str_2  = "Ring!!!   "  + number;
      Serial.println(str_2);
      
      bool numberExists = false;
      for(int i = 0; i < sizeof(phoneBook) - 1; i++){
        
        if(number == phoneBook[i]){
          numberExists = true;
          Serial.println(phoneBook[i]);
          break;
        }
      }
      if(numberExists){
        digitalWrite(12, LOW);
        Serial.println("OK");
        delay(1500);
      }
    }
  }
  str_1 = "";
}
