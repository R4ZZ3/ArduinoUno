#include <SoftwareSerial.h> //Software Serial is needed to interface with ESP8266 because the hardware serial 
//is being used for monitoring Serial line with computer during trouble shooting.
SoftwareSerial ESP8266(10,11);//RX,TX
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
char ssid[] = "<YOURNETWORK>";          //  your network SSID (name) 
char pass[] = "<YOURPASSWORD>";   // your network password
int status = WL_IDLE_STATUS;
WiFiClient  client;

#include <Wire.h>
#include <Adafruit_BMP085.h>

#define IP "184.106.153.149" // thingspeak.com IP address; see their website for more detail
String GET = "GET /update?api_key=5R39CPOEIOZND7GW&field"; // you channel will have unique code. osoite fieldiin asti
String field1="1=";

float paine;

unsigned long myChannelNumber = 122412;
const char * myWriteAPIKey = "5R39CPOEIOZND7GW";

Adafruit_BMP085 bmp;

void setup() {
       
  Serial.begin(9600); // this is to start serial monitoring with your Arduino IDE Serial monitor.
  ESP8266.begin(9600); // this is to start serial communication with the ESP via Software Serial.
  ESP8266.println("AT+RST"); // this resets the ESP8266.
  Serial.println("AT+RST"); // this is just echoing the command to your serial monitor so you can
  // follow what is going on - this is not really needed.
  // through out the code below I echo almost everything to the Serial monitor which you
  // you don't have to do and can eliminate from the code.

  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }

 WiFi.begin(ssid, pass);
   ThingSpeak.begin(client);
  delay(2000);

  ESP8266.println("AT");
  Serial.println("AT");
  
  delay(5000);
  if(ESP8266.find("OK")){
      Serial.println("OK");  
  
      Serial.println("Connected");
  }    
}

void loop() {
  delay(2000);
  paine = bmp.readPressure();
  char buffer[16];
  Serial.println("in the main loop");
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)


  //update(paine,field1); 
  ThingSpeak.writeField(myChannelNumber, 1, paine, myWriteAPIKey);
  delay(15000);  
  delay(1000);
  Serial.println("loop-de-loop");  
}

void update(float value, String field){

  Serial.println("in the update loop"); 
  ESP8266.println("AT+RST"); // it seems that mine works better if I reset it everytime before I do CIPSTART
  Serial.println("AT+RST");
  delay(5000);
  String cmd = "AT+CIPSTART=\"TCP\",\""; //standard code. see https://github.com/espressif/esp8266_at/wiki //
  cmd += IP; // += is concatenating the previous cmd string with the content of IP
  cmd += "\",80"; // same thing here it just keep adding stuff to the cmd string content

  ESP8266.println(cmd);//type in the string in cmd into the ESP8266
  Serial.println(cmd);
  delay(5000);
  
  if(ESP8266.find("Error")){
    Serial.println("AT+CIPSTART Error");
    return;
  }
  cmd = GET;
  cmd += field;
  cmd += value;
  cmd += "\r\n\r\n"; // it seems that this part is important, to input enough \r\n, mine does not work if I only have one pair.
  ESP8266.print("AT+CIPSEND="); 
  ESP8266.println(cmd.length());
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  delay(17000);
  if(ESP8266.find(">")){ // if ESP8266 return the > prompt back from the CIPSEND command, you are set, if not something is wrong
    ESP8266.print(cmd); //type in the GET command string and done
    Serial.print(">");
    Serial.println(cmd);

  }
  else
  {
   //Serial.println("AT+CIPCLOSE"); //this command somehow does not work and always return errors so I just comment it out
   Serial.println("AT+CIPSEND error");
  }
}


