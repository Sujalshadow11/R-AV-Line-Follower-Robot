#include<SparkFun_TB6612.h>

//Out1/2/3/4/5--> A1/A2/A3/A4/A5 
#define AIN1 8
#define AIN2 9
#define BIN1 6
#define BIN2 7
#define PWMA 10
#define PWMB 11
#define STBY 5
#define fspeed 80
#define tspeed 120
#define fdelay 250
#define ldelay 658
#define rdelay 658
#define ts 220
#define ds 115                  //325
const int offsetA = 1;
const int offsetB = 1;
const int sensorPins[4] = {A0,A1,A6,A7};   //FROM BACKSIDE VIEW                     DIGITAL : A7,A6,A1,A0               ANALOG : A5,A4,A3,A2                           //right-->>left A0,A1,A6,A3,A4,A7 black = 1 and white = 0 
float minValues[4], maxValues[4], threshold[4];
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
int edge=0;
bool end=1,ans;




int readSensor() {
  int sensorValues[4];
  int result = 0;

  for (int i = 0; i < 4 ; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
    if (sensorValues[i] > threshold[i]) {
      result |= (1 << i); // Set the corresponding bit if the sensor is active
    }
  }
  return result;
}





void calibrateRight() {
  for (int i = 0; i < 4; i++) {
    minValues[i] = analogRead(sensorPins[i]);
    maxValues[i] = minValues[i];
  }

  for (int i = 0; i < 4000; i++) {
    right(motor2, motor1, 255);
    for (int j = 0; j < 4; j++) {
      int sensorValue = analogRead(sensorPins[j]);
      if (sensorValue < minValues[j]) {
        minValues[j] = sensorValue; 
      }
      if (sensorValue > maxValues[j]) {
        maxValues[j] = sensorValue;
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    threshold[i] = (minValues[i] + maxValues[i]) / 2;
  }
  brake(motor1, motor2);
}





void PIDO(){
  int newlef,newrig;
  newlef=analogRead(A5);
  newrig=analogRead(A2);
  float KpO,KdO,KiO;                       //sp=80;
  KpO=0.560;                          //0.0775;
  KdO=0.0;                            //0.0278  0.0276365;
  KiO=0.0;                             //0.008;
  float errorO=newlef-newrig;
  float preverrorO;
  float propO=errorO;
  float derivO=errorO-preverrorO;
  float integO=integO+errorO; 
  float solO=(KpO*propO)+(KdO*derivO)+(KiO*integO);
  int speedr=120+solO;
  int speedl=120-solO;
  int leftspeed=constrain(speedl,-255,255);
  int rightspeed=constrain(speedr,-255,255);
  motor2.drive(leftspeed);
  motor1.drive(rightspeed);
  preverrorO=errorO;
  newlef=analogRead(A5);
  newrig=analogRead(A2);
}

void PIDI(){
  int lef,rig;
  lef=analogRead(A4);
  rig=analogRead(A3);
  float KpI,KdI,KiI;                       //sp=80;
  KpI=0.12;                             //0.0775;
  KdI=0.0045;                            //0.0278  0.0276365;
  KiI=0.001;                             //0.008;
  float errorI=lef-(rig+rig*0.111);
  float preverrorI;
  float propI=errorI;
  float derivI=errorI-preverrorI;
  float integI=integI+errorI; 
  float solI=(KpI*propI)+(KdI*derivI)+(KiI*integI);
  int speedr=120+solI;
  int speedl=120-solI;
  int leftspeed=constrain(speedl,-255,255);
  int rightspeed=constrain(speedr,-255,255);
  motor2.drive(leftspeed);
  motor1.drive(rightspeed);
  preverrorI=errorI;
  lef=analogRead(A4);
  rig=analogRead(A3);
}




void dryRun(){
  int previousdata=readSensor();
  int lef,rig,newlef,newrig;
  newlef=analogRead(A5);
  newrig=analogRead(A2);
  lef=analogRead(A4);
  rig=analogRead(A3);
  PIDI();
  PIDO();
  delayMicroseconds(1);
  if(previousdata==0b1111){
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
    forward(motor1,motor2,fspeed);
    delay(ds);
    int previousdata=readSensor();
    if(previousdata==0b1111){
    brake(motor1, motor2);
    delay(15000);}
    previousdata=readSensor();
    lef=analogRead(A4);
    rig=analogRead(A3);
    brake(motor1, motor2);
    delay(20);
    while(rig<=300 && lef<=300){
      right(motor2, motor1,150);
      lef=analogRead(A4);
      rig=analogRead(A3);
    }
    brake(motor1, motor2);
    delay(1000);
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
  }
  else if (previousdata==0b0011){
    digitalWrite(2,HIGH);
    previousdata=readSensor();
    forward(motor1,motor2,fspeed);
    delay(ds);
    right(motor2,motor1,150);
    delay(200);
    lef=analogRead(A4);
    rig=analogRead(A3);
    brake(motor1, motor2);
    delay(20);
    while(lef<=300 && rig<=300){
      right(motor2, motor1,150);
      lef=analogRead(A4);
      rig=analogRead(A3);
    }
    brake(motor1, motor2);
    delay(1000);
    digitalWrite(2,LOW);
  }
  else if(previousdata==0b1100){
    digitalWrite(3,HIGH);
    previousdata=readSensor();
    forward(motor1,motor2,fspeed);
    delay(ds);
    lef=analogRead(A4);
    rig=analogRead(A3);
    brake(motor1, motor2);
    delay(20);
    while(rig<=300 && lef<=300){
      left(motor2, motor1,150);
      lef=analogRead(A4);
      rig=analogRead(A3);
    }
    brake(motor1, motor2);
    delay(1000);
    digitalWrite(3,LOW);
  }
  lef=analogRead(A4);
  rig=analogRead(A3);
  PIDI();
  PIDO();
  delayMicroseconds(1);
  lef=analogRead(A4);
  rig=analogRead(A3);
  previousdata=readSensor();
}

void setup() {
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  pinMode(13,INPUT_PULLUP);
}



void loop(){
  digitalWrite(0,LOW);
  digitalWrite(1,LOW);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  while(digitalRead(4)){
    delay(1000);
    calibrateRight();
  }
  while(digitalRead(12)){
    delay(1000);
    while(1){
      PIDI();
      PIDO();
    }
  }
  while(digitalRead(13)){
    delay(1000);
    while(1){
      int previousdata=readSensor();
      int lef,rig;
      lef=analogRead(A4);
      rig=analogRead(A3);
      dryRun();
    }
  }
}