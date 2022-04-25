#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
//#include <Stepper.h>
#include <AccelStepper.h>

//**// config ESP-NOW connectino
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int a;
  int b;
} struct_message;

// Create a struct_message called rotaryData
struct_message rotaryData;

//**// config stepper motors
const int stepsPerRevolution = 4;  // change this to fit the number of steps per revolution


// ULN2003 Motor Driver Pins
#define motorPin1  13     // 28BYJ48 pin 1
#define motorPin2  12     // 28BYJ48 pin 2
#define motorPin3  14    // 28BYJ48 pin 3
#define motorPin4  27    // 28BYJ48 pin 4

#define motorPin5  26     // 28BYJ48 pin 1
#define motorPin6  25    // 28BYJ48 pin 2
#define motorPin7  33     // 28BYJ48 pin 3
#define motorPin8  32     // 28BYJ48 pin 4

// initialize the stepper library
AccelStepper stepper_Min(stepsPerRevolution, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper_Hr(stepsPerRevolution, motorPin5, motorPin7, motorPin6, motorPin8);
//max speed: 660

// the previous reading
int previous_a = 0;
int previous_b = 0;

//stepper motor steps & angles
int stepsToTake = 128; //16*64=1024
int fullRevolution = 1024;
int stepToTake_Angle = fullRevolution / 60;

int anglePosition_Hr;
int anglePosition_Min;

#define hallPin_Hr  15    // 28BYJ48 pin 3
#define hallPin_Min  4    // 28BYJ48 pin 4

long travel_Hr;  // Used to store the value entered in the Serial Monitor
long travel_Min;
bool home_finished = true;
long initial_homing = 1;
int move_finished = 1;

bool isMove = false;
bool isDrop = false;
bool isGoNut = false;
uint8_t functionIndex = 0;


bool newData, runallowed = false; // booleans for new data from serial, and runallowed flag
char receivedCommand; //character for commands


// callback function that will be executed when data is *received*
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&rotaryData, incomingData, sizeof(rotaryData));

  Serial.print("rotaryData_a: ");
  Serial.print(rotaryData.a);
  Serial.print("   |   ");
  Serial.print("rotaryData_b: ");
  Serial.println(rotaryData.b);
  int val_a = rotaryData.a;
  int val_b = rotaryData.b;

  //   Serial.println(val-previous);

  if (val_a != previous_a && val_a != 0 && val_a != 32)
  {

    stepper_Hr.move(stepsToTake * (val_a - previous_a));
    //    if(val_a ==0){
    //      stepper_Hr.moveTo(stepsToTake*(val_a-previous_a));
    //      }
  }

  if (val_b != previous_b && val_b != 0 && val_b != 32)
  {
    stepper_Min.move(-stepsToTake * (val_b - previous_b));

  }

  previous_a = val_a;
  previous_b = val_b;

  //  stepper_Hr.run();
  //  stepper_Min.run();
  //
}


//re calculate position to a minimum value with diection
int posCal(int handPos) {

  handPos = handPos % fullRevolution;
  if (handPos >= 0 && handPos <= (fullRevolution / 2)) {
    return handPos;
  }
  if (handPos > (fullRevolution / 2) && handPos <= fullRevolution) {
    return handPos - fullRevolution;
  }

  if (handPos < 0 && handPos >= -(fullRevolution / 2)) {
    return handPos;
  }
  if (handPos < (fullRevolution / 2) && handPos > -fullRevolution) {
    return handPos + fullRevolution;
  }

}


void home_Hr() {
  Serial.print("hallPin_Hr:  ");
  Serial.println(digitalRead(hallPin_Hr));
  Serial.println("Hr_initial_homing");
  while (digitalRead(hallPin_Hr)) {
    //    Serial.print("Hr_initial_homing:  ");
    //    Serial.println(initial_homing);
    stepper_Hr.moveTo(initial_homing);
    initial_homing++;   // Hand_Hr will move CCW
    stepper_Hr.run();
  }

  stepper_Hr.setCurrentPosition(0);
  stepper_Hr.setMaxSpeed (600.0);
  stepper_Hr.setSpeed(400);
  stepper_Hr.setAcceleration(400.0);
  initial_homing = -1;
  delay(500);

  while (!digitalRead(hallPin_Hr)) {
    stepper_Hr.moveTo(initial_homing);
    stepper_Hr.run();
    initial_homing--;
    Serial.print("Hr_initial_homing:  ");
    Serial.println(initial_homing);
  }

  stepper_Hr.setCurrentPosition(0);
  Serial.println("----- Hr Homed -----");
  stepper_Hr.setMaxSpeed (800.0);
  stepper_Hr.setSpeed(600);
  stepper_Hr.setAcceleration(400.0);

}


