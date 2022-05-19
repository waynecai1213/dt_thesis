/*
   Homing.h - Own library for homing stepper motor position.
*/

#include "Arduino.h"
#include "Homing.h"
#include <AccelStepper.h>

Homing::Homing(int pin, AccelStepper stepper, int dir)
{
  pinMode(pin, INPUT);
  _homePin = pin;
  _dir = dir;
  _stepper = stepper;
  _stepper.setMaxSpeed(300);
  _stepper.setAcceleration(200);
}

void Homing::runHome()
{
  // Serial.print("Home Sensor Pin:  ");
  // Serial.println(digitalRead(_homePin));
  // Serial.println("Stepper_initial_homing");
  _stepper.moveTo(_dir*100000);
  while (digitalRead(_homePin))
  {
    _stepper.run();
  }

  // Reset position and speed
  _stepper.setCurrentPosition(0);
  _stepper.setMaxSpeed(300.0);
  _stepper.setAcceleration(300.0);

 _stepper.moveTo(_dir*10000*(-1));
  
  delay(500);

  while (!digitalRead(_homePin))
  {
    _stepper.run();
  }

  _stepper.setCurrentPosition(0);
  _stepper.setMaxSpeed(300.0);
  _stepper.setAcceleration(200.0);
  // Serial.println("----- Homed -----");
 
}
