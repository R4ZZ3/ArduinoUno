// Tämä ohjelma mittaa lämpötilan ja julkaisee sen Thingspeakkiin

//kirjastot
#include "ThingSpeak.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <string.h>
#include <SoftwareSerial.h>

//muuttujat
float lampo =0;     // for temperature

//muut määritteyt
SoftwareSerial esp8266(2, 3); // RX, TX

char TCP[12]  = "\"TCP\"";
#define SSID "NETGEAR61"
#define PASS "curlygadfly298"
char Thingspeak[30] = "api.thingspeak.com";
String GET = "GET /update?=key=UBEOD86SADHLV12K&field1=";

// GET https://api.thingspeak.com/update?api_key=UBEOD86SADHLV12K&field1=0

// replace with your channel's thingspeak API key
String API = "OTD72LEDIZKGE7MP";

Adafruit_BMP085 bmp; 


///TÄSTÄ ALKAA KOODI///
// SETUPPIIIIIII
void setup() {                
  
  // Käynnistettään 
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
    if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
esp8266.begin(9600);
delay(100);

esp8266.println("AT+CWMODE=3");
delay(100);
esp8266.println("AT+CIPMUX=1");
delay(100);
esp8266.println("AT+CIPMODE=0");
delay(100);
String cmd="AT+CWJAP=\"";
cmd+=SSID;
cmd+="\",\"";;
cmd+=PASS;
cmd+="\"";
esp8266.println(cmd);
delay(5000);

}
  // LOOOOOPPPIIIIII 
void loop() {
  lampo= bmp.readTemperature();
  char lamponettiin[10];
  dtostrf(lampo,4,1, lamponettiin);
Serial.println(lamponettiin);

  //alustetaan yhteys Thingspeakkiin
char thingspeak[80] = "AT+CIPSTART=0,";
  strcat(thingspeak, "TCP");
  strcat(thingspeak, ",");
  strcat(thingspeak, Thingspeak);
  strcat(thingspeak, ",80");
  strcat(thingspeak, "\n");
  
  esp8266.println(thingspeak);
  Serial.println(thingspeak);
    delay(7000);
  void kuuntelu();
  delay(5000);

//alustetaan lähetys
String cmd = GET; 
cmd+= lamponettiin;
cmd+= "\n";

// lähetetään
esp8266.println("AT+CIPSEND=0,");
delay(2500);
esp8266.println("api.thingspeak.com/update?api_key=UBEOD86SADHLV12K&field1=20"); 
Serial.println("uuteen looppiin");
delay(20000); //odotellaan ja uudestaan  
}




void kuuntelu(){;
  if (esp8266.available()) 
    Serial.write(esp8266.read());
}

