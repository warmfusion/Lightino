//***************************************************************
//Lightino is an open source project develop by MakerStorage LLC.
//It is a STEM & EdTech. fidget spinner for students to learn code.
//Please contrubute and suport this project at lightino.org
// e-mail:ne@makerstorage.com
//***************************************************************
//delay functions and graphics taken from Ken (MakerBox)
//***************************************************************
////Printing text functions from
//https://github.com/reger-men/Arduion-POV-clock/blob/master/clock.ino
//



#include "font.h"
#include <avr/pgmspace.h>

#define BLUE  A1
#define RED   A0
#define GREEN A2
#define LED1 9
#define LED2 8
#define LED3 7
#define LED4 6
#define LED5 5
#define LED6 4
#define LED7 3
#define LED8 2
#define SENSOR A10

uint8_t led_anodes[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
uint8_t led_cathodes[] = {GREEN, RED, BLUE};
int color = 0; //color index 0 to 2
boolean flag=true;

unsigned long long lastTimeUs;                // time (us) magnet sensed
unsigned long long revTimeUs;                 // time (us) of last full rotation
unsigned long long dwellTimeUs;               // time (us) between LED changes (based on rotation speed)

int rows= 8;            // Total LED's in a row
const int charHeight = 8;
const int charWidth = 5;
int i;

char textString_Up[] = " Hello";
char textString_Down[] = "World!";

void setup() {

   // Interupt setting
   PCMSK0 = bit (PCINT6); //Use PCINT6 = PB6 pin 30.
   PCICR |= (1<<PCIE0);   //Enable Pin change interrupt
   sei();


 // Serial.begin(9600);
 //  while (!Serial) ;
  
  TXLED0;// on board leds off
  RXLED0;
  
  pinMode(RED, OUTPUT); 
  pinMode(BLUE, OUTPUT); 
  pinMode(GREEN, OUTPUT); 
  
  pinMode(LED8, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED1, OUTPUT);


  
  pinMode(SENSOR, INPUT);
  digitalWrite(SENSOR,HIGH); 

   // default off
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);;
  digitalWrite(GREEN, LOW); 
  
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  digitalWrite(LED1, LOW);

  lastTimeUs = micros();
}

void loop() {
  unsigned long long curTimeUs;

  

if (flag){  
flag=false;

  curTimeUs = micros();
  revTimeUs =  curTimeUs - lastTimeUs;
  lastTimeUs = curTimeUs;
  dwellTimeUs = (revTimeUs * 3ul / 360ul);  
  setColor (0);  


      for (int k=0; k<sizeof(textString_Up)-1; k++){
        printLetter(textString_Up[k]);
      }


      if(1 && (revTimeUs < 100000)){
 // wait for it . . .
        while((micros() < (lastTimeUs + revTimeUs / 2)) && !flag){};
        
        for (int k=sizeof(textString_Down)-1; k>-1; k--){
          printLetterLower(textString_Down[k]);
        }  

      }


  //   dwellTimeUs = (revTimeUs * 3ul / 360ul);  //making 4ul not works
  //   dwellDelay();
   //    delayMicroseconds(dwellTimeUs);



} else {
    //AllLedsOff();
}
 


}//loop

void AllLedsOff(){

   for(int LED=0; LED<8; LED++){
       digitalWrite(led_anodes[LED], 0); 
       setColor (-1);       
     }  

}


void setColor (int color){

switch (color) {
    case 0:    //red
      digitalWrite(led_cathodes[0], LOW);
      digitalWrite(led_cathodes[1], LOW);
      digitalWrite(led_cathodes[2], HIGH);
      break;
      
    case 1:    //green
      digitalWrite(led_cathodes[0], LOW);
      digitalWrite(led_cathodes[1], HIGH);
      digitalWrite(led_cathodes[2], LOW);
      break;
      
    case 2:    //blue
      digitalWrite(led_cathodes[0], HIGH);
      digitalWrite(led_cathodes[1], LOW);
      digitalWrite(led_cathodes[2], LOW);
      break;

     default:
        // turn all the LEDs off:  
      digitalWrite(led_cathodes[0], LOW);
      digitalWrite(led_cathodes[1], LOW);
      digitalWrite(led_cathodes[2], LOW);
     
  }

  
}

void dwellDelay(){ // avoid glitch on first rotation having erronious value 
  if (dwellTimeUs > 2000){
    dwellTimeUs = 2000;
  }
  if (dwellTimeUs < 100){
    dwellTimeUs = 100;
  }  
  delayMicroseconds(dwellTimeUs);
}



void printLetter(char ch){
// https://github.com/reger-men/Arduion-POV-clock/blob/master/clock.ino
  // make sure the character is within the alphabet bounds (defined by the font.h file)
  // if it's not, make it a blank character
  if (ch < 32 || ch > 126){
    ch = 32;
    }
  // subtract the space character (converts the ASCII number to the font index number)
  ch -= 32;
  // step through each byte of the character array
  for (int i=0; i<charWidth; i++) {
    char b = pgm_read_byte_near(&(font[ch][i]));
    
    for (int j=0; j<charHeight; j++) {
      digitalWrite(led_anodes[j], bitRead(b, 7-j));
    }
    dwellDelay();
  }
  
  //clear the LEDs
  for (int i = 0; i < rows; i++)
    digitalWrite(led_anodes[i] , LOW);
  dwellDelay();
}


void printLetterLower(char ch){
  // make sure the character is within the alphabet bounds (defined by the font.h file)
  // if it's not, make it a blank character
  if (ch < 32 || ch > 126){
    ch = 32;
    }
  // subtract the space character (converts the ASCII number to the font index number)
  ch -= 32;
  // step through each byte of the character array
  for (int i=charWidth-1; i>-1; i--) {
    char b = pgm_read_byte_near(&(font[ch][i]));
    for (int j=0; j<charHeight; j++) {
      digitalWrite(led_anodes[j+1], bitRead(b,j));
    }
    dwellDelay();
  }
  //clear the LEDs
  for (int i = 0; i < rows; i++)
    digitalWrite(led_anodes[i] , LOW);

  // space between letters
  dwellDelay();
}  


ISR(PCINT0_vect){  // Magnet sensed
  if (!digitalRead(SENSOR)){
    flag = true;             // Increment volatile variables
   // revolutions += 1;
  }
}

