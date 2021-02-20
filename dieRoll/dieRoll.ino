//www.elegoo.com
//2016.12.9

//We always have to include the library
#include "LedControl.h"

LedControl lc=LedControl(12,10,11,1);
int buttonPin = 4;
int buttonState = 0;  

/* we always wait a bit between updates of the display */
unsigned long delaytime1=100;
unsigned long longDelay=2000;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
   
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,1);
  /* and clear the display */
  lc.clearDisplay(0);
  
  Serial.begin( 9600);
}

String list[8] = {"one","two","three","four","five","six"};
byte one[8]={B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000};
byte two[8]={B00000000,B01100000,B01100000,B00000000,B00000000,B00000110,B00000110,B00000000};  
byte three[8]={B00000000,B01100110,B01100110,B00000000,B00000000,B00000110,B00000110,B00000000}; 
byte four[8]={B00000000,B01100110,B01100110,B00000000,B00000000,B01100110,B01100110,B00000000}; 
byte five[8]={B00000000,B01100110,B01100110,B00011000,B00011000,B01100110,B01100110,B00000000};
byte six[8]={B00000000,B11011011,B11011011,B00000000,B00000000,B11011011,B11011011,B00000000};

void writeOne(){
  for(int i = 0; i < 8; i++){
    lc.setRow(0, i, one[i]);
  }
}
void writeTwo(){
  for(int i = 0; i < 8; i++){
    lc.setRow(0, i, two[i]);
  }
}
void writeThree(){
  for(int i = 0; i < 8; i++){
    lc.setRow(0, i, three[i]);
  }
}
void writeFour(){
  for(int i = 0; i < 8; i++){
    lc.setRow(0, i, four[i]);
  }
}
void writeFive(){
  for(int i = 0; i < 8; i++){
    lc.setRow(0, i, five[i]);
  }
}
void writeSix(){
  for(int i = 0; i < 8; i++){
    lc.setRow(0, i, six[i]);
  }
}

void printDie(){
  writeOne();
  delay(delaytime1);
  writeTwo();
  delay(delaytime1);
  writeThree();
  delay(delaytime1);
  writeFour();
  delay(delaytime1);
  writeFive();
  delay(delaytime1);
  writeSix();
  delay(delaytime1);
}

void pickFace(){
  int num = random(1,6);
  
  if(num == 1){
    writeOne();
  }else if(num == 2){
    writeTwo();
  }else if(num == 3){
    writeThree(); 
  }else if(num == 4){
    writeFour();
  }else if(num == 5){
    writeFive();
  }else if(num == 6){
    writeSix();
  }
  delay(longDelay);
}

void loop() { 
  buttonState = digitalRead(buttonPin);
  if(buttonState == LOW){
    pickFace();
  }else{
    printDie();
  }
  buttonState = digitalRead(buttonPin);
}
