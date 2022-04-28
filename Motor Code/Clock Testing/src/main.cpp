#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
//#include <Stepper.h>
#include <AccelStepper.h>

//my own library
#include <Homing.h>
#include <LED_Test.h>

LED_Test LED1(13, 300);
LED_Test LED2(12, 30);

//**// config stepper motors
const int stepsPerRevolution = 4; // change this to fit the number of steps per revolution

// ULN2003 Motor Driver Pins
#define motorPin1 13 // 28BYJ48 pin 1
#define motorPin2 12 // 28BYJ48 pin 2
#define motorPin3 14 // 28BYJ48 pin 3
#define motorPin4 27 // 28BYJ48 pin 4

#define motorPin5 26 // 28BYJ48 pin 1
#define motorPin6 25 // 28BYJ48 pin 2
#define motorPin7 33 // 28BYJ48 pin 3
#define motorPin8 32 // 28BYJ48 pin 4


#define hallPin_Hr 15 // 28BYJ48 pin 3
#define hallPin_Min 4 // 28BYJ48 pin 4

// initialize the stepper library
AccelStepper stepper_Hr(stepsPerRevolution, motorPin5, motorPin7, motorPin6, motorPin8);
AccelStepper stepper_Min(stepsPerRevolution, motorPin1, motorPin3, motorPin2, motorPin4);

//for homing, 1/-1 represent rotation direction
Homing home_stepper_Hr(hallPin_Hr,stepper_Hr,1);
Homing home_stepper_Min(hallPin_Min,stepper_Min,-1);

// max speed: 660

// stepper motor steps & angles
int stepsToTake = 128; // 16*64=1024; one full revolution = 1024;
int fullRevolution = 1024;
int stepToTake_Angle = fullRevolution / 60;
#define STEPS_PER_HR 85  // 1024/12
#define STEPS_PER_MIN 17 // 1024/60

//real time parameters
long hours = 4;
long minutes = 50;

// -  Hand_Hr will move CW
// +  Hand_Min will move CW

int anglePosition_Hr;
int anglePosition_Min;

long travel_Hr; // Used to store the value entered in the Serial Monitor
long travel_Min;
bool home_finished = true;
long initial_homing = 1;
int move_finished = 1;

bool isMove = false;
bool isDrop = false;
bool isGoNut = false;
uint8_t functionIndex = 0;

bool newData, runallowed = false; // booleans for new data from serial, and runallowed flag
char receivedCommand;             // character for commands
char clock_state;




// re calculate position to a minimum value with diection
int posCal(int handPos)
{

  handPos = handPos % fullRevolution;
  if (handPos >= 0 && handPos <= (fullRevolution / 2))
  {
    return handPos;
  }
  if (handPos > (fullRevolution / 2) && handPos <= fullRevolution)
  {
    return handPos - fullRevolution;
  }

  if (handPos < 0 && handPos >= -(fullRevolution / 2))
  {
    return handPos;
  }
  if (handPos < (fullRevolution / 2) && handPos > -fullRevolution)
  {
    return handPos + fullRevolution;
  }
}


void goNut()
{
  if ((move_finished == 0) && (stepper_Min.distanceToGo() == 0) && (stepper_Hr.distanceToGo() == 0))
  {
    Serial.println("--Completed--");
    move_finished = 1;
    stepper_Hr.setCurrentPosition(posCal(stepper_Hr.currentPosition())); // re calculate hand position
    //    stepper_Min.setCurrentPosition(posCal(stepper_Min.currentPosition()));    //re calculate hand position
    Serial.print("Hr current posistion");
    Serial.println(stepper_Hr.currentPosition());
    //    Serial.print("Min current posistion");
    //    Serial.println(stepper_Min.currentPosition());
    isMove = false;
  }
}

void showCorrectTimeFix()
{
  Serial.println("----- show correct time, Start-----");
  stepper_Hr.moveTo(abs(hours * STEPS_PER_HR - fullRevolution / 2));
  stepper_Min.moveTo((minutes * STEPS_PER_MIN - fullRevolution / 2));
  

  if ((stepper_Min.distanceToGo() == 0) && (stepper_Hr.distanceToGo() == 0))
  {
    stepper_Hr.setCurrentPosition(posCal(stepper_Hr.currentPosition())); // re calculate hand position
    Serial.print("Hr current posistion");
    Serial.println(stepper_Hr.currentPosition());

    stepper_Min.setCurrentPosition(posCal(stepper_Min.currentPosition())); // re calculate hand position
    Serial.print("Min current posistion");
    Serial.println(stepper_Min.currentPosition());
    clock_state = 'i';
    Serial.println("----- show correct time, Done-----");
  }
}