void home_Min() {
  Serial.print("hallPin_Hr:  ");
  Serial.println(digitalRead(hallPin_Min));
  Serial.println("Min_initial_homing");
  initial_homing = -1;
  while (digitalRead(hallPin_Min)) {
    //    Serial.print("Min_initial_homing:  ");
    //    Serial.println(initial_homing);
    stepper_Min.moveTo(initial_homing);
    initial_homing--;  // Hand_Hr will move CCW
    stepper_Min.run();
  }

  stepper_Min.setCurrentPosition(0);
  stepper_Min.setMaxSpeed (600.0);
  stepper_Min.setSpeed(400);
  stepper_Min.setAcceleration(400.0);
  initial_homing = 1;
  delay(500);

  while (!digitalRead(hallPin_Min)) {
    stepper_Min.moveTo(initial_homing);
    stepper_Min.run();
    initial_homing++;
    Serial.print("initial_homing:  ");
    Serial.println(initial_homing);
  }
  stepper_Min.setCurrentPosition(0);
  Serial.println("----- Min Homed -----");
  stepper_Min.setMaxSpeed (800.0);
  stepper_Min.setSpeed(600);
  stepper_Min.setAcceleration(400.0);
}


void showCorrectTimeFix() {
  Serial.println("----- show correct time, Start-----");
  stepper_Hr.moveTo((17 * 10));
  stepper_Min.moveTo(-(17 * 40));
  Serial.println("----- show correct time, Done-----");

}


void moveToInput() {

  Serial.println("----- move to input, start");
  stepper_Hr.setMaxSpeed(800.0);
  stepper_Hr.setSpeed(800);
  stepper_Hr.setAcceleration(300.0);

  stepper_Min.setMaxSpeed (800.0);
  stepper_Min.setSpeed(800);
  stepper_Min.setAcceleration(300.0);

  //deal with the input _ Hr first
  //  travel_Hr = Serial.parseInt();
  //  travel_Min = Serial.parseInt();

  move_finished = 0;
  Serial.print("Moving Hr Stepper into position:  ");
  Serial.println(travel_Hr);
  Serial.print("Moving Min Stepper into position:  ");
  Serial.println(travel_Min);

  stepper_Hr.moveTo(travel_Hr);
  stepper_Min.moveTo(travel_Min);
  //  delay(500);

  while ((stepper_Min.distanceToGo() != 0 ) || (stepper_Hr.distanceToGo() != 0 ) ) {
    Serial.print("-  ");
    stepper_Hr.run();
    stepper_Min.run();
  }
  

  if ( (move_finished == 0) && (stepper_Min.distanceToGo() == 0) &&  (stepper_Hr.distanceToGo() == 0)) {
    Serial.println("--Completed--");
    move_finished = 1;
    stepper_Hr.setCurrentPosition(posCal(stepper_Hr.currentPosition()));    //re calculate hand position
    //    stepper_Min.setCurrentPosition(posCal(stepper_Min.currentPosition()));    //re calculate hand position
    Serial.print("Hr current posistion");
    Serial.println(stepper_Hr.currentPosition());
    //    Serial.print("Min current posistion");
    //    Serial.println(stepper_Min.currentPosition());
    isMove = false;
  }

  Serial.println("----- move to input, done");

}


