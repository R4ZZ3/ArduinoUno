#include <SoftwareSerial.h>

SoftwareSerial esp8266(2, 3); // RX, TX
#include <Wire.h>
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;
float lampo;

char pass[12] = "\"R4ZZ392!\"";
char ssid[12] = "\"rt\"";
char TCP[12]  = "\"TCP\"";
char API[30]  = "\"api.thingspeak.com\"";


void setup() {
    pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }

  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Started");

  lampo = bmp.readTemperature();
  delay(100);
  esp8266.begin(9600);
  if (esp8266.available())
    Serial.write(esp8266.read());
  delay(2000);
  esp8266.println("AT\r\n");
  Serial.println("AT");
  delay(1000);
  void kuuntelu();
    delay(1000);
  void kuuntelu();
    delay(1000);
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
    delay(12000);
  void kuuntelu();
  delay(500);
if (esp8266.available())
    Serial.write(esp8266.read());
  esp8266.println("AT+CIPSEND=0,110");
    delay(2000);
  void kuuntelu();
  if (esp8266.available()) 
    Serial.write(esp8266.read());

  esp8266.print("GET /apps/thingtweet/1/statuses/update?api_key=LTVFCBSELWDPNJ6J&status=Hei, huoneeni lampotila on ");
  esp8266.print(lampo);
  esp8266.println("°C");
  for (int i=0;i<7;i++) {  
    delay(1000);
      kuuntelu();
  esp8266.println("");
  }

  Serial.println("looppiin");
  delay(2000);
}
  

void loop() {
  delay(60000);
  mittaus();
}

void kuuntelu() {
  for (int i=0;i<3000;i++) {
      if (esp8266.available()) {
        Serial.write(esp8266.read());
        }
  }
  }

void mittaus() {

  Serial.println("Started");

  lampo = bmp.readTemperature();
  Serial.println(lampo);
  delay(100);

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

  esp8266.print("GET /apps/thingtweet/1/statuses/update?api_key=LTVFCBSELWDPNJ6J&status=Hei, huoneeni lampotila on ");
  esp8266.print(lampo);
  esp8266.println("°C");
  for (int i=0;i<7;i++) {  
    delay(1000);
      kuuntelu();
  esp8266.println("");
  }

  delay(2000);
}

