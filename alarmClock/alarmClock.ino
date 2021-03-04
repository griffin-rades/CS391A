//www.elegoo.com
//2016.12.12
#include <Wire.h>
#include <DS3231.h>

DS3231 clock;
RTCDateTime dt;

int latch=12;  //74HC595  pin 9 STCP
int clockPin=13; //74HC595  pin 10 SHCP
int data=11;   //74HC595  pin 8 DS
int controlPins[4] = {10,9,8,7};


const byte numbers[10] =
{
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111  // 9
};

void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(data,OUTPUT);

  for (int i = 0; i < 4; i++)
  {
    pinMode(controlPins[i], OUTPUT);
  }

  clock.begin();
  //clock.setDateTime(2021, 03, 03, 07, 36, 00);

  Serial.begin(9600);
}

void Display(unsigned char num)
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(controlPins[i], HIGH);
  }
  
  digitalWrite(latch,LOW);
  shiftOut(data,clockPin,MSBFIRST,numbers[9]);
  digitalWrite(latch,HIGH);

  digitalWrite(controlPins[1], LOW);
}
void loop() {
  dt = clock.getDateTime();
  
  Serial.print(dt.hour);
  Serial.print(dt.minute);
  Display(3);
  delay(1000);
}