void inputTest() {
  while (Serial.available()) {
    move_finished = 0;
    travel_Min = Serial.parseInt();
    Serial.print("Moving Min Stepper into position:  ");
    Serial.println(travel_Min);
    stepper_Min.moveTo(travel_Min);
    delay(500);

  }

  if ((stepper_Min.distanceToGo() != 0 )) {
    Serial.print("moving  ");
    stepper_Min.run();
  }

  if ( (move_finished == 0) && (stepper_Min.distanceToGo() == 0) ) {
    Serial.println("--Completed--");
    move_finished = 1;
    //re calculate hand position
    stepper_Min.setCurrentPosition(posCal(stepper_Min.currentPosition()));
    Serial.println("cuurent posistion");
    Serial.print(stepper_Min.currentPosition());
  }

}


void dropHands() {
  
  stepper_Hr.setMaxSpeed(8000.0);
  stepper_Hr.setSpeed(660);
  stepper_Hr.setAcceleration(300.0);

  stepper_Min.setMaxSpeed (800.0);
  stepper_Min.setSpeed(660);
  stepper_Min.setAcceleration(300.0);


  float dropFactor = 0.4;
  if ((stepper_Hr.distanceToGo() == 0) || (stepper_Min.distanceToGo() == 0)) {
    if (abs(stepper_Hr.currentPosition()) >= 0.001) {
      stepper_Hr.moveTo(-stepper_Hr.currentPosition()*dropFactor);
      Serial.print("Hr dropping - to next point   ");
    }
    if (abs(stepper_Min.currentPosition()) >= 0.001) {
      stepper_Min.moveTo(-stepper_Min.currentPosition()*dropFactor);
      Serial.print("Min dropping - to next point");
    }

    if ( (abs(stepper_Hr.currentPosition()) <= 0.01) && (abs(stepper_Min.currentPosition()) <= 0.01)) {
      isDrop = false;
    }
  }
  stepper_Hr.run();
  stepper_Min.run();

}


void goNut() {
  if ( (move_finished == 0) && (stepper_Min.distanceToGo() == 0) &&  (stepper_Hr.distanceToGo() == 0)) {
    Serial.println("--Completed--");
    move_finished = 1;
    stepper_Hr.setCurrentPosition(posCal(stepper_Hr.currentPosition()));    //re calculate hand position
    //    stepper_Min.setCurrentPosition(posCal(stepper_Min.currentPosition()));    //re calculate hand position
    Serial.print("Hr current posistion");
    Serial.println(stepper_Hr.currentPosition());
    //    Serial.print("Min current posistion");
    //    Serial.println(stepper_Min.currentPosition());
    isMove = false;
  }
}


void chaseLoop() {
  //home_Hr();
  if (stepper_Hr.currentPosition() == 0) {
    stepper_Min.moveTo(-stepsToTake);
    stepper_Min.run();
    home_Min();
  }

  if (stepper_Min.currentPosition() == 0) {
    stepper_Hr.moveTo(stepsToTake / 4);
    stepper_Hr.run();
    home_Hr();
  } else {
    home_Min();
  }
}


void checkSerial() {
  if (Serial.available() > 0) //if something comes
  {
    receivedCommand = Serial.read(); // read the first character from the serial command

    switch (receivedCommand) {
      case 't':
        showCorrectTimeFix();
        break;

      case 'm':
        isMove = true;
        travel_Hr = Serial.parseInt();
        travel_Min = Serial.parseInt();
        break;

      case 'h':
        Serial.println("home");
        home_Hr();
        home_Min();
        break;

      case 'd':

        isDrop = true;
        break;
      case 'n':

        isGoNut = true;
        break;

    }
  }

}


void setup() {
  //Hall sensor
  pinMode(hallPin_Hr, INPUT);
  pinMode(hallPin_Min, INPUT);

  //set stepper motors speed
  stepper_Hr.setMaxSpeed(400.0);
  stepper_Hr.setSpeed(200);
  stepper_Hr.setAcceleration(200.0);

  stepper_Min.setMaxSpeed (400.0);
  stepper_Min.setSpeed(200);
  stepper_Min.setAcceleration(200.0);

  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);


  /*Homing Stepper Motos*/
  home_Hr();
  home_Min();
}


void loop() {
  //input in serial monitor to test movement
  //  inputTest();
  checkSerial();
   stepper_Hr.run();
   stepper_Min.run();

  if (isDrop) {
    dropHands();
  }

  if (isMove) {
    moveToInput();
  }

}


