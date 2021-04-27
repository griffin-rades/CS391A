//www.elegoo.com

#include <Servo.h> 
 
//Line Tracking IO define
#define sensor !digitalRead(4)

#define leftWheels 7
#define leftWheelsReverse 8
#define rightWheelsReverse 9
#define rightWheels 11
#define ENA 5
#define ENB 6

int carSpeed = 250;

int Echo = A4;  
int Trig = A5; 

int distanceTest() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;      
  return (int)Fdistance;
}

void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  
  while(sensor){
    digitalWrite(leftWheels, HIGH);
    digitalWrite(leftWheelsReverse, LOW);
    digitalWrite(rightWheelsReverse, LOW);
    digitalWrite(rightWheels, HIGH);
  }
   backup();
   delay(400);
   
   for(int i = 1; i <= 200; i += 10){
      delay(5);
      if(distanceTest() < 60){
          break;
       }else{
        turn();
        delay(i);
       }
   }
}

void turn(){
    analogWrite(ENA, carSpeed - 30);
    analogWrite(ENB, carSpeed - 30);
    digitalWrite(leftWheels, LOW);
    digitalWrite(leftWheelsReverse, HIGH);
    digitalWrite(rightWheelsReverse, LOW);
    digitalWrite(rightWheels, HIGH);
}

void backup(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(leftWheels, LOW);
  digitalWrite(rightWheels, LOW);
  digitalWrite(leftWheelsReverse, HIGH);
  digitalWrite(rightWheelsReverse, HIGH); 
}

void setup(){
  Serial.begin(9600);

  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
 
  pinMode(leftWheels,OUTPUT); 
  pinMode(leftWheelsReverse,OUTPUT); 
  pinMode(rightWheels,OUTPUT);
  pinMode(rightWheelsReverse,OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  delay(3000);
}

void loop() {
  forward();
}
