#include "LED_Test.h"

LED_Test::LED_Test(int pin,  int led_delay){
  pinMode(pin, OUTPUT);
  _pin   = pin;
  _delay = led_delay;
}

void LED_Test::ON(){
  digitalWrite(_pin,HIGH);
  delay(_delay);
}

void LED_Test::OFF(){
  digitalWrite(_pin,LOW);
  delay(_delay);
}