#ifndef LED_Test_H
#define LED_Test_H
#include "arduino.h"

class LED_Test {
  public:
    LED_Test(int pin, int delay);
    void ON();
    void OFF();
    int _pin;
    int _delay;
};

#endif