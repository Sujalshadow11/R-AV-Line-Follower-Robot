#include <EEPROM.h>
void setup() {
  Serial.begin(9600);
  for(int i=0;i<101;i++){
    Serial.print(EEPROM.read(i));
    Serial.print(" ");
  }
  Serial.println(" ");
}

void loop() {
  for(int i=100;i<201;i++){
    float vall=EEPROM.read(i);
    Serial.print(vall);
    Serial.print(" ");
  }
  Serial.println(" ");
  delay(10000);
}
