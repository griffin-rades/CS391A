#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long distance;
int buzzer = 8;
int led = 7;

void setup() {
   //Serial.begin(9600);
   pinMode(buzzer,OUTPUT);
   pinMode(led, OUTPUT);
   delay(1000);
}



void loop() {
   distance = sr04.Distance();
   //Serial.println(distance); 

   if(distance <= 30 && distance >= 20){
      digitalWrite(buzzer, HIGH);
      digitalWrite(led, HIGH);
      delay(300);
      digitalWrite(buzzer, LOW);
      digitalWrite(led, LOW);
      distance = sr04.Distance();
   }else if(distance < 20 && distance >= 10){
      digitalWrite(buzzer, HIGH);
      digitalWrite(led, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      digitalWrite(led, LOW);
      distance = sr04.Distance();
   }else if(distance < 10){
      digitalWrite(buzzer, HIGH);
      digitalWrite(led, HIGH);
      distance = sr04.Distance();
   }
}
