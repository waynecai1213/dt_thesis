#include <Arduino.h>

  // put your main code here, to run repeatedly:
char receivedCommand;
String Q;

void setup() {
       
  // put your setup code here, to run once:
pinMode(13,OUTPUT); 
Serial.begin(9600);
}
 
void loop() {

 

//-------------------------------Check Serial Port---------------------------------------
 
    if (Serial.available() >0) {
      receivedCommand = Serial.read();  //gets one byte from serial buffer
    
    }
 

      if(receivedCommand=='t'){         
        digitalWrite(13,HIGH);               
      }
      if(receivedCommand=='f'){         
        digitalWrite(13,LOW);             
      }
 
 
 
}