void moveToInput()
{
  Serial.println("----- move to input, start");
  
  // deal with the input _ Hr first
  //   travel_Hr = Serial.parseInt();
  //   travel_Min = Serial.parseInt();

  Serial.print("Moving Hr Stepper into position:  ");
  Serial.println(travel_Hr);
  Serial.print("Moving Min Stepper into position:  ");
  Serial.println(travel_Min);

  stepper_Hr.moveTo(travel_Hr);
  stepper_Min.moveTo(travel_Min);
  //  delay(500);

  // while ((stepper_Min.distanceToGo() != 0) || (stepper_Hr.distanceToGo() != 0))
  // {
  //   Serial.print("-  ");
  //   stepper_Hr.run();
  //   stepper_Min.run();
  // }

  if ((stepper_Min.distanceToGo() == 0) && (stepper_Hr.distanceToGo() == 0))
  {
    Serial.println("--Completed--");
    stepper_Hr.setCurrentPosition(posCal(stepper_Hr.currentPosition())); // re calculate hand position
                                                                         //  stepper_Min.setCurrentPosition(posCal(stepper_Min.currentPosition()));    //re calculate hand position
    Serial.print("Hr current posistion");
    Serial.println(stepper_Hr.currentPosition());
    //    Serial.print("Min current posistion");
    //    Serial.println(stepper_Min.currentPosition());
    clock_state = 'i';
  }

  Serial.println("----- move to input, done");
}

void dropHands()
{
  float dropFactor = 0.7;
  if (stepper_Hr.distanceToGo() == 0)
  {
    if (abs(stepper_Hr.currentPosition()) >= 0.01)
    {

      stepper_Hr.moveTo(-stepper_Hr.currentPosition() * dropFactor);
      Serial.print("Hr dropping - to next point:  ");
      Serial.println(-stepper_Hr.currentPosition() * dropFactor);
    }
  }
   if (abs(stepper_Hr.currentPosition()) <= 0.01)
  {
    clock_state = 'i';
  }

  // if ((stepper_Min.distanceToGo() == 0))
  // {
  //   if (abs(stepper_Min.currentPosition()) >=  0.01)
  //   {
  //     stepper_Min.moveTo(-stepper_Min.currentPosition() * dropFactor);
  //     Serial.print("Min dropping - to next point");
  //     Serial.println(-stepper_Min.currentPosition() * dropFactor);
  //   }
  // }

  // if ((abs(stepper_Hr.currentPosition()) <= 0.01) && (abs(stepper_Min.currentPosition()) <= 0.01))
  // {
  //   clock_state = 'i';
  // }


// if ((stepper_Hr.distanceToGo() == 0) || (stepper_Min.distanceToGo() == 0))
// {
//   if (abs(stepper_Hr.currentPosition()) >= 0.001)
//   {
//     stepper_Hr.moveTo(-stepper_Hr.currentPosition() * dropFactor);
//     Serial.print("Hr dropping - to next point   ");
//   }

//   if (abs(stepper_Min.currentPosition()) >= 0.001)
//   {
//     stepper_Min.moveTo(-stepper_Min.currentPosition() * dropFactor);
//     Serial.print("Min dropping - to next point");
//   }

//   if ((abs(stepper_Hr.currentPosition()) <= 0.01) && (abs(stepper_Min.currentPosition()) <= 0.01))
//   {
//    clock_state='i';
//   }
// }

}


void checkSerial()
{
  if (Serial.available() > 0) // if something comes
  {
    receivedCommand = Serial.read(); // read the first character from the serial command

    switch (receivedCommand)
    {
    case 't':
     
      clock_state = 't';
      break;

    case 'm':
      isMove = true;
      clock_state = 'm';
      travel_Hr = Serial.parseInt();
      travel_Min = Serial.parseInt();
      stepper_Hr.setMaxSpeed(800.0);
      stepper_Hr.setSpeed(800);
      stepper_Hr.setAcceleration(300.0);

      stepper_Min.setMaxSpeed(800.0);
      stepper_Min.setSpeed(800);
      stepper_Min.setAcceleration(300.0);

      break;

    case 'h':
      Serial.println("home");
      // home_Hr();
      // home_Min();
      break;

    case 'd':
      stepper_Hr.setMaxSpeed(800.0);
      stepper_Hr.setSpeed(660);
      // stepper_Hr.setAcceleration(300.0);

      // stepper_Min.setMaxSpeed(800.0);
      // stepper_Min.setSpeed(660);
      // stepper_Min.setAcceleration(300.0);
      clock_state = 'd';
      break;

     case 'n':
      isGoNut = true;
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
  // home_Hr();
  // home_Min();
  home_stepper_Hr.runHome();
  home_stepper_Min.runHome();


}

void loop()
{
  // input in serial monitor to test movement
  //   inputTest();
  // checkSerial();
  // if (millis()>=5000){
  //   clock_state='t';
  // }

  switch (clock_state)
  {
  case 't':
    showCorrectTimeFix();
    break;
  case 'm':
    moveToInput();
    break;

  case 'd':
    dropHands();

    break;

  case 'n':
    isGoNut = true;
    break;

  default:

    break;
  }

  stepper_Hr.run();
  // stepper_Min.run();
}
