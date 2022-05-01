
#include <Arduino.h>
#include <AccelStepper.h>

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

// max speed: 660

// stepper motor steps & angles
int stepsToTake = 128; // 16*64=1024; one full revolution = 1024;
int fullRevolution = 1024;
int stepToTake_Angle = fullRevolution / 60;
#define STEPS_PER_HR 85  // 1024/12
#define STEPS_PER_MIN 17 // 1024/60

// real time parameters
long hours = 4;
long minutes = 50;

// -  Hand_Hr will move CW
// +  Hand_Min will move CW


long travel_Hr; // Used to store the value entered in the Serial Monitor
long travel_Min;

int input_Speed; 

int move_finished = 1;


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

// re calculate hand position
void reCalPos()
{
    
    // re calculate hand position when reaching target position
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

void goNut()
{

}

void showCorrectTimeFix()
{
    reCalPos();
}

void moveToInput()
{
    reCalPos();
}

void dropHands()
{
   
    float dropFactor = 0.5;

    if ((stepper_Hr.distanceToGo() == 0))
    {
        if (abs(stepper_Hr.currentPosition()) >= 0.001)
        {
            stepper_Hr.moveTo(-stepper_Hr.currentPosition() * dropFactor);
        }
    }

    if (stepper_Min.distanceToGo() == 0)
    {
        if (abs(stepper_Min.currentPosition()) >= 0.001)
        {
            stepper_Min.moveTo(-stepper_Min.currentPosition() * dropFactor);
        }
    }

    if ((abs(stepper_Hr.currentPosition()) <= 0.001) && (abs(stepper_Min.currentPosition()) <= 0.001))
    {
        clock_state = 'i';
    }
}
