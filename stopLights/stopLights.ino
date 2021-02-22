int tDelay = 100;
int latchPin = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;     // (12) DS [S1] on 74HC595
unsigned long delays[3] = {3000,1700,3000};
boolean restartFlag = false;

byte leds = 0;

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}

void setup() 
{
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  leds = 0;

  setOne();
}
void restart(){
  leds = 0;
  
  updateShiftRegister();

  setOne();
}

void setOne(){
  int lightsOne[4] = {4,3,2,5};

  for(int i = 0; i < 3; i++){
    if(i == 2){
      bitSet(leds, i);
      setTwo();
    }else{
      bitSet(leds, lightsOne[3]);
      bitSet(leds, lightsOne[i]);
      updateShiftRegister();
      delay(delays[i]);
      leds = 0;
    }
  }
}

void setTwo(){
  int lightsTwo[4] = {7,6,5,2};
  for(int i = 0; i < 3; i++){
    if(i == 2){
      restart();
    }else{
      bitSet(leds, lightsTwo[3]);
      bitSet(leds, lightsTwo[i]);
      updateShiftRegister();
      delay(delays[i]);
      leds = 0;
    }
  }
}

void loop() {
  
}
