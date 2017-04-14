#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{B00000000, B11000000,
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
int nappi = 0;
int state = 0;
const int nappi1 = 2;
const int nappi2 = 3;
const int buzzer = 5;
const int ledi1 = 6;
const int ledi2 = 7;
int voitot1 = 0;
int voitot2 = 0;
void setup(){
  Serial.begin(9600);
  pinMode(nappi1, INPUT);
  pinMode(nappi2, INPUT);
  pinMode(buzzer, OUTPUT); //BUZZ
  pinMode(ledi1, OUTPUT);
  pinMode(ledi2, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.display();
delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Tervetuloa!");
  display.println("Kun kuulet aanen,"); 
  display.println("paina nappia nopeasti");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.display();
  delay(8000);
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Aloitetaan!");
  display.setTextSize(2);
  display.setCursor(20,10);
  display.println("5...");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Aloitetaan!"); 
  display.setTextSize(2);
  display.setCursor(20,10);
  display.println("4...");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Aloitetaan!");
  display.setTextSize(2);
  display.setCursor(20,10);
  display.println("3...");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Aloitetaan!");
  display.setTextSize(1);
  display.setTextSize(2);
  display.setCursor(20,10);
  display.println("2...");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Aloitetaan!");
  display.setTextSize(2);
  display.setCursor(20,10);
  display.println("1...");
  display.display();
  delay(1000);
}

void loop() {
display.clearDisplay();
display.display();
int randNumber = random(4000);
delay(randNumber);
int ok = ((digitalRead(nappi1) != 1) && (digitalRead(nappi2) != 1));
Serial.println(ok); 
if (ok == 0)
 loop();
  int voittaja = kisa();
  analogWrite(buzzer, 0);
 if (voittaja == 1) {
 digitalWrite(ledi1,HIGH);
 voitot1 += 1;
 }
   if (voittaja == 2) {
   digitalWrite(ledi2, HIGH);
 voitot2 += 1;
 }
  delay(1000);
  digitalWrite(ledi1, LOW);
  digitalWrite(ledi2, LOW);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Tilanne:");
  display.print(voitot1);
  display.print("  -  ");
  display.println(voitot2);
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
}
int kisa() {
  analogWrite(buzzer, 200);
  while (1){
  if (digitalRead(nappi1) == 1)
  return 1;
  if (digitalRead(nappi2) == 1)
  return 2;
 }
}


