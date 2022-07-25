#include <WS2812FX.h>
#include <FastLED.h>
#include <pixeltypes.h>

#define LED_COUNT 144
#define DIGITALSENSPIN 8      //pin number of sound sensor module
#define LEDPIN 12             //pin number of led data pin
#define MIN 100               //sensor analog data in [1020 HIGH, 79 LOW] or [79 HIGH - 5 LOW],  afh van gevoeligheid
#define INTERVALMS 10         //sample size of var aantal
#define MAXAANTAL 400         //max sample size, used for normalising var aantal
#define MAXBRIGHTNESS 255     //maximum brightness, 8bit number (max 255)
#define IDLER 20              //*
#define IDLEG 20              //idle color values RGB
#define IDLEB 20              //*

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LEDPIN, NEO_RGB + NEO_KHZ800);

CRGB leds[LED_COUNT];         //led array die ledstrip voorstelt

unsigned long lastms = 0;     //sample & interval global variables
unsigned long currentms;      //current time of executing loop
unsigned long interval;       //current-lastms; check if this is greater than defined var INTERVALMS
int aantal = 0;

bool aan = true;              //global on:off variable, used in interrupt
int brightness 
  = MAXBRIGHTNESS;            //global variable, used in interrupt

int loper = 0;                //running red led 
int deltaLoper = 0;           //running vu step delta
int gradient = 0;             //fill rainbow initial hue value, used for cycling hue range

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812,LEDPIN>(leds, LED_COUNT);
  FastLED.setBrightness(MAXBRIGHTNESS);
  analogReference(DEFAULT);
  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setSpeed(900);
  ws2812fx.setColor(0x007BFF);
  ws2812fx.setMode(FX_MODE_STATIC);
  ws2812fx.start();
}

bool vu = false;

void loop() {
  ws2812fx.service();
  if(Serial.available() > 0){
    int m = Serial.read();
    Serial.println(m);
    if(m == 57) {
      ws2812fx.stop();
      vu = true;
    } else {
      if(m == 58){
        ws2812fx.stop();
        vu = false;
      } else {
        ws2812fx.setMode(m);
        ws2812fx.start();
        vu = false;
      }
      
    }
  }
  if(vu){
    if(aan){
      double val = digitalRead(DIGITALSENSPIN);
      currentms = millis();
      interval = currentms - lastms;
      if(val == LOW){
        aantal++;
      }
      if(interval > INTERVALMS){
        Serial.println(aantal);
        double volume = ((double)aantal/MAXAANTAL)*142;
        if(volume > LED_COUNT){
          volume = LED_COUNT;       //cap volume if exceeds number of leds
        }
  
        normalVU((int)volume);    //function with vu meter implementation
        
        FastLED.show();
        aantal = 0;
        lastms = millis();        //operations after this should be minimal as they will interfere with the interval timing
      }
    } else {
      fill_solid(leds, LED_COUNT, CRGB(0,0,0));
      FastLED.show();
    }
  }
}

void normalVU(int volume){
  if(loper < volume) {
    loper = volume;
  } else {
    if(loper>0) {
      loper--;
    }
  }
  if(deltaLoper < volume){
      deltaLoper = volume;
  } else {
    if(deltaLoper-4>0){
      deltaLoper -= 4;
    } else {
      deltaLoper = 0;
    }
  }
  if(gradient == 255){
    gradient = 0;
  }
  //volume color
  fill_rainbow(leds, deltaLoper, gradient++, 1);
  //idle color
  for(int i = LED_COUNT; i >= deltaLoper; i--){
    leds[i].setRGB(IDLEG,IDLER,IDLEB);       
  }
  leds[loper].setRGB(0,255,0);
}
