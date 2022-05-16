#include <Arduino.h>
#include <FastLED.h>

char receivedCommand;

// Confif LED
#define NUM_LEDS 15
#define DATA_PIN 15
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

uint8_t max_bright = 200;
uint8_t brightnessValue = 0;
bool isEnd = false;

uint8_t colorIndex[NUM_LEDS];

char functionIndex = 'i';

uint8_t patCounter = 0;
int breathSpeed = 30;
unsigned long preTime;
uint8_t downCounter = 0;

CRGB leds[NUM_LEDS];


void idle(){
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


void breath(){
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
        breathSpeed = 20;
        isEnd = !isEnd;
        patCounter++;
        delay(random(100,200));
      }
    }
  }

  // pat
if (patCounter == 6)
  {
    functionIndex = 'i';
  }
  fill_solid(leds, NUM_LEDS, CRGB::White);
  int eased_brightnessValue = ease8InOutCubic(brightnessValue);
  // int eased_brightnessValue = map(ease8InOutCubic(brightnessValue), 0, ease8InOutCubic(max_bright), 0, max_bright);
  FastLED.setBrightness(eased_brightnessValue);
  FastLED.show();
}

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);

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

  if (Serial.available() > 0)
  {
    functionIndex = Serial.read(); // gets one byte from serial buffer

  }

  switch (functionIndex)
  {
  case 't':
    digitalWrite(13, HIGH);
    tickle();

    break;

  case 'f':
    digitalWrite(13, LOW);
    break;
  
    case 'p':
    digitalWrite(13, LOW);
     breath();

    break;

  default:
    // idle();
    break;
  }
}