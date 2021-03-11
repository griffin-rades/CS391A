//www.elegoo.com
//2016.12.12
#include <Wire.h>
#include <DS3231.h>

DS3231 clock;
RTCDateTime dt;

int leftH; 
int rightH;
int leftM;
int rightM;


int latch=12;  //74HC595  pin 9 STCP
int clockPin=13; //74HC595  pin 10 SHCP
int data=11;   //74HC595  pin 8 DS
int controlPins[4] = {7,8,9,10};
int ledPin = 6;
int buttonPins[4] = {2,3,4,5};
int setButtonState = 0; 
int hourButtonState = 0;
int minButtonState = 0;
int alarmOnState = 0;
int hourState = 1;
int minState = 1;
int alarmON = 0; 
int alarmHour = 0;
int alarmMin = 0;


const byte numbers[10] =
{
  B11111100,  // 0
  B01100000,  // 1
  B11011010,  // 2
  B11110010,  // 3
  B01100110,  // 4
  B10110110,  // 5
  B10111110,  // 6
  B11100000,  // 7
  B11111110,  // 8
  B11110110  // 9
};

void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(data,OUTPUT);

  for (int i = 0; i < 4; i++)
  {
    pinMode(controlPins[i], OUTPUT);
    digitalWrite(controlPins[i], HIGH);
  }

  for(int i = 0; i < 4; i++){
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(ledPin, OUTPUT);

  clock.begin();
  Serial.begin(9600);
}

void setDisplay(int LH, int RH, int LM, int RM){
  //Serial.print(LH);Serial.print(RH);Serial.print(LM);Serial.println(RM);
  
    digitalWrite(latch,LOW);
    shiftOut(data,clockPin,LSBFIRST,numbers[LH]);
    digitalWrite(latch,HIGH);
    digitalWrite(controlPins[0],LOW);
    delay(3);
    
    digitalWrite(controlPins[0], HIGH);
    digitalWrite(latch,LOW);
    shiftOut(data,clockPin,LSBFIRST,numbers[RH]);
    digitalWrite(latch,HIGH);
    digitalWrite(controlPins[1],LOW);
    delay(3);

    digitalWrite(controlPins[1], HIGH);
    digitalWrite(latch,LOW);
    shiftOut(data,clockPin,LSBFIRST,numbers[LM]);
    digitalWrite(latch,HIGH);
    digitalWrite(controlPins[2],LOW);
    delay(3);

    digitalWrite(controlPins[2], HIGH);
    digitalWrite(latch,LOW);
    shiftOut(data,clockPin,LSBFIRST,numbers[RM]);
    digitalWrite(latch,HIGH);
    digitalWrite(controlPins[3],LOW);
    delay(3);

    digitalWrite(controlPins[3], HIGH);
}
void increaseHour(int hour){
  if(hour + 1 > 24){
    clock.setDateTime(dt.year, dt.month, dt.day, 1, dt.minute, 00);
  }else{
    clock.setDateTime(dt.year, dt.month, dt.day, hour + 1, dt.minute, 00);
  }
  hourState = 0;
}
void increaseMin(int minute){
  if(minute + 1 > 60){
    clock.setDateTime(dt.year, dt.month, dt.day, dt.hour, 0, 00);
  }else{
    clock.setDateTime(dt.year, dt.month, dt.day, dt.hour, minute + 1, 00);
  }
  minState = 0;
}

void increaseHourAlarm(int hour){
  if(hour + 1 > 24){
    alarmHour = 1;
  }else{
    alarmHour += 1;
  }
  hourState = 0;
}
void increaseMinAlarm(int minute){
  if(minute + 1 > 60){
    alarmMin = 0;
  }else{
    alarmMin += 1;
  }
  minState = 0;
}

void loop() {
  dt = clock.getDateTime();
 
  setButtonState = digitalRead(buttonPins[0]);
  alarmOnState = digitalRead(buttonPins[1]);
  hourButtonState = digitalRead(buttonPins[3]);
  minButtonState = digitalRead(buttonPins[2]);

//  Serial.print(hourState);
//  Serial.println(hourButtonState);
  
  if(setButtonState == 0 && alarmON == 1){
    if(hourButtonState == 0 && minButtonState == 0){
      alarmON = 0;
    }
    
    if(hourButtonState == 0 && hourState == 1){
      increaseHourAlarm(alarmHour);
    }
  
    if(minButtonState == 0 && minState == 1){
      increaseMinAlarm(alarmMin);
    }

    Serial.print(alarmHour);
    Serial.print(alarmMin);
    Serial.println(hourButtonState);
    setDisplay(alarmHour / 10, alarmHour % 10, alarmMin / 10, alarmMin % 10);

    if(hourButtonState == 1){
      hourState = 1;
    }else{
      hourState = 0;
    }
    if(minButtonState == 1){
      minState = 1;
    }else{
      minState = 0;
    }
    
  }else{
    if(alarmOnState == 0){
      alarmON = 1;
      alarmHour = 0;
      alarmMin = 0;
    }
    
    if(hourButtonState == 0 && hourState == 1){
      increaseHour(dt.hour);
    }
  
    if(minButtonState == 0 && minState == 1){
      increaseMin(dt.minute);
    }
  
    if(dt.hour == alarmHour && dt.minute == alarmMin){
      digitalWrite(ledPin, LOW);
      delay(200);
      digitalWrite(ledPin, HIGH);
      delay(200);
      digitalWrite(ledPin, LOW);
      delay(200);
      digitalWrite(ledPin, HIGH);
      delay(200);
      digitalWrite(ledPin, LOW);
      delay(200);
      digitalWrite(ledPin, HIGH);
      delay(200);
      digitalWrite(ledPin, LOW);
  
      alarmON = 0;
      alarmHour = 0;
      alarmMin = 0;
    }
  
    leftH = dt.hour / 10; 
    rightH = dt.hour;
    leftM = dt.minute / 10;
    rightM = dt.minute;
  
    setDisplay(leftH % 10 , rightH % 10 , leftM % 10, rightM % 10);
  
    if(hourButtonState == 1){
      hourState = 1;
    }else{
      hourState = 0;
    }
    if(minButtonState == 1){
      minState = 1;
    }else{
      minState = 0;
    }
  }
}
