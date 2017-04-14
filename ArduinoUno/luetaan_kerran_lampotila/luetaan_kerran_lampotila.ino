#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SoftwareSerial.h>
float lampo1, lampo2, lampo3, lampoavg;

Adafruit_BMP085 bmp; 

// this runs once
void setup() {        
    Serial.begin(9600);   
    delay(1000);     
  Serial.println("tsetuppi");
  delay(100);
   
 bmp.begin();
  
  Serial.println("setup ok");

  }


// the loop 
void loop() {
  Serial.println("looppi");   
  delay(200);            
  lampo1 = bmp.readTemperature();
  delay(200);
  Serial.println(lampo1);
}  
