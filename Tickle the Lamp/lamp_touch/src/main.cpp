#include <Arduino.h>
#include <FastLED.h>
#include <OneButton.h>

#define NUM_LEDS 15
#define DATA_PIN 15
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define BTN_PIN 4

#define twinkleInterval 100 //  闪烁间隔时间 (毫秒)
#define twinkleChance 80    //  闪烁数量，数值越大闪烁越多（0-255）

uint8_t max_bright = 200; // LED亮度控制变量，可使用数值为 0 ～ 255， 数值越大则光带亮度越高
uint8_t brightnessValue = 0;
bool isEnd = false;

uint8_t colorIndex[NUM_LEDS];

uint8_t functionIndex = 0;

CRGB leds[NUM_LEDS]; // 建立光带leds

DEFINE_GRADIENT_PALETTE(accentGradient_gp){
    0, 255, 228, 45,
    127, 255, 247, 184,
    255, 255, 228, 45};

// yellow orange --- Obsolete
DEFINE_GRADIENT_PALETTE(bhw1_justducky_gp){
    0, 47, 28, 2,
    76, 229, 73, 1,
    163, 255, 255, 0,
    255, 229, 73, 1};

// light blue + pink
DEFINE_GRADIENT_PALETTE(bhw1_hello_gp){
    0, 237, 156, 197,
    35, 244, 189, 230,
    56, 255, 255, 255,
    79, 244, 189, 230,
    109, 237, 156, 197,
    160, 121, 255, 255,
    196, 255, 255, 255,
    255, 121, 255, 255};


CRGBPalette16 accentGradient = bhw1_hello_gp;

OneButton btn = OneButton(BTN_PIN,true,true);

// touch
#define TOUCH_PIN T0
int touchVal;
int preTouchVal;

int offset;
bool isOffset = false;

unsigned long patTime;
int patternCounter1 = 0;

// smoothing parameters
float smooth = 0.5; //  0 < smooth < 1
int numRead = 20;
int blinkCounter=0;

//millis() -> pat time 
void switchFunction_touch()
{
  // smoothing method 2
  int senseSum = 0;
  for (int k = 0; k < numRead; k++)
  {
    senseSum += touchRead(TOUCH_PIN);
  }
  Serial.print("-touchRead: ");
  touchVal = senseSum / numRead;
  //  touchVal = map(senseSum / numRead, 0, 40, 0, 20);
  Serial.println(touchVal); // get value using T0
  //  delay(10);

  // pat pattern
  if (touchVal <= 15)
  {
    patTime = millis();
    preTouchVal = touchVal;
  }

  if ((millis() - patTime) > 100)
  {
    if ((touchVal - preTouchVal) > 6)
    {
      patternCounter1++;
      Serial.print("---------patternCounter1: ");
      Serial.println(patternCounter1);
    }
  }

  if ((millis() - patTime) > 10000)
  {
    patternCounter1 = 0;
  }

  if (patternCounter1 >= 10)
  {
    functionIndex = 1;
  }
  else
  {
    functionIndex = 0;
  }
}


void switchFunction_btn()
{

  Serial.println("----- Button Click -----");
  //  EVERY_N_SECONDS(5) {
  //    functionIndex = (functionIndex + 1) % 3;
  //  }
  functionIndex = (functionIndex + 1) % 3;
}


void hug()
{
  for (int i = 0; i < NUM_LEDS - 1; i++)
  {
    leds[i] = CRGB::FairyLight; //  FairyLight =0xFFE42D, CRGB color name: http://fastled.io/docs/3.1/struct_c_r_g_b.html
    FastLED.show();
    delay(100);
  }

  for (int i = NUM_LEDS - 1; i >= 0; i--)
  {
    fadeToBlackBy(leds, i, 50);
    //    leds[i] = CRGB::Black;
    FastLED.show();
    delay(100);
  }
}


//breath in & out 
void pat_1()
{

  Serial.println("----pat-----");
 
  FastLED.setBrightness(brightnessValue);
  
    int breathSpeed=20;
  //time affect breathing speed
  EVERY_N_MILLISECONDS(breathSpeed)
  {
    if (brightnessValue < max_bright && !isEnd)
    {
      brightnessValue++;
    }
    else
    {
      brightnessValue--;
    }

    if (brightnessValue == 0 || brightnessValue == max_bright)
    {
      isEnd = !isEnd;
    }
   
  }
  FastLED.show();
}


void pat_2()
{

  fill_solid(leds, NUM_LEDS, CRGB::FairyLight);

  EVERY_N_MILLISECONDS(50)
  {
    FastLED.setBrightness(brightnessValue);
    if (brightnessValue < max_bright && (!isEnd))
    {
      brightnessValue++;
    }
    else
    {
      brightnessValue--;
    }

    if (brightnessValue == 0)
    {
      isEnd = false;
    }
    if (brightnessValue == max_bright)
    {
      isEnd = true;
    }
  }

  FastLED.show();
}


