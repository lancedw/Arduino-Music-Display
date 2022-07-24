import controlP5.*;
import processing.serial.*;
import java.util.Random;

Serial port;
ControlP5 cp;
PFont font;
String text = "Static;Blink;Breath;Color Wipe;Color Wipe Inverse;Color Wipe Reverse;Color Wipe Reverse Inverse;Color Wipe Random;Random Color;Single Dynamic;Multi Dynamic;Rainbow;Rainbow Cycle;Scan;Dual Scan;Fade;Theater Chase;Theater Chase Rainbow;Running Lights;Twinkle;Twinkle Random;Twinkle Fade;Twinkle Fade Random;Sparkle;Flash Sparkle;Hyper Sparkle;Strobe;Strobe Rainbow;Multi Strobe;Blink Rainbow;Chase White;Chase Color;Chase Random;Chase Rainbow;Chase Flash;Chase Flash Random;Chase Rainbow White;Chase Blackout;Chase Blackout Rainbow;Color Sweep Random;Running Color;Running Red Blue;Running Random;Scanner;Comet;Fireworks;Fireworks Random;Christmas;Fire Flicker;Fire Flicker (soft);Fire Flicker (intense);Circus Combustus;Halloween;Bicolor Chase;Tricolor Chase;TwinkleFOX";
String[] fx = text.split(";");

void setup() {
  size(1200, 900);    //(width, height)
  port = new Serial(this, "COM5", 9600); 
  cp = new ControlP5(this);
  font = createFont("calibri light", 18);
  
  int nr = 0;
  int w = 170;     //width of button
  int h = 60;     //height of button

  //for(int r = 0; r<11; r++){
  //  for(int c = 0; c<5; c++){
  //    cp.addButton("button"+nr)    //name of button
  //      .setLabel(fx[nr])
  //      .setPosition(50+c*(w+15), 20+r*(h+15))    //(x,y) of upper left corner
  //      .setSize(w, h)       //(width, height)
  //      .setFont(font)
  //      ;
  //      nr++;
  //  }
  //}
}

void draw(){
  background(150, 0, 150);   //(R, G, B)
}

void button0(){port.write(0);}
void button1(){port.write(1);}
void button2(){port.write(2);}
void button3(){port.write(3);}
void button4(){port.write(4);}
void button5(){port.write(5);}
void button6(){port.write(6);}
void button7(){port.write(7);}
void button8(){port.write(8);}
void button9(){port.write(9);}
void button10(){port.write(10);}
void button11(){port.write(11);}
void button12(){port.write(12);}
void button13(){port.write(13);}
void button14(){port.write(14);}
void button15(){port.write(15);}
void button16(){port.write(16);}
void button17(){port.write(17);}
void button18(){port.write(18);}
void button19(){port.write(19);}
void button20(){port.write(20);}
void button21(){port.write(21);}
void button22(){port.write(22);}
void button23(){port.write(23);}
void button24(){port.write(24);}
void button25(){port.write(25);}
void button26(){port.write(26);}
void button27(){port.write(27);}
void button28(){port.write(28);}
void button29(){port.write(29);}
void button30(){port.write(30);}
void button31(){port.write(31);}
void button32(){port.write(32);}
void button33(){port.write(33);}
void button34(){port.write(34);}
void button35(){port.write(35);}
void button36(){port.write(36);}
void button37(){port.write(37);}
void button38(){port.write(38);}
void button39(){port.write(39);}
void button40(){port.write(40);}
void button41(){port.write(41);}
void button42(){port.write(42);}
void button43(){port.write(43);}
void button44(){port.write(44);}
void button45(){port.write(45);}
void button46(){port.write(46);}
void button47(){port.write(47);}
void button48(){port.write(48);}
void button49(){port.write(49);}
void button50(){port.write(50);}
void button51(){port.write(51);}
void button52(){port.write(52);}
void button53(){port.write(53);}
void button54(){port.write(54);}
void button55(){port.write(55);}
