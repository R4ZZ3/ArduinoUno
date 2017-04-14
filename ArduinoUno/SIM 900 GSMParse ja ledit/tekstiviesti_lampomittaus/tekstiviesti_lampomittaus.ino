#include <SoftwareSerial.h>
SoftwareSerial GPRS(7, 8); // RX, TX
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <math.h>

enum _parseState {
  PS_DETECT_MSG_TYPE,

  PS_IGNORING_COMMAND_ECHO,

  PS_READ_CMTI_STORAGE_TYPE,
  PS_READ_CMTI_ID,

  PS_READ_CMGR_STATUS,
  PS_READ_CMGR_NUMBER,
  PS_READ_CMGR_SOMETHING,
  PS_READ_CMGR_DATE,
  PS_READ_CMGR_CONTENT
};

byte state = PS_DETECT_MSG_TYPE;

float lampo1, lampo2, lampo3; 
float lampoavg = 123.456;

char buffer[80];
byte pos = 0;
char numero[80];

int lastReceivedSMSId = 0;
boolean validSender = false;

void resetBuffer() {
  memset(buffer, 0, sizeof(buffer));
  pos = 0;
}

    // aloittaa anturin käytön
//Adafruit_BMP085 bmp; 

void setup()
{
  GPRS.begin(19200);
  Serial.begin(19200);
  //if (!bmp.begin()) {
  //Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  //while (1) {}
  //}


  // Set as appropriate for your case
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

  for (int i = 1; i <= 10; i++) {
    GPRS.print("AT+CMGD=");
    GPRS.println(i);
    delay(500);

    // Not really necessary but prevents the serial monitor from dropping any input
    while(GPRS.available()) 
      Serial.write(GPRS.read());
  }
}

void loop()
{
  while(GPRS.available()) {
    parseATText(GPRS.read());
  }
}

