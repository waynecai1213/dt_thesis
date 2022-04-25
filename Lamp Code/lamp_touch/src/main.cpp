#include <Arduino.h>
#include <FastLED.h>
#include <OneButton.h>

#define NUM_LEDS 15
#define DATA_PIN 15
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define BTN_PIN 4

#define twinkleInterval  100    //  闪烁间隔时间 (毫秒)
#define twinkleChance 80        //  闪烁数量，数值越大闪烁越多（0-255） 

uint8_t max_bright = 255;       // LED亮度控制变量，可使用数值为 0 ～ 255， 数值越大则光带亮度越高
uint8_t brightnessValue = 0;
bool isEnd = false;

uint8_t colorIndex[NUM_LEDS];

uint8_t functionIndex = 0;

CRGB leds[NUM_LEDS];            // 建立光带leds

DEFINE_GRADIENT_PALETTE(accentGradient_gp) {
  0, 255, 228, 45,
  127, 255, 247, 184,
  255, 255, 228, 45
};

//yellow orange
DEFINE_GRADIENT_PALETTE( bhw1_justducky_gp ) {
  0,  47, 28,  2,
  76, 229, 73,  1,
  163, 255, 255,  0,
  255, 229, 73,  1
};

//light blue + pink
DEFINE_GRADIENT_PALETTE( bhw1_hello_gp ) {
  0, 237, 156, 197,
  35, 244, 189, 230,
  56, 255, 255, 255,
  79, 244, 189, 230,
  109, 237, 156, 197,
  160, 121, 255, 255,
  196, 255, 255, 255,
  255, 121, 255, 255
};

DEFINE_GRADIENT_PALETTE( os250k_metres_gp ) {
    0, 255,255,255,
   11, 255,255,255,
   11, 255,252,214,
   34, 255,252,214,
   34, 255,248,178,
   57, 255,248,178,
   57, 255,211,130,
   81, 255,211,130,
   81, 255,176, 89,
  115, 255,176, 89,
  115, 255,147, 63,
  173, 255,147, 63,
  173, 255,127, 55,
  255, 255,127, 55};



CRGBPalette16 accentGradient =  bhw1_justducky_gp;

//OneButton btn = OneButton(BTN_PIN,true,true);



//touch 
#define TOUCH_PIN T0
int touchVal;
int preTouchVal;

int offset;
bool isOffset = false;

unsigned long patTime;
int patternCounter1 = 0;

//smoothing parameters
float smooth = 0.5;     //  0 < smooth < 1
int numRead = 20;



void setup() {


  LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  // 初始化光带

  FastLED.setBrightness(max_bright);                            // 设置光带亮度
  FastLED.setCorrection(TypicalPixelString);

  for (int i = 0; i < NUM_LEDS; i++) {
    colorIndex[i] = random8();
  }

  Serial.begin(115200);

  //button initiate
//  btn.attachClick(switchFunction_btn);
//  pinMode(BTN_PIN, INPUT_PULLUP); 
  
}

void loop () {

  switch (functionIndex) {
    case 0:
     gentle_2();
      break;
    case 1:
      pat_1();
      break;
    case 2:
      tickle();
      break;
  }

 switchFunction_touch();

//OneButton.h requirement
//  btn.tick();

}


void switchFunction_touch(){
  //smoothing method 2
  int senseSum = 0;
  for (int k = 0; k < numRead; k++) {
    senseSum += touchRead(TOUCH_PIN);
  }
  Serial.print("-touchRead: ");
  touchVal=senseSum / numRead;
//  touchVal = map(senseSum / numRead, 0, 40, 0, 20);
  Serial.println(touchVal);  // get value using T0
  //  delay(10);

  
  // pat pattern
  if (touchVal <= 15) {
    patTime = millis();
    preTouchVal = touchVal;
  }

  if ((millis() - patTime) > 100) {
    if ((touchVal - preTouchVal) > 6) {
      patternCounter1++;
      Serial.print("---------patternCounter1: ");
      Serial.println(patternCounter1);
    }
  }

  if ((millis() - patTime)>10000) {
    patternCounter1=0;
    }
    
  if (patternCounter1>=10){
   functionIndex=1;
  }else{
  functionIndex=0;
    }

 
 }



void switchFunction_btn() {

  Serial.println("----- Button Click -----");
//  EVERY_N_SECONDS(5) {
//    functionIndex = (functionIndex + 1) % 3;
//  }
   functionIndex = (functionIndex + 1) % 3;
}

void hug() {

  for ( int i = 0; i < NUM_LEDS - 1; i++) {
    leds[i] = CRGB::FairyLight; //  FairyLight =0xFFE42D, CRGB color name: http://fastled.io/docs/3.1/struct_c_r_g_b.html
    FastLED.show();
    delay(100);
  }

  for ( int i = NUM_LEDS - 1; i >= 0; i--) {
    fadeToBlackBy( leds, i, 50);
    //    leds[i] = CRGB::Black;
    FastLED.show();
    delay(100);
  }

}

void pat_1() {
Serial.println("----pat-----");
  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(37, 184, brightnessValue);

  }

  EVERY_N_MILLISECONDS(15) {
    if ( brightnessValue < max_bright && (!isEnd )) {
      brightnessValue++;
    } else {
      brightnessValue--;
    }

    if (brightnessValue == 0) {
      isEnd = false;
    }
    if (brightnessValue == max_bright ) {
      isEnd = true;
    }
  }
  FastLED.show();
}

void pat_2() {

  fill_solid(leds, NUM_LEDS, CRGB::FairyLight);

  EVERY_N_MILLISECONDS(50) {
    FastLED.setBrightness(brightnessValue);
    if ( brightnessValue < max_bright && (!isEnd )) {
      brightnessValue++;
    } else {
      brightnessValue--;
    }

    if (brightnessValue == 0) {
      isEnd = false;
    }
    if (brightnessValue == max_bright ) {
      isEnd = true;
    }

  }

  FastLED.show();
}


void tickle() {
  EVERY_N_MILLISECONDS(150) {
    leds[random8(0, NUM_LEDS - 1)] = CRGB::FairyLight;
  }
  fadeToBlackBy(leds, NUM_LEDS, 1);
  FastLED.show();

}

void gentle() {

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(accentGradient, colorIndex[i]);
  }

  EVERY_N_MILLISECONDS(5) {
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex[i]++;
    }
  }
  FastLED.show();

}

void gentle_2(){
  Serial.println("----gentle-----");
  for (int i=0;i<NUM_LEDS;i++){
    uint8_t brightness =inoise8(i*max_bright,millis()/5);
   uint8_t index=inoise8(i*100,millis()/10);
    leds[i]=ColorFromPalette(accentGradient,index,brightness);
    }
     FastLED.show();
     
  }


void test_1() {

  //segment back n forth
  uint8_t sinBeat = beatsin8(30, 0, NUM_LEDS - 1, 0, 0);
  leds[sinBeat] = CRGB::FairyLight;
  fadeToBlackBy(leds, NUM_LEDS, 10);

  EVERY_N_MILLISECONDS(10) {
    Serial.println(sinBeat);
  }
  FastLED.show();

}


void test_2() {
  //segment run in one direction
  uint8_t pos = map(beat8(40, 0), 0, 255, 0, NUM_LEDS - 1);
  leds[pos] = CRGB::FairyLight;
  fadeToBlackBy(leds, NUM_LEDS, 5);

  EVERY_N_MILLISECONDS(10) {
    Serial.println(pos);
  }
  FastLED.show();

}