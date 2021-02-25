int sensorPin = 10;
int blackOrWhite;
int previous;
int waitTime = 2000; 
int numLines; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);

  numLines = 0; 
  previous = digitalRead(sensorPin);
}

void change(){
    numLines += 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print(digitalRead(sensorPin));
  blackOrWhite = digitalRead(sensorPin);
  
  if(blackOrWhite != previous){ 
      if(blackOrWhite == 1){
          change();
      }
      previous = blackOrWhite;
  }else{
      previous = blackOrWhite;
  }
  delay(200);
  
  Serial.println(numLines);
}
