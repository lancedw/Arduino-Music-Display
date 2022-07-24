#include <FastLED.h>
#include <pixeltypes.h>
#include <fix_fft.h>

#define NUMLEDS 142           //number of leds connected in serial (veroorzaakt ruis als >142)
#define FULLARRAY 283         //daisy chained leds
#define DIGITALSENSPIN 8      //pin number of sound sensor module
#define LEDPIN 12             //pin number of led data pin
#define BTNPIN 3              //pin number of button, has to be 2 or 3 to enable interrupts
#define MIN 100               //sensor analog data in [1020 HIGH, 79 LOW] or [79 HIGH - 5 LOW],  afh van gevoeligheid
#define INTERVALMS 10         //sample size of var aantal
#define MAXAANTAL 400         //max sample size, used for normalising var aantal
#define MAXBRIGHTNESS 30      //maximum brightness, 8bit number (max 255)
#define IDLER 20              //*
#define IDLEG 20              //idle color values RGB
#define IDLEB 20              //*
#define A 143                 //**
#define B 144                 //*mirror points

#define SAMPLES 128           //base 2 number, max 128 for arduino nano
#define ANALOGSENSPIN 0       //needed for frequency detection
  
CRGB leds[FULLARRAY];           //led array die ledstrip voorstelt

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
  pinMode(BTNPIN, INPUT);
  FastLED.addLeds<WS2812,LEDPIN>(leds, FULLARRAY);
  FastLED.setBrightness(MAXBRIGHTNESS);
  analogReference(DEFAULT);
  //attachInterrupt(digitalPinToInterrupt(BTNPIN),ISRbtn,RISING); 
}

void loop() {
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
      if(volume > NUMLEDS){
        volume = NUMLEDS;       //cap volume if exceeds number of leds
      }

      mirrorVU((int)volume);    //function with vu meter implementation
      
      FastLED.show();
      aantal = 0;
      lastms = millis();        //operations after this should be minimal as they will interfere with the interval timing
    }
  } 
  else {
    fill_solid(leds, FULLARRAY, CRGB(0,0,0));
    FastLED.show();
  }
}

void ISRbtn(){
  brightness /= 2;                  //button press will cycle brightness and turn on:off 
  //Serial.println("interrupt");
  if(!aan){                         //if previous state was off, turn back on with full brightness
    aan = !aan;
    brightness = MAXBRIGHTNESS;
  }
  else if(brightness < 10) {        //if previous state was not off, check if we need to turn off
    aan = !aan;
  }
  FastLED.setBrightness(brightness);  
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
  fill_rainbow(leds,deltaLoper,gradient++,1);
  //idle color
  for(int i = NUMLEDS; i >= deltaLoper; i--){
    leds[i].setRGB(IDLEG,IDLER,IDLEB);       
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
    leds[i].setRGB(IDLEG,IDLER,IDLEB);      
  }
  for(int i = 0; i <= A-deltaLoper; i++){
    leds[i].setRGB(IDLEG,IDLER,IDLEB);      
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