void gentle()
{

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = ColorFromPalette(accentGradient, colorIndex[i]);
  }

  EVERY_N_MILLISECONDS(5)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      colorIndex[i]++;
    }
  }
  FastLED.show();
}


void gentle_2()
{
  Serial.println("----gentle-----");
  for (int i = 0; i < NUM_LEDS; i++)
  {
    uint8_t brightness = inoise8(i * max_bright, millis() / 5);
    uint8_t index = inoise8(i * 100, millis() / 10);
    leds[i] = ColorFromPalette(accentGradient, index, brightness);
  }
  FastLED.show();
}


void test_1()
{

  // segment back n forth
  uint8_t sinBeat = beatsin8(30, 0, NUM_LEDS - 1, 0, 0);
  leds[sinBeat] = CRGB::FairyLight;
  fadeToBlackBy(leds, NUM_LEDS, 10);

  EVERY_N_MILLISECONDS(10)
  {
    Serial.println(sinBeat);
  }
  FastLED.show();
}


void test_2()
{
  // segment run in one direction
  uint8_t pos = map(beat8(40, 0), 0, 255, 0, NUM_LEDS - 1);
  leds[pos] = CRGB::FairyLight;
  fadeToBlackBy(leds, NUM_LEDS, 5);

  EVERY_N_MILLISECONDS(10)
  {
    Serial.println(pos);
  }
  FastLED.show();
}


void firstBlink(){

 if(blinkCounter==0){
    
    
  FastLED.setBrightness(max_bright/2);
    fill_solid( leds,NUM_LEDS , CRGB::White);
    // FastLED.setBrightness(brightnessValue);
    FastLED.show();
    delay(600);
    blinkCounter++;
  }

if (blinkCounter<3 && blinkCounter>0){
  FastLED.setBrightness(max_bright);
    fill_solid( leds,NUM_LEDS , CRGB::White);
    FastLED.show();
    delay(200);
    // Now turn the LED off, then pause
    fill_solid( leds,NUM_LEDS , CRGB::Black);
    FastLED.show();
    delay(300);
    blinkCounter++;
  }else{
    fill_solid( leds,NUM_LEDS , CRGB::Black);
    FastLED.show();
    delay(3000);
    blinkCounter=0;
    functionIndex=1;
  }

}

void knockBlink(){
  if (blinkCounter<2){
      FastLED.setBrightness(max_bright/2);
      fill_solid( leds,NUM_LEDS , CRGB::White);
      FastLED.show();
      delay(200);
      // Now turn the LED off, then pause
      fill_solid( leds,NUM_LEDS , CRGB::Black);
      FastLED.show();
      delay(400);
      blinkCounter++;
    }else{
      fill_solid( leds,NUM_LEDS , CRGB::Black);
      FastLED.show();
      delay(3000);
      functionIndex=2;
    }
}

uint8_t upCounter = 0;
void gradualUp()
{
  EVERY_N_MILLISECONDS(15)
  {
    if (brightnessValue < max_bright / 3 && upCounter == 0)
    {
      brightnessValue++;
      // Serial.print("brightnessValue:  ");
      // Serial.print(brightnessValue);
      // Serial.print("--- eased brightnessValue:  ");
      // Serial.println(map(ease8InOutCubic(brightnessValue),0,ease8InOutCubic(max_bright),0,max_bright));
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
        functionIndex = 3;
      }
    }
  }
  fill_solid(leds, NUM_LEDS, CRGB::White);
  // ease in out funtion: https://github.com/FastLED/FastLED/wiki/High-performance-math#easing-and-linear-interpolation-functions
  int eased_brightnessValue = map(ease8InOutCubic(brightnessValue), 0, ease8InOutCubic(max_bright), 0, max_bright);
  FastLED.setBrightness(eased_brightnessValue);
  FastLED.show();
}

uint8_t downCounter = 0;
unsigned long  preTime;
void gradualDown()
{
  EVERY_N_MILLISECONDS(20)
  {
    if (brightnessValue >= max_bright / 4 && downCounter == 0)
    {
      brightnessValue--;
    }
    else if (downCounter == 0)
    {
      downCounter = 1;
      delay(200);
    }

    if (downCounter == 1 && brightnessValue < max_bright / 2)
    {
      brightnessValue++;
    }
    else if (downCounter == 1)
    {
      downCounter = 2;
      Serial.println("Start to fade");
      delay(500);
    }
  }
  
  if (downCounter != 2)
  {
    fill_solid(leds, NUM_LEDS, CRGB::White);
    // ease in out funtion: https://github.com/FastLED/FastLED/wiki/High-performance-math#easing-and-linear-interpolation-functions
    int eased_brightnessValue = map(ease8InOutCubic(brightnessValue), 0, ease8InOutCubic(max_bright), 0, max_bright);
    FastLED.setBrightness(eased_brightnessValue);
    FastLED.show();
    preTime= millis();
  }
  else
  {
    // fade to sleep
    fadeToBlackBy(leds, NUM_LEDS, 50);
    //    leds[i] = CRGB::Black;
    delay(80);
    FastLED.show();
    //to next state
    int waitTime=8000;
    if((millis() - preTime)>waitTime){
        functionIndex=4;
       
        //reset parameters before past to next state
        preTime = millis();
        downCounter=0;

      }
  }
}

