//***************************************************************
//Lightino is an open source project develop by MakerStorage LLC.
//It is a STEM & EdTech. fidget spinner for students to learn code.
//Please contrubute and suport this project at lightino.org
// e-mail:ne@makerstorage.com
//***************************************************************

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

uint8_t led_anodes[] = {LED8, LED7, LED6, LED5, LED4, LED3, LED2, LED1};
uint8_t led_cathodes[] = {GREEN, RED, BLUE};


void setup() {

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


}

void loop() {
  TXLED0;  //TX LED OFFF
  RXLED0;  //TX LED OFFF


int QRE_Value = analogRead(SENSOR); //read optical sensor it is analog

if (QRE_Value > 900) { //sensor trigered

 AllLedsON();
 delayMicroseconds(100);

} else {

AllLedsOFF(); 

}//else

}//loop


void AllLedsON() {
  
digitalWrite(led_cathodes[0], LOW);
digitalWrite(led_cathodes[1], LOW);
digitalWrite(led_cathodes[2], HIGH);
 
for (int i = 8 ; i-- > 0 ; ){
  digitalWrite(led_anodes[i], 1);     
}

}

void AllLedsOFF() {
  
digitalWrite(led_cathodes[0], LOW);
digitalWrite(led_cathodes[1], LOW);
digitalWrite(led_cathodes[2], LOW);

for (int i = 8 ; i-- > 0 ; ){
 digitalWrite(led_anodes[i], 0);     
}

}


