#include <Arduino.h>
#include "Window.h"
#include "Classifier.h"

bool isRecording = false;

Window window;
Eloquent::ML::Port::Classifier clf;

//ESP UART2
#define RXD2 16
#define TXD2 17

// #define TOUCH_PIN T0 // GPIO 4
#define TOUCH_PIN T4 // GPIO 13 //the most stable one so fat
// #define TOUCH_PIN T7 // GPIO 27
// #define TOUCH_PIN T8 // GPIO 33
// #define TOUCH_PIN T9 // GPIO 32
int touchVal;
int preTouchVal;

unsigned long patTime;
int patternCounter1 = 0;
String previousGesture;
String currentGesture;
int predictCounter;

// smoothing parameters
int numRead = 15;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  delay(3000);

}

void loop()
{

  if (Serial.available())
  {
     Serial2.write(Serial.read());  
    // type "record" in serial monitor to start collecting data
    // type anything else to stop recording
    String command = Serial.readStringUntil('\n');
    Serial.print("Command: ");
    Serial.println(command);
    // if user sent "record", start recording
    if (command.equals("record"))
    {
      Serial.println("Start recording...");
      isRecording = true;
    }
    // otherwise stop recording
    else
    {
      Serial.println("Stop recording...");
      isRecording = false;
     
    }


  }

  if (isRecording)
  {
    // print data with smoothing
    int senseSum = 0;
    for (int k = 0; k < numRead; k++)
    {
      senseSum += touchRead(TOUCH_PIN);
    }
    // Serial.print("-touchRead: ");
    touchVal = senseSum / numRead;
    Serial.println(touchVal); // get value using T0
  }

  /*********** Predit gesture ***************/
  // comment this part when collecting data 
  // uncomment if recognize touch pattern

  // print data with smoothing
  int senseSum = 0;
  for (int k = 0; k < numRead; k++)
  {
    senseSum += touchRead(TOUCH_PIN);
  }
  // Serial.print("-touchRead: ");
  touchVal = senseSum / numRead;
  // touchVal = map(touchVal,20,42,7,16);
      // Serial.print("touchVal");
  Serial.println(touchVal);
  // get value using T0

  float sample[] = {touchVal};

  // feed data to the window and wait until the window is full
  if (!window.transform(sample))
    return;

  // predict gesture
  // delay(300);
  
//   Serial.print(" --- Gesture: ");
//   Serial.println(clf.predictLabel(window.features));
  
//   // Serial.println(clf.predictLabel(window.features));
//   currentGesture = clf.predictLabel(window.features); 

// if (previousGesture == currentGesture){
//     predictCounter++;
// }else{
//   predictCounter=0;
// }
// if (predictCounter >10){
//   Serial.print(" --------------- Trigger Gesture: ");
//   Serial.println(clf.predictLabel(window.features));
// }
//   /**************************/
//   previousGesture = currentGesture;


}