#include <Arduino.h>
#define PIN_AIN A7

void setup() 
{
  pinMode(PIN_AIN, INPUT);
  Serial.begin(115200);
}

void loop() 
{
  uint16_t aVal = analogRead(PIN_AIN);
  Serial.println(aVal);
  delay(1000);
}

