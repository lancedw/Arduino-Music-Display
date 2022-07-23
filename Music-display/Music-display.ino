#include <FastLED.h>
#include <pixeltypes.h>
#include <fix_fft.h>

#define NUMLEDS 142           //number of leds connected in serial
#define DIGITALSENSPIN 2      //pin number of sound sensor module
#define LEDPIN 6              //pin number of led data pin
#define BTNPIN 8              //PIN moet D2 of D3 zijn om met int te werken
#define MIN 100               //sensor analog data in [1020 HIGH, 79 LOW] or [79 HIGH - 5 LOW],  afh van gevoeligheid
#define INTERVALMS 10         //sample size of var aantal
#define MAXAANTAL 400         //max sample size, used for normalising var aantal
#define MAXBRIGHTNESS 255     //maximum brightness, 8bit number
#define IDLER 20              //*
#define IDLEG 20              //idle color values RGB
#define IDLEB 20              //*
#define SAMPLES 128           //base 2 number, max 128 for arduino nano
#define ANALOGSENSPIN 0       //needed for frequency detection
  
CRGB leds[NUMLEDS];           //led array die ledstrip voorstelt

unsigned long lastms = 0;     //sample & interval global variables
unsigned long currentms;      //current time of executing loop
unsigned long interval;       //current-lastms; check if this is greater than defined var INTERVALMS
int aantal = 0;

bool aan = true;              //global on:off variable, used in interrupt
int brightness 
  = MAXBRIGHTNESS;            //global variables, used in interrupt

int loper = 0;                //running red led 

void setup() {  
  Serial.begin(9600);
  pinMode(BTNPIN, INPUT);
  FastLED.addLeds<WS2812,LEDPIN, GRB>(leds, NUMLEDS);
  FastLED.setBrightness(MAXBRIGHTNESS);
  analogReference(DEFAULT);
  attachInterrupt(digitalPinToInterrupt(BTNPIN),ISRbtn,RISING); 
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
      //Serial.println(aantal);
      double volume = ((double)aantal/MAXAANTAL)*142;
      if(volume > NUMLEDS){
        volume = NUMLEDS;       //cap volume if exceeds number of leds
      }

      normalVU((int)volume);    //function with vu meter implementation
      
      FastLED.show();
      aantal = 0;
      lastms = millis();        //operations after this should be minimal as they will interfere with the interval timing
    }
  } 
}

void ISRbtn(){
  brightness -= 52;               //button press will cycle brightness and turn on:off 
  
  if(!aan){                       //if previous state was off, turn back on with full brightness
    aan = !aan;
    brightness = MAXBRIGHTNESS;
  }
  else if(brightness < 1) {       //if previous state was not off, check if we need to turn off
    aan = !aan;
  }
  FastLED.setBrightness(brightness);  
  Serial.println("interrupt routine called");
}

void normalVU(int volume){
  //volume color
  fill_rainbow(leds,volume-1,0,255/(NUMLEDS-10));

  //idle color
  for(int i = NUMLEDS;i >= volume; i--){
    leds[i].setRGB(IDLEG,IDLER,IDLEB);       
  }
  
  if(loper<volume) {
    loper = (int)volume;
  } 
  else if(loper>0) {
     loper--;
  }
  leds[loper].setRGB(0,255,0);
}

char im[SAMPLES], data[SAMPLES];
int i = 0;
int val;
void frequencyVU() {
  int min = 1024;
  int max = 0;
  for(i=0;i<SAMPLES;i++){
    val = analogRead(ANALOGSENSPIN); 
    data[i] = val/4-128;
    im[i] = 0;
    if(val>max) max = val;
    if(val<min) min = val;
  }

  fix_fft(data,im,7,0);

  
}

void inefficient_rainbow(int volume){  
  int delta = NUMLEDS /7;          //7 colors thus need for 7 intervals 
  for(int i = 0; i<volume; i++){
    if(i<delta)                   leds[i] = CRGB::Blue;
    if(1*delta<=i && i<2*delta)   leds[i] = CRGB::Fuchsia;
    if(2*delta<=i && i<3*delta)   leds[i] = CRGB::Blue;
    if(3*delta<=i && i<4*delta)   leds[i] = CRGB::Green;
    if(4*delta<=i && i<5*delta)   leds[i] = CRGB::Yellow;
    if(5*delta<=i && i<6*delta)   leds[i] = CRGB::Orange;
    if(6*delta<=i && i<=NUMLEDS)  leds[i] = CRGB::Red;
  }
}
