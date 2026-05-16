#include<SparkFun_TB6612.h>
#define AIN1 8
#define AIN2 9
#define BIN1 6
#define BIN2 7
#define PWMA 10
#define PWMB 11
#define STBY 5
#define fspeed 100
#define tspeed 100
#define fdelay 200
#define ldelay 6568
#define rdelay 658
#define ts 220
#define ds1 150
#define ds2 100

const int offsetA = 1;
const int offsetB = 1;

const int sensorPins[4] = {A0,A1,A6,A7};
float minValues[4], maxValues[4], threshold[4];

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int edge=0;
bool end=1,ans;
// white = low value  and   black = high value

int readSensor() {
  int sensorValues[4];
  int result = 0;

  for (int i = 0; i < 4 ; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
    if (sensorValues[i] > threshold[i]) {
      result |= (1 << i);
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

void iPID80(){
  int lef,rig;
  lef=analogRead(A4);
  rig=analogRead(A3)-100;
  float Kp,Kd,Ki;                       //sp=120
  Kp=0.0555;                             //0.0855
  Kd=0.0218;                            //0.01
  Ki=0.002;                             //0.002
  float error=lef-rig;
  float preverror;
  float prop=error;
  float deriv=error-preverror;
  float integ=integ+error; 
  float sol=(Kp*prop)+(Kd*deriv)+(Ki*integ);
  int speedr=80-sol; //+
  int speedl=80+sol; //-
  int leftspeed=constrain(speedl,-255,255);
  int rightspeed=constrain(speedr,-255,255);
  motor2.drive(leftspeed);
  motor1.drive(rightspeed);
  preverror=error;
  lef=analogRead(A4);
  rig=analogRead(A3)-100;
}

void oPID100(){
  int newlef,newrig;
  newlef=analogRead(A5);
  newrig=analogRead(A2);
  float Kpo,Kdo,Kio;                       //sp=120
  Kpo=0.041;                             //0.0855
  Kdo=0.0058;                            //0.01
  Kio=0.006;                             //0.002
  float erroro=newlef-newrig;
  float preverroro;
  float propo=erroro;
  float derivo=erroro-preverroro;
  float intego=intego+erroro; 
  float solo=(Kpo*propo)+(Kdo*derivo)+(Kio*intego);
  int speedro=80-solo; //+
  int speedlo=80+solo; //-
  int leftspeedo=constrain(speedlo,-255,255);
  int rightspeedo=constrain(speedro,-255,255);
  motor2.drive(leftspeedo);
  motor1.drive(rightspeedo);
  preverroro=erroro;
  newlef=analogRead(A5);
  newrig=analogRead(A2);
}

void dryRun100l(){                                         //speed=150  |  left dominance
  int previousdata=readSensor();
  int lef,rig,newlef,newrig,DN;
  lef=analogRead(A4);
  rig=analogRead(A3);
  iPID80();
  newlef=analogRead(A2);
  newrig=analogRead(A5);
  oPID100();
  DN=digitalRead(3);
  delayMicroseconds(1);

  if(previousdata==0b0000){     //T
    forward(motor1,motor2,fspeed);
    delay(ds2);
    left(motor2, motor1,150);
    delay(250);
    // brake(motor1,motor2);
    // delay(300);
    previousdata=readSensor();
    lef=analogRead(A4);
    rig=analogRead(A3);
    while(rig>=300 && lef>=300){
      left(motor2, motor1,150);
      lef=analogRead(A4);
      rig=analogRead(A3);
    }
  }

  else if (previousdata==0b1100){     //right
    previousdata=readSensor();
    forward(motor1,motor2,fspeed);
    delay(ds2);
    previousdata=readSensor();
    lef=analogRead(A4);
    rig=analogRead(A3);
    while(lef>=300 && rig>=300){
      right(motor2, motor1,150);
      lef=analogRead(A4);
      rig=analogRead(A3);
    }
  }

  else if(previousdata==0b0011){      //left
    previousdata=readSensor();
    forward(motor1,motor2,fspeed);
    delay(ds2);
    left(motor2, motor1,150);
    delay(250);
    // brake(motor1,motor2);
    // delay(300);
    previousdata=readSensor();
    lef=analogRead(A4);
    rig=analogRead(A3);
    while(rig>=300 && lef>=300){
      left(motor2, motor1,150);
      lef=analogRead(A4);
      rig=analogRead(A3);
    }
  }

  // else if(previousdata==0b1111 && DN==1){
  //   forward(motor1,motor2,fspeed);
  //   delay(ds2);
  //   brake(motor1,motor2);
  //   delay(300);
  //   previousdata=readSensor();
  //   lef=analogRead(A4);
  //   rig=analogRead(A3);
  //   while(rig>=200 && lef>=200){
  //     left(motor2, motor1,150);
  //     lef=analogRead(A4);
  //     rig=analogRead(A3);
  //   }
  // }
  lef=analogRead(A4);
  rig=analogRead(A3);
  iPID80();
  newlef=analogRead(A2);
  newrig=analogRead(A5);
  oPID100();
  previousdata=readSensor();
}

void setup() {
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}

void loop(){
  digitalWrite(0,LOW);
  digitalWrite(1,LOW);
  while(digitalRead(12)){
    delay(1000);
    while(1){
      iPID80();
    }
  }
  while(digitalRead(13)){
    delay(1000);
    calibrateRight();
    delay(500);
    calibrateRight();
  }
  while(digitalRead(4)){
    delay(1000);
    while(1){
      iPID80();
      delayMicroseconds(1);
      oPID100();
      delayMicroseconds(1);
      dryRun100l();  
      delayMicroseconds(1);
      iPID80();
      delayMicroseconds(1);
      oPID100();
      delayMicroseconds(1);
}
}
}























// char raw[100]={'L','B','L','L','L','B','S','B','L','L','B','S','L','L'};
char raw[100]={'L','B','L','L','S','L','B','L','B','S','L','L','R','B','L','L','S','L','L','B','L','S','L','S','L','B','L','L','S','B','L','B','L','R','S','L','L','B','L','L','L','B','L','L','L','B','L','B','S','L','L','R'};
char pro[100]={ };
int i,j,k,l;
int main() {
    for(int a=0;a<100;a++){
        
        for (i=0,j=0;i<100,j<100;i++,j++){
            
            if(raw[i]=='L' && raw[i+1]=='B' && raw[i+2]=='L'){
                pro[j]='S';
                
                for(k=(i+3);k<100;k++){
                    pro[k-2]=raw[k];
                }
                for(l=0;l<100;l++){
                    raw[l]=pro[l];
                }
                break;
            }
            
            else if(raw[i]=='S' && raw[i+1]=='B' && raw[i+2]=='S'){
                pro[j]='B';
                
                for(k=(i+3);k<100;k++){
                    pro[k-2]=raw[k];
                }
                for(l=0;l<100;l++){
                    raw[l]=pro[l];
                }
                break;
            }
            
            else if(raw[i]=='S' && raw[i+1]=='B' && raw[i+2]=='L'){
                pro[j]='R';
                for(k=(i+3);k<100;k++){
                    pro[k-2]=raw[k];
                }
                for(l=0;l<100;l++){
                    raw[l]=pro[l];
                }
                break;
            }
            
            else if(raw[i]=='R' && raw[i+1]=='B' && raw[i+2]=='L'){
                pro[j]='B';
                for(k=(i+3);k<100;k++){
                    pro[k-2]=raw[k];
                }
                for(l=0;l<100;l++){
                    raw[l]=pro[l];
                }
                break;
            }
            
            else if(raw[i]=='L' && raw[i+1]=='B' && raw[i+2]=='S'){
                pro[j]='R';
                for(k=(i+3);k<100;k++){
                    pro[k-2]=raw[k];
                }
                for(l=0;l<100;l++){
                    raw[l]=pro[l];
                }
                break;
            }
            
            else if(raw[i]=='L' && raw[i+1]=='B' && raw[i+2]=='R'){
                pro[j]='B';
                for(k=(i+3);k<100;k++){
                    pro[k-2]=raw[k];
                }
                for(l=0;l<100;l++){
                    raw[l]=pro[l];
                }
                break;
            }
            
            else{
                pro[j]=raw[i];
            }
        }
    }
    return 0;
}
void setup() {

}

void loop() {

}
