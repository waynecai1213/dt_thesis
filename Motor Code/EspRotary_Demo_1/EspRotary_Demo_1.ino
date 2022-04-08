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

int stepsToTake = 128; //16*64=1024

#define hallPin_Hr  15    // 28BYJ48 pin 3
#define hallPin_Min  4    // 28BYJ48 pin 4


bool home_finished = true;
long initial_homing = -1;

uint8_t functionIndex = 0;


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
  stepper_Min.setMaxSpeed (1000.0);
  stepper_Min.setSpeed(800);
  stepper_Min.setAcceleration(400.0);


  stepper_Hr.setMaxSpeed(1000.0);
  stepper_Hr.setSpeed(800);
  stepper_Hr.setAcceleration(400.0);


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
while (digitalRead(hallPin_Hr)){
  
  
  }



}


void loop() {
  
//switch (functionIndex) {
//    case 0:
//     
//      break;
//    case 1:
//     
//      break;
//    case 2:
//     
//      break;
//  }

  if (!home_finished) {
    home_Hr();
    home_Min();
    if (stepper_Hr.currentPosition () == 0 && stepper_Min.currentPosition () == 0){
      home_finished = true;
      delay(3000);
       stepper_Hr.moveTo(500);
    }
  } else {

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

//     if (stepper_Hr.distanceToGo() == 0){
//      stepper_Hr.moveTo(-stepper_Hr.currentPosition()*0.5);
//     }
//    stepper_Hr.run();
    
  }
}


void home_Hr() {
  if (digitalRead(hallPin_Hr)) {
    
    stepper_Hr.move(stepsToTake / 4);
    stepper_Hr.run(); 
  } else {
    stepper_Hr.setCurrentPosition(0);
    stepper_Hr.setMaxSpeed (1000.0);
    stepper_Hr.setSpeed(400);
    stepper_Hr.setAcceleration(400.0);
    Serial.println("Hr Homed");
    
  }

}

void home_Min() {
  if (digitalRead(hallPin_Min)) {
    stepper_Min.setMaxSpeed (1000.0);
    stepper_Min.setSpeed(400);
    stepper_Min.setAcceleration(400.0);
    stepper_Min.move(-stepsToTake / 4);
    stepper_Min.run();
  } else {
    stepper_Min.setCurrentPosition(0);
       Serial.println("Min Homed");
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