void tickle()
{
  EVERY_N_MILLISECONDS(150)
  {
    leds[random8(0, NUM_LEDS - 1)] = CRGB::White;
  }
  fadeToBlackBy(leds, NUM_LEDS, 1);
  FastLED.show();

  if((millis()-preTime)>10000){
   functionIndex=5;
   preTime=millis();
  }

}

void gradualUp_2(){

  for (uint8_t i = NUM_LEDS / 2; i < NUM_LEDS; i++) {
    leds[i]= CRGB::White;
    leds[NUM_LEDS-i]= CRGB::White;
    // fadeToBlackBy(leds, NUM_LEDS, 10);
    FastLED.show();
    delay(100);
  }
  
  // functionIndex =6;
 
  if((millis()-preTime)>10000){

   functionIndex=6;
   brightnessValue= max_bright/2;
   isEnd=false;
  }

}


uint8_t patCounter=0;
void patToSleep(){
    int breathSpeed=30;
    //time affect breathing speed
    EVERY_N_MILLISECONDS(breathSpeed)
    {
      if(patCounter<=5){
          if (brightnessValue < max_bright/2 && !isEnd)
          {
            brightnessValue++;
          }
          else
          {
            brightnessValue--;
          }
        if (brightnessValue == 20 || brightnessValue == max_bright/2)
        {
          isEnd = !isEnd;
          patCounter++;
          delay(200);
        }
       }
    }

    if (patCounter==6){
        functionIndex=7;
    }


    int eased_brightnessValue = ease8InOutCubic(brightnessValue);
    // int eased_brightnessValue = map(ease8InOutCubic(brightnessValue), 0, ease8InOutCubic(max_bright), 0, max_bright);
    FastLED.setBrightness(eased_brightnessValue);
  
    FastLED.show();

}


void gradualDown_2()
{
  EVERY_N_MILLISECONDS(10)
  {
    if (brightnessValue >= max_bright / 4 && downCounter == 0)
    {
      brightnessValue--;
    }
    else if (downCounter == 0)
    {
      downCounter = 1;
      delay(200);
    }

    if (downCounter == 1 && brightnessValue < max_bright / 2)
    {
      brightnessValue++;
    }
    else if (downCounter == 1)
    {
      downCounter = 2;
      Serial.println("Start to fade");
      delay(500);
    }
  }
  
  if (downCounter != 2)
  {
    fill_solid(leds, NUM_LEDS, CRGB::White);
    // ease in out funtion: https://github.com/FastLED/FastLED/wiki/High-performance-math#easing-and-linear-interpolation-functions
    int eased_brightnessValue = map(ease8InOutCubic(brightnessValue), 0, ease8InOutCubic(max_bright), 0, max_bright);
    FastLED.setBrightness(eased_brightnessValue);
    FastLED.show();
    preTime= millis();
  }
  else
  {
    // fade to sleep
    fadeToBlackBy(leds, NUM_LEDS, 50);
    //    leds[i] = CRGB::Black;
    delay(80);
    FastLED.show();
    //to next state
    int waitTime=8000;
    if((millis() - preTime)>waitTime){
        // functionIndex=4;
       
        //reset parameters before past to next state
        // preTime = millis();
        // downCounter=0;

      }
  }
}

void setup()
{
  LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS); // 初始化光带
  FastLED.setBrightness(max_bright); // 设置光带亮度
  FastLED.setCorrection(TypicalPixelString);
  //https://fastled.io/docs/3.1/group___color_enums.html // Candle:1900K
  // https://www.lumens.com/the-edit/the-guides/understanding-kelvin-color-temperature/
  // FastLED.setTemperature(Candle);

  // for (int i = 0; i < NUM_LEDS; i++)
  // {
  //   colorIndex[i] = random8();
  // }

  Serial.begin(115200);

  // button initiate
   btn.attachClick(switchFunction_btn);
  //  pinMode(BTN_PIN, INPUT_PULLUP);
}

void loop()
{
  switch (functionIndex)
  {
  case 0:
    firstBlink();
    break;
  case 1:
    knockBlink();
    // patToSleep();
    // gentle_2();
    break;
  case 2:
    gradualUp();
    // pat_1();
    break;
  case 3:
    gradualDown();
    // tickle();
    break;
  case 4:
    tickle();
    break;
  case 5:
    gradualUp_2();
    break;
  case 6:
    patToSleep();
    // gradualDown();
    break;
  case 7:
     gradualDown_2();
    break;
  }

  // OneButton.h requirement
  btn.tick();
}
