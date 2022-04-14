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


// the previous reading
int previous_a = 0;
int previous_b = 0;

//stepper motor steps & angles
int stepsToTake = 128; //16*64=1024
int fullRevolution = 1080;
int angle_Unit = fullRevolution/60;

int moveAngle_Hr;
int moveAngle_Min;

#define hallPin_Hr  15    // 28BYJ48 pin 3
#define hallPin_Min  4    // 28BYJ48 pin 4

long Travel_Hr;  // Used to store the value entered in the Serial Monitor
long Travel_Min;
bool home_finished = true;
long initial_homing = 1;
int move_finished = 1;

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




void setup() {

  //Hall sensor
  pinMode(hallPin_Hr, INPUT);
  pinMode(hallPin_Min, INPUT);

  //set stepper motors speed
  stepper_Min.setMaxSpeed (400.0);
  stepper_Min.setSpeed(400);
  stepper_Min.setAcceleration(200.0);


  stepper_Hr.setMaxSpeed(1000.0);
  stepper_Hr.setSpeed(800);
  stepper_Hr.setAcceleration(200.0);


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
    inputTest();
//  checkSerial();
//  stepper_Hr.run();
//  stepper_Min.run();
}


void home_Hr() {
  Serial.print("hallPin_Hr:  ");
  Serial.println(digitalRead(hallPin_Hr));
  while (digitalRead(hallPin_Hr)) {
    Serial.print("Hr_initial_homing:  ");
    Serial.println(initial_homing);
    stepper_Hr.moveTo(initial_homing);
    initial_homing++;   // Hand_Hr will move CCW
    stepper_Hr.run();
  }

  stepper_Hr.setCurrentPosition(0);
  stepper_Hr.setMaxSpeed (400.0);
  stepper_Hr.setSpeed(200);
  stepper_Hr.setAcceleration(200.0);
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
  stepper_Hr.setMaxSpeed (1000.0);
  stepper_Hr.setSpeed(800);
  stepper_Hr.setAcceleration(400.0);

}

void home_Min() {
  Serial.println(digitalRead(hallPin_Min));
  initial_homing = -1;
  while (digitalRead(hallPin_Min)) {
    Serial.print("Min_initial_homing:  ");
    Serial.println(initial_homing);
    stepper_Min.moveTo(initial_homing);
    initial_homing--;  // Hand_Hr will move CCW
    stepper_Min.run();
  }

  stepper_Min.setCurrentPosition(0);
  stepper_Min.setMaxSpeed (400.0);
  stepper_Min.setSpeed(200);
  stepper_Min.setAcceleration(200.0);
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
  stepper_Min.setMaxSpeed (1000.0);
  stepper_Min.setSpeed(800);
  stepper_Min.setAcceleration(400.0);
}


void checkSerial() {
  if (Serial.available() > 0) //if something comes
  {
    receivedCommand = Serial.read(); // read the first character from the serial command

    switch (receivedCommand) {
      case 't':
        Serial.println("show time");
        showCorrectTimeFix();
        break;
      case 'b':
        Serial.println("b");
        break;
      case 'h':
        Serial.println("home");
        home_Hr();
        home_Min();
        break;

    }
  }

}

void inputTest() {
  while (Serial.available()) {
    Travel_Min = Serial.parseInt();
    if (Travel_Min != 0) {
      move_finished = 0;
      Serial.print("Moving Min Stepper into position:  ");
      Serial.println(Travel_Min);
      stepper_Min.moveTo(Travel_Min);
      delay(500);
    } else {
      home_Min();
    }
  }

  if ((stepper_Min.distanceToGo() != 0 )) {
    Serial.print("moving  ");
    stepper_Min.run();
  }

  if ( (move_finished == 0) && (stepper_Min.distanceToGo() == 0) ) {
    Serial.println("--Completed--");
    move_finished = 1;
  }

}


void showCorrectTimeFix() {
  stepper_Hr.moveTo((17 * 10));
  stepper_Min.moveTo(-(17 * 40));

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

void store() {
  //  if (!home_finished) {
  //    home_Hr();
  //    home_Min();
  //    if (stepper_Hr.currentPosition () == 0 && stepper_Min.currentPosition () == 0){
  //      home_finished = true;
  //      delay(3000);
  //       stepper_Hr.moveTo(500);
  //    }
  //  } else {

  //    if (stepper_Min.distanceToGo() == 0)
  //    {
  //      // Random change to speed, position and acceleration
  //      // Make sure we dont get 0 speed or accelerations
  ////      delay(1000);
  //      stepper_Min.moveTo(rand() % 200);
  //      stepper_Min.setMaxSpeed((rand() % 200) + 1);
  //      stepper_Min.setAcceleration((rand() % 200) + 1);
  //    }
  //    stepper_Min.run();

  // bounce around a position
  //     if (stepper_Hr.distanceToGo() == 0){
  //      stepper_Hr.moveTo(-stepper_Hr.currentPosition()*0.5);
  //     }
  //    stepper_Hr.run();
  //  }

}
