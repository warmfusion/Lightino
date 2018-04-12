//***************************************************************
//Lightino is an open source project develop by MakerStorage LLC.
//It is a STEM & EdTech. fidget spinner for students to learn code.
//Please contrubute and suport this project at lightino.org
// e-mail:ne@makerstorage.com
//***************************************************************
//delay functions and graphics taken from Ken (MakerBox)
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

byte data[] = { 
  B00000100,
  B00000100,
  B00000010,
  B00000010,
  B00000010,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000010,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
  B10000000,
  B01000000,
  B00100000,
  B00010000,
  B00001000,
  B00000100,
  B00000010,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000010,
  B00000010,
  B00000010,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00000100,
  B00000100,
  B00000100,
  B00000010,
  B00000010,
  B00000001,
  B00000001,
  B00000010,
  B00000010,
  B00000100,
  B00000100,
  B00000100,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00000100
  
  
};

byte data1[] = { 
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00100001,
  B01010001,
  B01001001,
  B01001001,
  B01010001,
  B00100001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00100001,
  B01010001,
  B01001001,
  B01001001,
  B01010001,
  B00100001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00100001,
  B00010001,
  B00010001,
  B00011001,
  B00011001,
  B00011001,
  B00011001,
  B00011001,
  B00011001,
  B00011001,
  B00011001,
  B00011001,
  B00011001,
  B00011001,
  B00011001,
  B00011001,
  B00011001,
  B00011001,
  B00011001,
  B00010001,
  B00010001,
  B00100001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001
  
  
};


uint8_t led_anodes[] = {LED8, LED7, LED6, LED5, LED4, LED3, LED2, LED1};
uint8_t led_cathodes[] = {GREEN, RED, BLUE};
int color = 0; //color index 0 to 2
boolean flag=true;

unsigned long long lastTimeUs;                // time (us) magnet sensed
unsigned long long revTimeUs;                 // time (us) of last full rotation
unsigned long long dwellTimeUs;               // time (us) between LED changes (based on rotation speed)



void setup() {

 // Interupt setting
   PCMSK0 = bit (PCINT6); //Use PCINT6 = PB6 pin 30.
   PCICR |= (1<<PCIE0);   //Enable Pin change interrupt
   sei();


 // Serial.begin(9600);
 //  while (!Serial) ;
  
  TXLED1;// on board leds off
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
//  TXLED0;  //TX LED OFFF
 // RXLED0;  //TX LED OFFF






    
//ADC_TIME_13;  // 13us conversion time
//int QRE_Value = analogRead(SENSOR);

//if (!(QRE_Value > 900)) { //sensor trigered
//  flag=true;
  

//}
  

if (flag){  
flag=false;

  curTimeUs = micros();
  revTimeUs =  curTimeUs - lastTimeUs;
  lastTimeUs = curTimeUs; 
  setColor (0);  
  for(int k=0; k<72; k++){
        if (flag){
          break;
        }
    byte oneByte = data[k];
    
    for(int LED=0; LED<8; LED++){
      // color++; //increment color index
      // if (color>=3) color =0; //prevent grow up
       digitalWrite(led_anodes[LED], bitRead(oneByte,LED)); 
       if (flag){
          break;
        }
           
     }  
   
   
   dwellTimeUs = (revTimeUs * 4ul / 360ul);  //making 4ul not works

  
  
 // dwellTimeUs = (revTimeUs*0.012); 
 // dwellTimeUs = round (revTimeUs / 72);
  dwellDelay();
   //   delayMicroseconds(dwellTimeUs);
  

  }

}
 
else {
   // AllLedsOff();
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

ISR(PCINT0_vect){  // Magnet sensed
  if (!digitalRead(SENSOR)){
    flag = true;             // Increment volatile variables
   // revolutions += 1;
  }
}

