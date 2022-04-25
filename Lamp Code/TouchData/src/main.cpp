#include <Arduino.h>
#include "Window.h"
#include "Classifier.h"


bool isRecording = false;

Window window;
Eloquent::ML::Port::Classifier clf;


#define TOUCH_PIN T0
int touchVal;
int preTouchVal;

unsigned long patTime;
int patternCounter1 = 0;

// smoothing parameters
int numRead = 10;

void setup()
{
  Serial.begin(115200);
  delay(3000);
}

void loop()
{

  if (Serial.available())
  {
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

  // print data with smoothing
    int senseSum = 0;
    for (int k = 0; k < numRead; k++)
    {
      senseSum += touchRead(TOUCH_PIN);
    }
    // Serial.print("-touchRead: ");
    touchVal = senseSum / numRead;
    //     Serial.print("touchVal");
    // Serial.println(touchVal);
    // get value using T0
    


float sample[] = {touchVal};

   // feed data to the window and wait until the window is full
  if (!window.transform(sample))
      return;

    // predict gesture
    delay(100);
  Serial.print(" --- Gesture: ");
  Serial.println(clf.predictLabel(window.features));

  
}