int w=0;
int b=1;
int S1;
int S2;
int S3;
int S4;
int S5;
int Speed;
void back(){
  digitalWrite(12,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
}
void stop(){
  digitalWrite(12,LOW);
  digitalWrite(4,LOW);
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
}
void right(){
  digitalWrite(12,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(4,LOW);
}
void left(){
  digitalWrite(12,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
  digitalWrite(4,HIGH);
}
void forward(){
  digitalWrite(12,LOW);
  digitalWrite(4,LOW);
  digitalWrite(8,HIGH);
  digitalWrite(7,HIGH);
}
void read(){
  S1=digitalRead(11);
  S2=digitalRead(10);
  S3=digitalRead(9);
  S4=digitalRead(6);
  S5=digitalRead(2);
}
void setup() {
  pinMode(11,INPUT);
  pinMode(10,INPUT);
  pinMode(9,INPUT);
  pinMode(6,INPUT);
  pinMode(2,INPUT);
  pinMode(4,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600);
}
void loop(){
  Speed=100;
  analogWrite(3,Speed);
  analogWrite(5,Speed);
  read();
  delay(1);
  read();
  Serial.println("Loop Start");
  while (S1==w && S2==w && S3==b && S4==w && S5==w){
    forward();
    delay(1);
    // Serial.println("Forward");
    read();
  }
  while(S1==w && S2==b && S4==w && S5==w){
    left();
    delay(1);
    forward();
    delay(1);
    Serial.println("Left align");
    read();
  }
  while(S1==w && S2==w && S4==b && S5==w){
    right();
    delay(1);
    forward();
    delay(1);
    Serial.println("Right align");
    read();
  }
  if(S1==b && S2==b && S3==b && S4==w && S5==w){
    forward();
    delay(500);
    Serial.println("Left turn sequence");
    read();
    while(S3==w){
      left();
      Serial.println("Left turning");
      delay(5);
      read();
    }
    Serial.println("Completed");
  }
  if(S1==w && S2==w && S3==b && S4==b && S5==b){
    forward();
    delay(500);
    Serial.println("Right turn sequence");
    right();
    delay(100);
    read();
    while(S3==w){
      right();
      Serial.println("Right turning");
      delay(5);
      read();
    }
    Serial.println("Completed");
  }
  if ((S1==w && S2==w && S3==w && S4==w && S5==w)){
    forward();
    delay(500);
    Serial.println("DeadEnd, U Turn");
    read();
    while(S3==w){
      right();
      delay(5);
      read();
    }
    Serial.println("U Turn Done");
  }
  if (S1==b && S2==b && S3==b && S4==b && S5==b){
    forward();
    delay(                                                                                                                                                                600);
    Serial.println("T Junction");
    read();
    while(S3==w){
      right();
      Serial.println("T Right Turning");
      delay(5);
      read();
    }
    Serial.println("T Done");
  }
}