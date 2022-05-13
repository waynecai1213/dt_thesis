
/*
  Homing.h - Own library for homing stepper motor position.
*/
#ifndef Homing_h
#define Homing_h
#include "Arduino.h"
#include <AccelStepper.h>

class Homing
{
  public:
    // pin to detect home position 
    Homing(int pin, AccelStepper stepper, int dir);
    void runHome();
    AccelStepper _stepper;
    int _homePin;
    long _dir;
};


#endif