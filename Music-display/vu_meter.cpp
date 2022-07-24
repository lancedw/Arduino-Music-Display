#include "vu_meter.h"

#define NUMLEDS 142           //number of leds connected in serial (veroorzaakt ruis als >142)
#define IDLER 20              //*
#define IDLEG 20              //idle color values RGB
#define IDLEB 20              //*

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
    if(deltaLoper-5>0){
      deltaLoper -= 5;
    } else {
      deltaLoper = 0;
    }
  }
  if(gradient == 255){
    gradient = 0;
  }
  //volume color
  fill_rainbow(leds, deltaLoper, gradient++,1);
  //idle color
  for(int i = NUMLEDS; i >= deltaLoper; i--){
    leds[i].setRGB(IDLEG, IDLER, IDLEB);       
  }
  leds[loper].setRGB(0,255,0);
}

void mirrorVU(int volume){
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
    if(deltaLoper-5>0){
      deltaLoper -= 5;
    } else {
      deltaLoper = 0;
    }
  }
  if(gradient == 255){
    gradient = 0;
  }
  //volume color
  my_fill_rainbow(leds, B, B+deltaLoper, gradient++, 1);
  reverse_fill_rainbow(leds, A, A-deltaLoper, gradient++, 1);
  // Serial.println("rainbow");
  //idle color
  for(int i = FULLARRAY-1; i >= B+deltaLoper; i--){
    leds[i].setRGB(IDLEG, IDLER, IDLEB);      
  }
  for(int i = 0; i <= A-deltaLoper; i++){
    leds[i].setRGB(IDLEG, IDLER, IDLEB);      
  }
  leds[B+loper].setRGB(0,255,0);
  leds[A-loper].setRGB(0,255,0);
}

void my_fill_rainbow( struct CRGB * pFirstLED, 
                  int start,
                  int numToFill,
                  uint8_t initialhue,
                  uint8_t deltahue )
{
    CHSV hsv;
    hsv.hue = initialhue;
    hsv.val = 255;
    hsv.sat = 240;
    for( int i = start; i < numToFill; i++) {
        pFirstLED[i] = hsv;
        hsv.hue += deltahue;
    }
}
void reverse_fill_rainbow( struct CRGB * pFirstLED, 
                  int end,
                  int begin,
                  uint8_t initialhue,
                  uint8_t deltahue )
{
    CHSV hsv;
    hsv.hue = initialhue;
    hsv.val = 255;
    hsv.sat = 240;
    for( int i = end; i > begin; i--) {
        pFirstLED[i] = hsv;
        hsv.hue += deltahue;
    }
}
