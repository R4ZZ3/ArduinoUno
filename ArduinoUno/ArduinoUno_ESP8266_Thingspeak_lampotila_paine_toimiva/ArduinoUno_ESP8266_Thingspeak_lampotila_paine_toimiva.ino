#include <SoftwareSerial.h>
#include <stdlib.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

SoftwareSerial ESP(3,2);

char laini[68];

void setup(){
  delay(1000);
  Serial.begin(9600);
    if (!bmp.begin()) {
      Serial.println("Could not find a valid BMP085 sensor, check wiring!");
      while (1) {}
      }
  ESP.begin(9600);
  delay(500);
  //ESP.println("AT+CWJAP=\"theswitch-visitor\",\"salaKala911\"");
  ESP.println("AT+CWJAP=\"NETGEAR61\",\"curlygadfly298\"");
  //ESP.println("AT+CWJAP=\"rt\",\"R4ZZ392!\"");
  delay(2000);
  ESP.println("AT");
  if (ESP.find("OK"))
    Serial.println("AT OK");


}

void loop() {
  float C = mittausC();
  int P = mittausP();
  Serial.println(P);
  Serial.println(C);
  delay(500);
  ESP.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
  delay(2000);
  ESP.println("AT+CIPSEND=68");
  
  if (ESP.find(">")) {
      laini[68] =="\n";
      int c1 = C;
      float f = C - c1;
      int c2 = trunc(f*100);
      int p1 = P;
      Serial.println(p1);
      sprintf(laini, "GET /update?api_key=UBEOD86SADHLV12K&field1=%d.%02d&field2=%d\n", c1, c2, P);
      Serial.println(laini);
      ESP.println(laini);
      delay(1000);
      ESP.println("");
      delay(1000);
      ESP.println("");
      delay(1000);
      ESP.println("");
    }
  else {
    ESP.println("AT+CIPCLOSE");
    Serial.println("AT+CIPCLOSE");
  }
  
  delay(20000);
}


float mittausC() {
   float lampotila = bmp.readTemperature();
   if (lampotila<50 && lampotila>-30)
    return(lampotila);
   else
    mittausC();
}

int mittausP() {
  int paine = bmp.readPressure()/100;
  return(paine);
}  


