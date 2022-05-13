#include <Arduino.h>
// #include <esp_now.h>
#include <WiFi.h>
//#include <Stepper.h>
#include <AccelStepper.h>

// my own library
#include <Homing.h>
#include <ClockStates.h>

char receivedCommand; // character for commands

// config for AP mode
const char *ssid = "GAZE the CLOCK";
const char *password = "gazetheclock";
WiFiServer server(80);
String html = "<!DOCTYPE HTML>\
<html>\
<body>\
<center><h1>GAZE the CLOCK Soft access point</h1></center>\
<center><h3>Soft access point</h3></center>\
<form>\
<input type=\"char\" name=\"Input_State\"> \
<input type=\"submit\" value=\"Sumbit State\"> \
</form>\
</body>\
</html>";

void Connect_WiFi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.println("WL_CONNECTING");
  }
}

// for homing, 1/-1 represent rotation direction
Homing home_stepper_Hr(hallPin_Hr, stepper_Hr, 1);     // CW
Homing home_stepper_Min(hallPin_Min, stepper_Min, -1); // CW

char previousCommand;
int greetingDir_Hr = 1;
int greetingDir_Min = 1;
char clock_state; // move this variable to "ClockStates.h" would cause the variable be reset

// for real time
long minuteMillis = 3000;
long previousMillis;

// real time parameters
long hours = 1;
long minutes = 15;


void switchCommand(){
    switch (receivedCommand)
      {
      // homing
      case 'h':
        // stepper_Hr.stop();
        // stepper_Min.stop();
        // stepper_Hr.runToPosition();
        // stepper_Min.runToPosition();
        Serial.println("start homing");
        home_stepper_Hr.runHome();
        home_stepper_Min.runHome();

        stepper_Hr.setCurrentPosition(0);
        stepper_Hr.setMaxSpeed(600.0);
        stepper_Hr.setAcceleration(400.0);

        stepper_Min.setCurrentPosition(0);
        stepper_Min.setMaxSpeed(600.0);
        stepper_Min.setAcceleration(400.0);

        Serial.println("done homing");   
        clock_state = 'h';
        break;

      // initiate real time mode
      case 'i': // h > i
        Serial.println("----- show correct time, Start-----");
        stepper_Hr.setMaxSpeed(600.0);
        stepper_Hr.setAcceleration(1200.0);

        stepper_Min.setMaxSpeed(800.0);
        stepper_Min.setAcceleration(2000.0);
        
        stepper_Hr.move(100);
        stepper_Min.move(100);
        while (stepper_Hr.distanceToGo() != 0 || stepper_Min.distanceToGo() != 0)
        {
          stepper_Hr.run();
          stepper_Min.run();
        }
        delay(100);

        stepper_Hr.moveTo(abs(hours * STEPS_PER_HR - fullRevolution / 2));
        stepper_Min.moveTo((minutes * STEPS_PER_MIN - fullRevolution / 2));

        clock_state = 'i';
        
  
        break;

      // move minute hand as real time ... Speed up ...
      case 't': //
        Serial.println("----- Move minute hand as real time -----");
        previousMillis = millis();
        minutes++;
        stepper_Min.moveTo((minutes * STEPS_PER_MIN - fullRevolution / 2));
        clock_state = 't';
        break;

      // drop hands
      case 'd':
            minutes++;
        // stop the hands and recalculate position
        stepper_Hr.stop();
        stepper_Min.stop();
        stepper_Hr.runToPosition();
        stepper_Min.runToPosition();
        reCalPos();

          // set
          stepper_Hr.setMaxSpeed(1000.0);
          stepper_Hr.setAcceleration(2000.0);

          stepper_Min.setMaxSpeed(1000.0);
          stepper_Min.setAcceleration(3000.0);
        clock_state = 'd';
        break;

        // drop hands with anticipation
      case 'D':
          minutes++;

        // stop the hands and recalculate position
        stepper_Hr.setMaxSpeed(1000.0);
        stepper_Hr.setAcceleration(3000.0);

        stepper_Min.setMaxSpeed(1000.0);
        stepper_Min.setAcceleration(4000.0);
        if (stepper_Hr.currentPosition() > 0)
        {
          stepper_Hr.move(150);
          stepper_Min.move(150);
        }
        else
        {
          stepper_Hr.move(-150);
          stepper_Min.move(-150);
        }
  
        while (stepper_Hr.distanceToGo() != 0 || stepper_Min.distanceToGo() != 0)
        {
          stepper_Hr.run();
          stepper_Min.run();
        }
         delay(50);
        // stepper_Hr.stop();
        // stepper_Min.stop();
        // stepper_Hr.runToPosition();
        // stepper_Min.runToPosition();

        // set

        clock_state = 'D';
        break;

        // small bounce b/w
      case 'b':
        // set
        stepper_Hr.setMaxSpeed(700.0);
        stepper_Hr.setAcceleration(1600.0);

        stepper_Min.setMaxSpeed(700.0);
        stepper_Min.setAcceleration(2000.0);
        clock_state = 'b';
        stepper_Hr.moveTo(150);
        stepper_Min.moveTo(150);
        break;

        // rotate left
      case 'l':
        stepper_Hr.setMaxSpeed(800.0);
        stepper_Hr.setAcceleration(600.0);
        stepper_Min.setMaxSpeed(800.0);
        stepper_Min.setAcceleration(600.0);

        stepper_Hr.moveTo(fullRevolution);
        stepper_Min.moveTo(fullRevolution);

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
        if (clock_state != 's')
        {
          stepper_Hr.setMaxSpeed(600.0);
          stepper_Min.setMaxSpeed(600.0);
        }
        stepper_Hr.setSpeed(input_Speed);
        stepper_Min.setSpeed(-input_Speed);
        break;

      //
      case 'g':
        stepper_Min.setMaxSpeed(600.0);
        stepper_Min.setAcceleration(400.0);
        stepper_Min.runToNewPosition(400);

        stepper_Hr.setMaxSpeed(600.0);
        stepper_Hr.setAcceleration(400.0);
        stepper_Hr.runToNewPosition(400);

        clock_state = 'g';
        break;

        // Greeting! waving hands
      case 'G':
        stepper_Min.setMaxSpeed(1000.0);
        stepper_Min.setAcceleration(2000.0);
        // stepper_Min.runToNewPosition(260);
        

        stepper_Hr.setMaxSpeed(800.0);
        stepper_Hr.setAcceleration(1200.0);
        // stepper_Hr.runToNewPosition(260);

        stepper_Min.moveTo(120);
         stepper_Hr.moveTo(100);

        clock_state = 'G';
        break;

        // Bye-Bye
       case 'B':
          stepper_Min.setMaxSpeed(1000.0);
          stepper_Min.setAcceleration(2000.0);
          stepper_Min.moveTo(400);

          stepper_Hr.setMaxSpeed(800.0);
          stepper_Hr.setAcceleration(1500.0);
          stepper_Hr.moveTo(0);

          clock_state = 'B';
          break;
      }

}



