
// otetaan LCD-kirjasto käyttöön
#include <LiquidCrystal.h>
//määritetään ohjelmalle käytössä olevat Arduinon pinnit 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int buzzer = 6; 
const int nappi1 = 8;
const int nappi2 = 9;
int state = 0;
int voitot1 = 0;
int voitot2 = 0;
void setup() {
  //asetetaan LCD-näytön rivien ja sarakkeiden lukumäärä 
  lcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  lcd.setCursor(0,0);
  lcd.print("Tervetuloa!");
  delay(5000);
  lcd.clear();
  
  } 

void loop() {
lcd.clear();
int randNumber = random(4000);
delay(randNumber);
int ok = ((digitalRead(nappi1) != 1) && (digitalRead(nappi2) != 1));
Serial.println(ok); 
if (ok == 0)
 loop();
  int voittaja = kisa();
  analogWrite(buzzer, 0);
 if (voittaja == 1) {
 //digitalWrite(ledi1,HIGH);
 voitot1 += 1;
 }
   if (voittaja == 2) {
   //digitalWrite(ledi2, HIGH);
 voitot2 += 1;
 }
  delay(1000);
  //digitalWrite(ledi1, LOW);
  //digitalWrite(ledi2, LOW);
  lcd.setCursor(0,0);
  lcd.print("Tilanne:");
  lcd.setCursor(0,1);
  lcd.print(voitot2);
  lcd.print("-");
  lcd.print(voitot1);
  delay(2000);
  lcd.clear();
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


