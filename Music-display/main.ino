#include <FastLED.h>
#include <pixeltypes.h>

#define NUMLEDS 142           //number of leds connected in serial (veroorzaakt ruis als >142)
#define LEDPIN 12             //pin number of led data pin
#define IDLER 20              //*
#define IDLEG 20              //idle color values RGB
#define IDLEB 20              //*

CRGB leds[FULLARRAY];

void setup() {  
  Serial.begin(9600);
  pinMode(BTNPIN, INPUT);
  FastLED.addLeds<WS2812,LEDPIN>(leds, FULLARRAY);
  FastLED.setBrightness(MAXBRIGHTNESS);
  analogReference(DEFAULT);
  //attachInterrupt(digitalPinToInterrupt(BTNPIN),ISRbtn,RISING); 
}

void loop() {
  fill_solid(leds, FULLARRAY, CRGB(IDLEG,IDLER,IDLEB));
  FastLED.show();
}
