#include <SoftwareSerial.h>
#define trigPin 5
#define echoPin 4
SoftwareSerial esp8266(2, 3); // RX, TX
#include <Wire.h>

char pass[12] = "\"R4ZZ392!\"";
char ssid[12] = "\"rt\"";
char TCP[12]  = "\"TCP\"";
char API[30]  = "\"api.thingspeak.com\"";


void setup() {
  int tila = 0;
  int nyktila = 0;

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.println("Started");

  delay(100);
  esp8266.begin(9600);
  if (esp8266.available())
    Serial.write(esp8266.read());
  delay(2000);
  esp8266.println("AT\r\n");
  void kuuntelu();
  
  esp8266.println("AT+CWMODE=3");
    delay(2000);
  void kuuntelu();
    esp8266.println("AT+CIPMUX=1");
    delay(2000);
  void kuuntelu();
  esp8266.println("AT+CIPMODE=0");
  if (esp8266.available())
    Serial.write(esp8266.read());
  char yhdistys[50] = "AT+CWJAP=";
  strcat(yhdistys, ssid);
  strcat(yhdistys, ",");
  strcat(yhdistys, pass);
  strcat(yhdistys, "\n");
  esp8266.println(yhdistys);
  Serial.println(yhdistys);
  delay(7000);
  void kuuntelu();
  delay(2000);
  char thingspeak[80] = "AT+CIPSTART=0,";
  strcat(thingspeak, TCP);
  strcat(thingspeak, ",");
  strcat(thingspeak, API);
  strcat(thingspeak, ",80");
  strcat(yhdistys, "\n");
  esp8266.println(thingspeak);
  Serial.println(thingspeak);
    delay(7000);
  void kuuntelu();

  delay(500);

  if (esp8266.available())
    Serial.write(esp8266.read());


  esp8266.println("AT+CIPSEND=0,110");
  
  delay(2000);
  void kuuntelu();
  if (esp8266.available()) 
    Serial.write(esp8266.read());

  esp8266.println("GET /apps/thingtweet/1/statuses/update?api_key=LTVFCBSELWDPNJ6J&status=Moi, olen postilaatikko :) #Posti");
  for (int i=0;i<5;i++) {  
    delay(1000);
      kuuntelu();
  esp8266.println("");
  }

  Serial.println("looppiin");
  delay(2000);
}
  

void loop() {
  int nyktila= 0;
  int tila=0;
  Serial.print("Tila on: ");
  Serial.println(nyktila);
  delay(3000);
  float etaisyys = mittaus();
  if (etaisyys < 5.00) {
    nyktila = 1;
  }
  else
    nyktila = 0;

  if (nyktila == tila) 
    delay(100);
  else {
    if (nyktila == 1 and tila == 0){ //posti tullut, ennen ei postia, nyt postia
      twitter();
      delay(50000);
    }
    else (nyktila == 0 and tila == 1); //posti haettu, ennen oli postia, nyt ei
      tila = 0;
  }

  }

void kuuntelu() {
  for (int i=0;i<2000;i++) {
      if (esp8266.available()) {
        Serial.write(esp8266.read());
        }
  }
  }

///////////////// TARKISTETAAN ONKO POSTIA ////////////////
float mittaus() {
  float duration;
  float distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = ("%.2f", duration/2) /29,1 ;
  Serial.print (distance);
  Serial.println (" cm");
  delay(250);
  return distance;
}

////////// LÄHETETÄÄN TWITTERIIN ILMOITUS POSTISTA ////////
void twitter() {


  if (esp8266.available())
    Serial.write(esp8266.read());
  delay(2000);
  esp8266.println("AT\r\n");
  
  void kuuntelu();
  
  if (esp8266.available())
    Serial.write(esp8266.read());
  char yhdistys[50] = "AT+CWJAP=";
  strcat(yhdistys, ssid);
  strcat(yhdistys, ",");
  strcat(yhdistys, pass);
  strcat(yhdistys, "\n");
  esp8266.println(yhdistys);
  Serial.println(yhdistys);
  delay(7000);
  void kuuntelu();
  delay(2000);
  char thingspeak[80] = "AT+CIPSTART=0,";
  strcat(thingspeak, TCP);
  strcat(thingspeak, ",");
  strcat(thingspeak, API);
  strcat(thingspeak, ",80");
  strcat(yhdistys, "\n");
  esp8266.println(thingspeak);
  Serial.println(thingspeak);
    delay(7000);
  void kuuntelu();
  delay(500);
if (esp8266.available())
    Serial.write(esp8266.read());
  esp8266.println("AT+CIPSEND=0,110");
    delay(2000);
  void kuuntelu();
  if (esp8266.available()) 
    Serial.write(esp8266.read());

  esp8266.println("GET /apps/thingtweet/1/statuses/update?api_key=LTVFCBSELWDPNJ6J&status=Hei, olet saanut postia!");
  for (int i=0;i<7;i++) {  
    delay(1000);
      kuuntelu();
  }

  delay(2000);
  kuuntelu();
}

