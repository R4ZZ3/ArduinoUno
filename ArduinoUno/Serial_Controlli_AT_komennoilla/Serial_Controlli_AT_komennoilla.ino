#include <SoftwareSerial.h>

SoftwareSerial ESP(3,2); //rx, tx  software serialissa aina ristiin 

void setup(){
  Serial.begin(9600);
  ESP.begin(9600);

  ESP.println("AT");
  delay(250);
  ESP.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
  delay(250);
  ESP.println("AT+CIPSEND=50");
  delay(250);
  ESP.println("GET //update?api_key=UBEOD86SADHLV12K&field1=7");
  delay(1000);
  ESP.println("");
  delay(1000);
  ESP.println("");
  delay(1000);
  ESP.println("");
  delay(1000);


}

void loop()
{
    delay(15000);
  ESP.println("AT");
  delay(250);
  ESP.println("AT+CWJAP=\"rt\",\"R4ZZ392!\"");
  delay(3000);
  ESP.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
  delay(250);
  ESP.println("AT+CIPSEND=50");
  delay(250);
  ESP.println("GET /update?api_key=UBEOD86SADHLV12K&field1=7");
  delay(1000);
  ESP.println("");
  delay(1000);
  ESP.println("");
  delay(1000);
  ESP.println("");
  delay(1000);
  ESP.println("AT+CIPCLOSE");
  Serial.println("joo");
}

