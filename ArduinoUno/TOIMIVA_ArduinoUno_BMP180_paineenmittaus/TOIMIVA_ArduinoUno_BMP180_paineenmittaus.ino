#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
float paine1, paine2, paine3, paineavg;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
Serial.println("looppiin");
}

void loop() {
  paine1 = bmp.readPressure();
  delay(200);
  paine2 = bmp.readPressure();
  delay(200);
  paine3 = bmp.readPressure();
  delay(200);
  paineavg = (paine1 + paine2 + paine3) / 3;
  Serial.print("kolmen paineen keskiarvo on ");
  Serial.print(paineavg);
  Serial.print(" Pa \n");
    delay(500);
}