void checkAPInput()
{
  WiFiClient client = server.available();
  if (client)
  {
    String request = client.readStringUntil('\r');
    if (request.indexOf("Input_State") != -1)
    {
      Serial.print("receive AP input: ");
      receivedCommand = request.charAt(request.lastIndexOf("=") + 1);
      Serial.println(receivedCommand);
      switchCommand();
    
    }
    client.print(html);
    request = "";
  }
}

void checkSerial()
{
  if (Serial.available() > 0) // if something comes
  {
    Serial.println("receive serial input");
    receivedCommand = Serial.read(); // read the first character from the serial command
    switchCommand();
  
  }
}

void setup()
{
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.println("Serial Connnected");

  // Setting soft access point mode
  Serial.println("Setting soft access point mode");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP); // http://192.168.4.1/
  server.begin();

  /*Homing Stepper Motos*/ // this homing function should go before Serial print and AP mode setting, otherwise it won't print or connect...
  home_stepper_Hr.runHome();
  home_stepper_Min.runHome();

   // Hall sensor
  pinMode(hallPin_Hr, INPUT);
  pinMode(hallPin_Min, INPUT);

 
}

/*************************************************************************/

void loop()
{
  checkAPInput();
  // checkSerial();

  switch (clock_state)
  {
  case 'h':

  break;
  case 'i':
    // initiate real time
    reCalPos();

    stepper_Hr.run();
    stepper_Min.run();
    previousCommand = 'i';
    break;

  case 't':
    // move mintue hand as real time
    Serial.println(millis() - previousMillis);
    if ((millis() - previousMillis) >= minuteMillis)
    {
      Serial.println("minute ++");
      previousMillis = millis();
      minutes++;
      stepper_Min.moveTo((minutes * STEPS_PER_MIN - fullRevolution / 2));
    }
    if (stepper_Min.distanceToGo() != 0)
    {
      stepper_Min.run();
    }
    break;

  case 'b':
    if (stepper_Hr.distanceToGo() == 0)
    {
      stepper_Hr.moveTo(-stepper_Hr.currentPosition());
    }

    if (stepper_Min.distanceToGo() == 0)
    {
      stepper_Min.moveTo(-stepper_Min.currentPosition());
    }
    stepper_Hr.run();
    stepper_Min.run();

    break;

  case 'd':
    dropHands();
    stepper_Hr.run();
    stepper_Min.run();
    previousCommand = 'd';
    break;

  case 'D':
    dropHands();
    stepper_Hr.run();
    stepper_Min.run();

    break;

  case 'l':
    reCalPos();
    stepper_Hr.run();
    stepper_Min.run();
    break;

  case 'm':
    reCalPos();
    stepper_Hr.run();
    stepper_Min.run();
    previousCommand = 'm';
    break;

  case 'n':
    stepper_Hr.runSpeed();
    stepper_Min.runSpeed();
    previousCommand = 'n';
    break;
  case 's':
    stepper_Hr.runSpeed();
    stepper_Min.runSpeed();
    previousCommand = 's';
    break;

  case 'g':
    if (stepper_Min.distanceToGo() == 0)
    {
      // delay(50);
      greetingDir_Min = greetingDir_Min * (-1);
      // Random change to speed, position and acceleration
      // Make sure we dont get 0 speed or accelerations
      stepper_Min.moveTo((rand() % 40 + 20) * greetingDir_Min + 400);
      // stepper_Min.setMaxSpeed(rand() % 100+ 400);
      // stepper_Min.setAcceleration((rand() % 100+100) + 200);
    }

    if (stepper_Hr.distanceToGo() == 0)
    {
      // delay(50);
      greetingDir_Hr = greetingDir_Hr * (-1);
      // Random change to speed, position and acceleration
      // Make sure we dont get 0 speed or accelerations
      stepper_Hr.moveTo((rand() % 40 + 20) * greetingDir_Hr + 400);
      // stepper_Min.setMaxSpeed(rand() % 100+ 400);
      // stepper_Min.setAcceleration((rand() % 100+100) + 200);
    }

    stepper_Min.run();
    stepper_Hr.run();
    break;

  case 'G':

    if (stepper_Min.distanceToGo() == 0)
    {
      // delay(50);
      greetingDir_Min = greetingDir_Min * (-1);
      // Random change to speed, position and acceleration
      // Make sure we dont get 0 speed or accelerations
      stepper_Min.moveTo((rand() % 120 + 20) * greetingDir_Min + 260);
      // stepper_Min.setMaxSpeed(rand() % 100+ 400);
      // stepper_Min.setAcceleration((rand() % 100+100) + 200);
    }

    if (stepper_Hr.distanceToGo() == 0)
    {
      // delay(50);
      greetingDir_Hr = greetingDir_Hr * (-1);
      // Random change to speed, position and acceleration
      // Make sure we dont get 0 speed or accelerations
      stepper_Hr.moveTo((rand() % 120 + 20) * greetingDir_Hr + 260);
      // stepper_Min.setMaxSpeed(rand() % 100+ 400);
      // stepper_Min.setAcceleration((rand() % 100+100) + 200);
    }

    stepper_Min.run();
    stepper_Hr.run();
    break;

  case 'B':
    if (stepper_Min.distanceToGo() == 0)
    {
      // delay(50);
      greetingDir_Min = greetingDir_Min * (-1);
      // Random change to speed, position and acceleration
      // Make sure we dont get 0 speed or accelerations
      stepper_Min.moveTo((rand() % 40 + 40) * greetingDir_Min + 400);
      // stepper_Min.setMaxSpeed(rand() % 100+ 400);
      // stepper_Min.setAcceleration((rand() % 100+100) + 200);
    }
    stepper_Min.run();
    stepper_Hr.run();
    break;

  default:
    // Serial.print("clock_state:");
    // Serial.println(clock_state);

    break;
  }
}
