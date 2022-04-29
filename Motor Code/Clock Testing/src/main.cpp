#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
//#include <Stepper.h>
#include <AccelStepper.h>

// my own library
#include <Homing.h>
#include <ClockStates.h>

// for homing, 1/-1 represent rotation direction
Homing home_stepper_Hr(hallPin_Hr, stepper_Hr, 1);
Homing home_stepper_Min(hallPin_Min, stepper_Min, -1);

void checkSerial()
{
  if (Serial.available() > 0) // if something comes
  {
    receivedCommand = Serial.read(); // read the first character from the serial command

    switch (receivedCommand)
    {
    case 't':
      Serial.println("----- show correct time, Start-----");
      stepper_Hr.setMaxSpeed(600.0);
      stepper_Hr.setAcceleration(400.0);

      stepper_Min.setMaxSpeed(600.0);
      stepper_Min.setAcceleration(400.0);

      stepper_Hr.moveTo(abs(hours * STEPS_PER_HR - fullRevolution / 2));
      stepper_Min.moveTo((minutes * STEPS_PER_MIN - fullRevolution / 2));

      clock_state = 't';

      break;

    case 'm':
      clock_state = 'm';
      travel_Hr = Serial.parseInt();
      travel_Min = Serial.parseInt();

      Serial.print("Moving Hr Stepper into position:  ");
      Serial.println(travel_Hr);
      Serial.print("Moving Min Stepper into position:  ");
      Serial.println(travel_Min);

      stepper_Hr.setMaxSpeed(700);
      stepper_Hr.setAcceleration(400);

      stepper_Min.setMaxSpeed(700);
      stepper_Min.setAcceleration(400);

      stepper_Hr.moveTo(travel_Hr);
      stepper_Min.moveTo(travel_Min);

      break;

    case 'h':
      Serial.println("home");

      break;

    case 'd':
      stepper_Hr.setMaxSpeed(700.0);
      stepper_Hr.setAcceleration(600.0);

      stepper_Min.setMaxSpeed(700.0);
      stepper_Min.setAcceleration(600.0);
      clock_state = 'd';
      break;

    case 'n':
      clock_state = 'n';
      input_Speed = Serial.parseInt();
      stepper_Hr.setMaxSpeed(700.0);
      stepper_Hr.setAcceleration(600.0);

      stepper_Min.setMaxSpeed(700.0);
      stepper_Min.setAcceleration(600.0);

      stepper_Hr.runToNewPosition(3 * STEPS_PER_HR);
      stepper_Min.runToNewPosition(15 * STEPS_PER_MIN);

       stepper_Hr.setSpeed(input_Speed);
        stepper_Min.setSpeed(-input_Speed);
      break;

    case 's':
    
      input_Speed = Serial.parseInt();
      stepper_Hr.setMaxSpeed(600.0);
       stepper_Min.setMaxSpeed(600.0);
      stepper_Hr.setSpeed(input_Speed);
      stepper_Min.setSpeed(-input_Speed);
      break;
    }
  }
}

void setup()
{
  // Hall sensor
  pinMode(hallPin_Hr, INPUT);
  pinMode(hallPin_Min, INPUT);

  // Initialize Serial Monitor
  Serial.begin(115200);
  /*Homing Stepper Motos*/
  home_stepper_Hr.runHome();
  home_stepper_Min.runHome();
}

void loop()
{
  checkSerial();
  // if (millis()>=5000){
  //   clock_state='t';
  // }

  // if (clock_state=='m'){
  //   moveToInput();
  // }

  switch (clock_state)
  {
  case 't':

    reCalPos();
    stepper_Hr.run();
    stepper_Min.run();
    break;
  case 'm':
    reCalPos();
    stepper_Hr.run();
    stepper_Min.run();
    break;

  case 'd':
    dropHands();
    stepper_Hr.run();
    stepper_Min.run();
    break;

  case 'n':
    stepper_Hr.runSpeed();
     stepper_Min.runSpeed();
    break;

  default:

    break;
  }
}