void parseATText(byte b) {

  buffer[pos++] = b;

  if ( pos >= sizeof(buffer) )
    resetBuffer(); // just to be safe

  /*
   // Detailed debugging
   Serial.println();
   Serial.print("state = ");
   Serial.println(state);
   Serial.print("b = ");
   Serial.println(b);
   Serial.print("pos = ");
   Serial.println(pos);
   Serial.print("buffer = ");
   Serial.println(buffer);*/

  switch (state) {
  case PS_DETECT_MSG_TYPE: 
    {
      if ( b == '\n' )
        resetBuffer();
      else {        
        if ( pos == 3 && strcmp(buffer, "AT+") == 0 ) {
          state = PS_IGNORING_COMMAND_ECHO;
        }
        else if ( pos == 6 ) {
          //Serial.print("Checking message type: ");
          //Serial.println(buffer);

          if ( strcmp(buffer, "+CMTI:") == 0 ) {
            Serial.println("Received CMTI");
            state = PS_READ_CMTI_STORAGE_TYPE;
          }
          else if ( strcmp(buffer, "+CMGR:") == 0 ) {
            Serial.println("Received CMGR");            
            state = PS_READ_CMGR_STATUS;
          }
          resetBuffer();
        }
      }
    }
    break;

  case PS_IGNORING_COMMAND_ECHO:
    {
      if ( b == '\n' ) {
        //Serial.print("Ignoring echo: ");
        //Serial.println(buffer);
        state = PS_DETECT_MSG_TYPE;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMTI_STORAGE_TYPE:
    {
      if ( b == ',' ) {
        Serial.print("SMS storage is ");
        Serial.println(buffer);
        state = PS_READ_CMTI_ID;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMTI_ID:
    {
      if ( b == '\n' ) {
        lastReceivedSMSId = atoi(buffer);
        Serial.print("SMS id is ");
        Serial.println(lastReceivedSMSId);

        GPRS.print("AT+CMGR=");
        GPRS.println(lastReceivedSMSId);
        //delay(500); don't do this!

        state = PS_DETECT_MSG_TYPE;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_STATUS:
    {
      if ( b == ',' ) {
        Serial.print("CMGR status: ");
        Serial.println(buffer);
        state = PS_READ_CMGR_NUMBER;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_NUMBER:
    {
      if ( b == ',' ) {
        Serial.print("CMGR number: ");
        Serial.println(buffer);

        // Uncomment these two lines to check the sender's cell number
        validSender = false;
        strcpy(numero, buffer);
        if ( strcmp(buffer, "\"+358442605379\",") == 0 ) {
          validSender = true;
        }

        validSender = true; //poistettu vertailu!!!

        if (validSender == true)
          state = PS_READ_CMGR_SOMETHING;
        else {
          GPRS.print("AT+CMGF=1\r");                                                        // AT command to send SMS message
          delay(100);
          GPRS.println("AT + CMGS = \"+358442605379\"");                                     // recipient's mobile number, in international format
          delay(100);
          GPRS.println("Joku spede yritti laittaa saunaa paalle numerosta");        // message to send
          delay(100);
          GPRS.println(buffer);
          delay(100);
          GPRS.println((char)26);                       // End AT command with a ^Z, ASCII code 26
          delay(100); 
          GPRS.println();
          Serial.println("viesti lähetetty");
          state = PS_DETECT_MSG_TYPE;
        }
          
        resetBuffer();
        
      }
    }
    break;

  case PS_READ_CMGR_SOMETHING:
    {
      if ( b == ',' ) {
        Serial.print("CMGR something: ");
        Serial.println(buffer);
        state = PS_READ_CMGR_DATE;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_DATE:
    {
      if ( b == '\n' ) {
        Serial.print("CMGR date: ");
        Serial.println(buffer);
        state = PS_READ_CMGR_CONTENT;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_CONTENT:
    {
      if ( b == '\n' ) {
        Serial.print("CMGR content: ");
        Serial.print(buffer);

        parseSMSContent();

        GPRS.print("AT+CMGD=");
        GPRS.println(lastReceivedSMSId);
        //delay(500); don't do this!

        state = PS_DETECT_MSG_TYPE;
        resetBuffer();
      }
    }
    break;
  }
}

void parseSMSContent() {

  char* ptr = buffer;

  while ( strlen(ptr) >= 2 ) {
    delay(100);
    if ( ptr[0] == 'r' ) {
      if ( ptr[1] == '1' ) {
        int c = 0;
        while (c <= 5) {
          digitalWrite(5, HIGH);
          delay(1000);
          digitalWrite(5, LOW);
          delay(1000);
          c += 2; 
        }
    }
      else
        digitalWrite(5, LOW);
    }

    if ( ptr[0] == 'm' ) {
      if ( ptr[1] == '1' ) {
        digitalWrite(4, HIGH);
        delay(5000);
        digitalWrite(4, LOW);
      }
      else
        digitalWrite(4, LOW);
    }
        if ( ptr[0] == 't' ) {
          int tsekkaus = 0;
          while (!tsekkaus) {
          /*//lampo1 = bmp.readTemperature();
          //delay(100);
          lampo2 = bmp.readTemperature();
          delay(100);
          lampo3 = bmp.readTemperature();
          delay(100);
          lampoavg = (lampo1 + lampo2 + lampo3) / 3;
          Serial.println(lampo1);
          Serial.println(lampo2);
          Serial.println(lampo3);
          delay(100);
          if (abs(lampo1-lampoavg) < 1.0 && abs(lampo1-lampoavg) < 1.0 && abs(lampo1-lampoavg) < 1.0) {
            tsekkaus = 1; */}
          }
      GPRS.print("AT+CMGF=1\r");                                                        // AT command to send SMS message
          delay(100);
          GPRS.print("AT + CMGS = ");                                     // recipient's mobile number, in international format
          GPRS.println(numero);
          delay(100);
          GPRS.println(lampoavg);        // message to send
          delay(100);
          GPRS.println((char)26);                       // End AT command with a ^Z, ASCII code 26
          delay(100); 
          GPRS.println();
          Serial.println("viesti lähetetty");
      }
    

    ptr += 2;
  }
  //GPRS.print("AT+CMGD=1");
  //Serial.println("Viesti poistettu");





