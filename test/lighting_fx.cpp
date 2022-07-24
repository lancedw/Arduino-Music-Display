#include "lighting_fx.h"

int hue = 0;
int divisor = 30;

void breathe(int r, int g, int b, CRGB leds[], int numleds){
  while(true){
    float breath = (exp(sin(millis()/5000.0*PI)) - 0.36787944)*108.0;
    breath = map(breath, 0, 255, 50, 255);
    FastLED.setBrightness(breath);
    fill_solid(leds, numleds, CRGB(r, g, b));
    if(hue == (255 * divisor)) {
      hue = 0;
    }
    FastLED.show();
    delay(2);
  }
}
