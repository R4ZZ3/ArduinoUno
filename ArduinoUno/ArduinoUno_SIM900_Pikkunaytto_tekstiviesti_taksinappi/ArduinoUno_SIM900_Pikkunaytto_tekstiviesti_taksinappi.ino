#include <SoftwareSerial.h>
SoftwareSerial GPRS(7, 8); // RX, TX
#include <Wire.h>


#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int painike1 = 9;
int painike2 = 5;

int keltainen = 3;
int punainen = 2;

char sijainti[20];

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


char buffer[80];
byte pos = 0;
char numero[80];

int lastReceivedSMSId = 0;
boolean validSender = false;

void resetBuffer() {
  memset(buffer, 0, sizeof(buffer));
  pos = 0;
}


void setup()
{
  GPRS.begin(19200);
  Serial.begin(19200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  delay(2000);
  display.drawPixel(10, 10, WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display.display();
  delay(2000);
  display.clearDisplay();

  
  // Set as appropriate for your case
  pinMode(painike1, INPUT);
  pinMode(painike2, INPUT);
  pinMode(keltainen, OUTPUT);
  pinMode(punainen, OUTPUT);


  for (int i = 1; i <= 15; i++) {
    GPRS.print("AT+CMGD=");
    GPRS.println(i);
    delay(500);

    // Not really necessary but prevents the serial monitor from dropping any input
    while(GPRS.available()) 
      Serial.write(GPRS.read());
  }
  Serial.println("Looppiin");
  display.clearDisplay();
}

void loop()
{
  display.clearDisplay();
  display.display();
  while(GPRS.available()) {
    parseATText(GPRS.read());
  }

  if (digitalRead(painike1) == 1)
    taksin_tilaus("Laseri");
  if (digitalRead(painike2) == 1)
    taksin_tilaus("Punkkeri");
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
    if ( ptr[0] == 'o' ) {
      if ( ptr[1] == 'k' ) {
          digitalWrite(keltainen, HIGH);
          delay(5000);
          digitalWrite(keltainen, LOW);
          delay(1000);
    }
      else
        digitalWrite(5, LOW);
    }

    if ( ptr[0] == 'e' ) {
      if ( ptr[1] == 'i' ) {
        for (int i = 0; i<10; i++) {
        digitalWrite(punainen, HIGH);
        delay(500);
        digitalWrite(punainen, LOW);
        delay(500);
        }
      }
      else
        digitalWrite(4, LOW);
    }

    // tähän kellonaika näyttöön
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hei, taksi tulossa");
  display.println("Arvioitu saapumisaika");
  display.setTextColor(WHITE); // 'inverted' text
  display.setTextSize(2);
  display.print(ptr[2]);  
  display.print(ptr[3]);
  display.println(" min");
  //display.setTextSize(2);
  //display.setTextColor(BLACK, WHITE);
  //display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();
  delay(5000);
  display.clearDisplay();
  display.display();
    //kellonaika loppu
    ptr += 10;
    }
    
  GPRS.println("AT+CMGD=1");
  Serial.println("Viesti poistettu");
}


void taksin_tilaus(char sijainti[20]) {
  Serial.println("TAKSI TILATTU");
  Serial.print("Kohteeseen: ");
  Serial.println(sijainti);
  
  GPRS.println("AT+CMGF=1\r");                                                        // AT command to send SMS message
  delay(300);
  GPRS.println("AT + CMGS = \"+358442660435\"");                                     // recipient's mobile number, in international format
  delay(300);
  GPRS.print("Taksi kohteeseen ");        // message to send
  GPRS.print(sijainti);
  GPRS.println(". Vastaa ok/ei");
  delay(300);
  GPRS.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(300); 
  GPRS.println();
  Serial.println("viesti lähetetty");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Taksi");
  display.setTextColor(WHITE); // 'inverted' text
  display.println("tilattu");
  //display.setTextSize(2);
  //display.setTextColor(BLACK, WHITE);
  //display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();
  delay(5000);
  display.clearDisplay();
  display.display();

  
}



