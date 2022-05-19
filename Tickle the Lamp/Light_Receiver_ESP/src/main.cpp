#include <Arduino.h>
#include <FastLED.h>

char receivedCommand;

#define RXD2 16
#define TXD2 17

// Confif LED
#define DEFAULT_LED_PIN 2
#define NUM_LEDS 15
#define DATA_PIN 15
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

uint8_t max_bright = 200;
uint8_t brightnessValue = 0;
bool isEnd = false;

uint8_t colorIndex[NUM_LEDS];

char functionIndex = 'i';
char lastFunctionIndex = 'i';

uint8_t patCounter = 0;
uint8_t upCounter = 0;
int breathSpeed = 20;
unsigned long preTime;
uint8_t downCounter = 0;

CRGB leds[NUM_LEDS];

void idle_on()
{
  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.setBrightness(max_bright);
  FastLED.show();
}

void tickle()
{
  EVERY_N_MILLISECONDS(200)
  {
    leds[random8(0, NUM_LEDS - 1)] = CRGB::White;
  }
  fadeToBlackBy(leds, NUM_LEDS, 1);
  FastLED.show();
}

void tickle_gradualUp(){
  for (uint8_t i = NUM_LEDS / 2; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::White;
    leds[NUM_LEDS - i] = CRGB::White;
    // fadeToBlackBy(leds, NUM_LEDS, 10);
    FastLED.show();
    delay(60);
  }
}


void breath()
{
  // time affect breathing speed
  EVERY_N_MILLISECONDS(breathSpeed)
  {
    if (patCounter <= 5)
    {
      if (brightnessValue < max_bright / 2 && !isEnd)
      {
        brightnessValue++;
      }
      else
      {
        brightnessValue--;
      }
      if (brightnessValue == 20 || brightnessValue == max_bright / 2)
      {
        // breathSpeed = 20;
        isEnd = !isEnd;
        patCounter++;
        delay(random(100, 200));
      }
    }
  }
  // pat
  if (patCounter == 6 && brightnessValue > 0)
  {
    brightnessValue--;
  }
  fill_solid(leds, NUM_LEDS, CRGB::White);
  int eased_brightnessValue = ease8InOutCubic(brightnessValue);
  // int eased_brightnessValue = map(ease8InOutCubic(brightnessValue), 0, ease8InOutCubic(max_bright), 0, max_bright);
  FastLED.setBrightness(eased_brightnessValue);
  FastLED.show();
}

// gradual up
void contantTouch()
{
  EVERY_N_MILLISECONDS(15)
  {
    if (brightnessValue < max_bright / 3 && upCounter == 0)
    {
      brightnessValue++;
    }
    else if (upCounter == 0)
    {
      upCounter = 1;
      delay(200);
    }

    if (upCounter == 1 && brightnessValue > 0)
    {
      brightnessValue--;
    }
    else if (upCounter == 1)
    {
      upCounter = 2;
      delay(500);
    }

    int currentTime;
    if (upCounter == 2 && brightnessValue < max_bright)
    {
      brightnessValue++;
      currentTime = millis();
    }
    else if (upCounter == 2)
    {
      if ((millis() - currentTime) > 5000)
      {
        // functionIndex = 4;
      }
    }
  }
  fill_solid(leds, NUM_LEDS, CRGB::White);
  // ease in out funtion: https://github.com/FastLED/FastLED/wiki/High-performance-math#easing-and-linear-interpolation-functions
  int eased_brightnessValue = map(ease8InOutCubic(brightnessValue), 0, ease8InOutCubic(max_bright), 0, max_bright);
  FastLED.setBrightness(eased_brightnessValue);
  FastLED.show();
}

void configInfo()
{
  if (functionIndex == 'p')
  {
    brightnessValue = max_bright / 2;
    patCounter = 0;
  }
  if (functionIndex == 't')
  {
    FastLED.setBrightness(max_bright);
  }
}

void setup()
{
  pinMode(DEFAULT_LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // initiate LED
  LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(max_bright);
  FastLED.setCorrection(TypicalPixelString);
  // https://fastled.io/docs/3.1/group___color_enums.html // Candle:1900K
  //  https://www.lumens.com/the-edit/the-guides/understanding-kelvin-color-temperature/
  FastLED.setTemperature(Candle);
}

void loop()
{
  if (Serial2.available() > 0)
  {
    functionIndex = Serial2.read(); // gets one byte from serial buffer
    configInfo();
  }

  if (Serial.available() > 0)
  {
    functionIndex = Serial.read(); // gets one byte from serial buffer
    configInfo();
  }

  switch (functionIndex)
  {
  
  case 't':
    digitalWrite(DEFAULT_LED_PIN, HIGH);
    tickle();
    lastFunctionIndex = 't';
    break;

  case 'f':
    digitalWrite(DEFAULT_LED_PIN, LOW);
 
    break;

  case 'p':
    digitalWrite(DEFAULT_LED_PIN, LOW);
    breath();
    lastFunctionIndex = 'p';
    break;

  case 'd':
   digitalWrite(DEFAULT_LED_PIN, HIGH);
    if (lastFunctionIndex == 't'){
       tickle_gradualUp();
    }
    if (lastFunctionIndex == 'c'){
        // idle_on();
    }
    if (lastFunctionIndex == 'p'){
        // idle_off();
    }
   
   
    break;

  case 'c':
    digitalWrite(DEFAULT_LED_PIN, HIGH);
    contantTouch();
    lastFunctionIndex = 'c';
    break;

  default:
    // idle();
    break;
  }
}