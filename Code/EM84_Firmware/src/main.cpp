#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DISPLAY__WIDTH 128
#define DISPLAY_HEIGHT 32
#define DISPLAY_RESET -1 
#define DISPLAY_ADDRESS 0x3C
#define PIN_AIN A6

Adafruit_SSD1306 display(DISPLAY__WIDTH, DISPLAY_HEIGHT, &Wire, DISPLAY_RESET);
uint8_t lastBarHeight;
uint16_t lastAnalogVal;

void setup() 
{
  delay(1000);
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS); 
  Serial.println("EM84.");
  display.clearDisplay();
  display.display();
}

void loop() 
{
  uint16_t analogVal = analogRead(PIN_AIN);
  uint16_t averageVal = (uint16_t)(((14.0*lastAnalogVal)+analogVal)/15);
  lastAnalogVal=analogVal;
  uint8_t barHeight = (uint8_t)(averageVal*63.0/1023);
  barHeight=barHeight>63?63:barHeight;
  if(barHeight!=lastBarHeight)
  {
    display.clearDisplay();
    display.fillRect(0,8,barHeight,24,SSD1306_WHITE);
    display.fillRect((127-barHeight),8,barHeight,24,SSD1306_WHITE);
    display.display();
    lastBarHeight=barHeight;
  }
  
  delay(50);
}

