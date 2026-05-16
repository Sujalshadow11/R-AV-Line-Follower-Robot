int S1;
int S2;
int S3;
int S4;
int S5;
void forward(){
  digitalWrite(12,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(7,LOW);
}
void stop(){
  digitalWrite(12,LOW);
  digitalWrite(8,LOW);
  digitalWrite(4,LOW);
  digitalWrite(7,LOW);
}
void left(){
  digitalWrite(12,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(4,LOW);
  digitalWrite(7,HIGH);
}
void right(){
  digitalWrite(12,LOW);
  digitalWrite(8,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(7,LOW);
}
void setup() {
  pinMode(11,INPUT);
  pinMode(10,INPUT);
  pinMode(9,INPUT);
  pinMode(6,INPUT);
  pinMode(5,INPUT);
  pinMode(4,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(12,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  S1=digitalRead(11);
  S2=digitalRead(10);
  S3=digitalRead(9);
  S4=digitalRead(6);
  S5=digitalRead(5);
  Serial.println("Beginning");
  if (S1==S2==S3==S4==S5==0){
    stop();
    delay(1);
    Serial.println("Halt state");
  }
  if(S3==1){
    forward();
    delay(1);
    Serial.println("Going Straight");
  }
  if (S1==1 && S2==1 && S3==1 && S4==0 && S5==0){
    Serial.println("Detected Left turn");
    forward();
    delay(3000);
    Serial.println("Taken to perfect radius");
    left();
    delay(2500);
    Serial.println("Left turn done");
    }
  if (S5==1 && S4==1 && S3==1 && S1==0 && S2==0){
    Serial.println("Detected Right turn");
    forward();
    delay(3000);
    Serial.println("Taken to perfect radius");
    right();
    delay(2500);
    Serial.println("Right turn done");
  }
  if (S2==1 && S4==0){
    left();
    delay(50);
    Serial.println("Aligning to left");
    }
  if (S4==1 && S2==0){
    right();
    delay(50);
    Serial.println("Aligning to right");
    }
  if (S1==S2==S3==S4==S5==0){
    stop();
    delay(10);
    Serial.println("Halt state");
  }
  // Serial.begin(9600);
  // Serial.print(S1);Serial.print(" ");Serial.print(S2);Serial.print(" ");Serial.print(S3);Serial.print(" ");Serial.print(S4);Serial.print(" ");Serial.println(S5);
  // delay(500);
}
