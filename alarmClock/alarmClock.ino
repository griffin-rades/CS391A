//www.elegoo.com
//2016.12.12
#include <Wire.h>
#include <DS3231.h>

DS3231 clock;
RTCDateTime dt;

int latch=9;  //74HC595  pin 9 STCP
int clockPin=10; //74HC595  pin 10 SHCP
int data=8;   //74HC595  pin 8 DS
int led = 6;
int buttonOne = 5;
int buttonTwo = 4;
int buttonThree = 3;
int buttonFour = 2;

unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};

void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(data,OUTPUT);

  pinMode(led, OUTPUT);
  pinMode(buttonOne, INPUT);
  pinMode(buttonTwo, INPUT);
  pinMode(buttonThree, INPUT);
  pinMode(buttonFour, INPUT);

  clock.begin();
  clock.setDateTime(2021, 02, 02, 10, 27, 00);

  Serial.begin(9600);
}

void Display(unsigned char num)
{

  digitalWrite(latch,LOW);
  shiftOut(data,clockPin,MSBFIRST,table[num]);
  digitalWrite(latch,HIGH);
  
}
void loop() {
  dt = clock.getDateTime();
  
  Serial.print(dt.second);
  Display(3);
  delay(1000);
}
