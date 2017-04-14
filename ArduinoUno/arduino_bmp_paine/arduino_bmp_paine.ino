#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SoftwareSerial.h>
float paine1, paine2, paine3, paineavg;

Adafruit_BMP085 bmp; 

// this runs once
void setup() {        
    Serial.begin(9600);   
    delay(1000);     
  Serial.println("tsetuppi");
  delay(100);
  // initialize the digital pin as an output.
   
  pinMode(4, OUTPUT);
Serial.println("ok1");
  // enable debug serial
 delay(100);
  
 bmp.begin();
  
  Serial.println("setup ok");

  }


// the loop 
void loop() {
  Serial.println("looppi");   
  delay(200);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);
  delay(200);               
  paine1 = bmp.readPressure();
  delay(200);
  Serial.println("luettu ensimmäinen paine");
  paine2 = bmp.readPressure();
  delay(200);
  Serial.println("luettu toinen paine");
  paine3 = bmp.readPressure();
  delay(200);
  Serial.println("luettu kolmas paine");
  paineavg = (paine1 + paine2 + paine3) / 3 ;
  Serial.print("kaikkien kolmen keskiarvo on: "); 
  Serial.print(paineavg);
  Serial.print(" Pa \n");
  delay(1000);
}  
