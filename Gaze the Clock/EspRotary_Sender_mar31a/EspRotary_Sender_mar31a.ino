//credit to: https://www.brainy-bits.com/

//library for Rotary Encoder
#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"

//library for for
#include <esp_now.h>
#include <WiFi.h>
#include <math.h>

uint8_t broadcastAddress[] = {0xC8, 0xC9, 0xA3, 0xC8, 0xA9, 0x00}; // Address of the receiver ESP32
// Structure to send data
// Must match the receiver structure
typedef struct struct_message {
  int a;
  int b;
} struct_message;

// Create a struct_message called rotaryData
struct_message rotaryData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


//controller config
/*
  connecting Rotary encoder
  Rotary encoder side    MICROCONTROLLER side
  -------------------    ---------------------------------------------------------------------
  CLK (A pin)            any microcontroler intput pin with interrupt ->  example pin 32
  DT (B pin)             any microcontroler intput pin with interrupt ->  example pin 21
  SW (button pin)        any microcontroler intput pin with interrupt ->  example pin 25
  GND - to microcontroler GND
  VCC                    microcontroler VCC (then set ROTARY_ENCODER_VCC_PIN -1)
*/
#define ROTARY_1_A_PIN 19
#define ROTARY_1_B_PIN 18
#define ROTARY_1_BUTTON_PIN 5
#define ROTARY_1_VCC_PIN -1 /* 27 put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */

#define ROTARY_2_A_PIN 23
#define ROTARY_2_B_PIN 22
#define ROTARY_2_BUTTON_PIN 21
#define ROTARY_2_VCC_PIN -1

//depending on your encoder - try 1,2 or 4 to get expected behaviour
//#define ROTARY_1_STEPS 1
//#define ROTARY_1_STEPS 2
#define ROTARY_1_STEPS 4
#define ROTARY_2_STEPS 4

//instead of changing here, rather change numbers above
AiEsp32RotaryEncoder rotaryEncoder1 = AiEsp32RotaryEncoder(ROTARY_1_A_PIN, ROTARY_1_B_PIN, ROTARY_1_BUTTON_PIN, ROTARY_1_VCC_PIN, ROTARY_1_STEPS);
AiEsp32RotaryEncoder rotaryEncoder2 = AiEsp32RotaryEncoder(ROTARY_2_A_PIN, ROTARY_2_B_PIN, ROTARY_2_BUTTON_PIN, ROTARY_2_VCC_PIN, ROTARY_2_STEPS);

int rotaryValue_A;
int rotaryValue_B;

int rotaryPosition_1=0;    // To store Stepper Motor Position
int rotaryPosition_2=0; 

void rotary_1_onButtonClick()
{
    rotaryPosition_1 = 0;
  static unsigned long lastTimePressed = 0;
  //ignore multiple press in that time milliseconds
  if (millis() - lastTimePressed < 500)
  {
    return;
  }
  lastTimePressed = millis();
  Serial.print("button pressed ");
  Serial.print(millis());
  Serial.println(" milliseconds after restart");
}

void rotary_2_onButtonClick()
{

  rotaryPosition_2 = 0;
  
  static unsigned long lastTimePressed = 0;
  //ignore multiple press in that time milliseconds
  if (millis() - lastTimePressed < 500)
  {
    return;
  }
  lastTimePressed = millis();
  Serial.print("button pressed ");
  Serial.print(millis());
  Serial.println(" milliseconds after restart");
}


void rotary_1_loop()
{
  //dont print anything unless value changed
  if (rotaryEncoder1.encoderChanged())
  {
    rotaryValue_A = rotaryEncoder1.readEncoder();
    rotaryValue_B = rotaryEncoder2.readEncoder();

    rotaryData.a = rotaryValue_A;
    rotaryData.b = rotaryValue_B;
    Serial.print("Value_A: ");
    Serial.print(rotaryEncoder1.readEncoder());
    Serial.print("   |   ");
    Serial.print("Value_B: ");
    Serial.println(rotaryEncoder2.readEncoder());

    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &rotaryData, sizeof(rotaryData));
    if (result == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }


  }
  if (rotaryEncoder1.isEncoderButtonClicked())
  {
    rotary_1_onButtonClick();
  }
}


void rotary_2_loop()
{
  //dont print anything unless value changed
  if (rotaryEncoder2.encoderChanged())
  {
    rotaryValue_B = rotaryEncoder2.readEncoder();
    rotaryData.b = rotaryValue_B;

    Serial.print("Value_A: ");
    Serial.print(rotaryEncoder1.readEncoder());
    Serial.print("   |   ");
    Serial.print("Value_B: ");
    Serial.println(rotaryEncoder2.readEncoder());
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &rotaryData, sizeof(rotaryData));
    if (result == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }


  }
  if (rotaryEncoder2.isEncoderButtonClicked())
  {
    rotary_2_onButtonClick();
  }
}

void IRAM_ATTR readEncoderISR()
{
  rotaryEncoder1.readEncoder_ISR();
  rotaryEncoder2.readEncoder_ISR();
}

void setup()
{
  Serial.begin(115200);

  //Initialize rotary encoder
  rotaryEncoder1.begin();
  rotaryEncoder1.setup(readEncoderISR);

  rotaryEncoder2.begin();
  rotaryEncoder2.setup(readEncoderISR);

  //set boundaries and if values should cycle or not
    /*Rotary acceleration introduced 25.2.2021.
     in case range to select is huge, for example - select a value between 0 and 1000 and we want 785
     without accelerateion you need long time to get to that number
     Using acceleration, faster you turn, faster will the value raise.
     For fine tuning slow down.
  */

  bool circleValues_1 = true;
  bool circleValues_2 = true;
  rotaryEncoder1.setBoundaries(0, 32, circleValues_1); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
  rotaryEncoder1.disableAcceleration(); //acceleration is now enabled by default - disable if you dont need it
  //  rotaryEncoder1.setAcceleration(250); //or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration
  rotaryEncoder2.setBoundaries(0, 32, circleValues_2); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
  rotaryEncoder2.disableAcceleration();
  //  rotaryEncoder2.setAcceleration(50); //or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration

  /* Set up ESP_NOW
  */
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we register for Send CB to get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }


}

void loop()
{
  /*Get rotary encoder values
  */
  //  //in loop call your custom function which will process rotary encoder values
  //  rotary_1_loop();
  //  rotary_2_loop();

  //dont print anything unless value changed
  if (rotaryEncoder1.encoderChanged() || rotaryEncoder2.encoderChanged())
  {
    rotaryValue_A = rotaryEncoder1.readEncoder();
    rotaryValue_B = rotaryEncoder2.readEncoder();

    rotaryData.a = rotaryValue_A;
    rotaryData.b = rotaryValue_B;
    Serial.print("rotaryValue_A: ");
    Serial.print(rotaryValue_A);
    Serial.print("   |   ");
    Serial.print("rotaryValue_B: ");
    Serial.println(rotaryValue_B);

    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &rotaryData, sizeof(rotaryData));
    if (result == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }


  }

  if (rotaryEncoder1.isEncoderButtonClicked())
  {
    rotary_1_onButtonClick();
  }

  if (rotaryEncoder2.isEncoderButtonClicked())
  {
    rotary_2_onButtonClick();
  }

//  delay(10); //or do whatever you need to do...


}
