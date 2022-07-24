#include <FastLED.h>
#include <pixeltypes.h>
#include "lighting_fx.h"

#define NUMLEDS 284           //number of leds connected in serial
#define LEDPIN 12             //pin number of led data pin
#define BRIGHTNESS 255        //8bit number (max 255)
#define IDLER 20              //*
#define IDLEG 20              //idle color values RGB
#define IDLEB 20              //*

CRGB leds[NUMLEDS];
int incomingByte;

void setup() {  
  Serial.begin(9600);
  FastLED.addLeds<WS2812,LEDPIN>(leds, NUMLEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
//  if(Serial.available() > 0){
//    incomingByte = Serial.parseInt();
//    fill_solid(leds, NUMLEDS, CRGB(incomingByte,30,60));
//    Serial.println(incomingByte);
//  }
//  FastLED.show();
  breathe(200, 100, 50, leds, NUMLEDS);
}
