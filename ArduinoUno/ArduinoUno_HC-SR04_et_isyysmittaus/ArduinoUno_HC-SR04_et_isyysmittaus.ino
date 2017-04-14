#define trigPin 8 // Määritellään Arduinon digitaalinen pin 8 yhdistettäväksi HC-SR04:n trig pinniin
#define echoPin 7  // Määritellään Arduinon digitaalinen pin 7 yhdistettäväksi HC-SR04:n echo pinniin
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(trigPin, OUTPUT);   //Määritellään trigPin OUTPUTiksi eli se kuuntelee Arduinolta tulevia käskyjä
pinMode(echoPin, INPUT);   // Määritellään echoPin INPUTiksi eli se antaa Arduinolle tietoa

pinMode(5, OUTPUT);  // Määritellään buzzer kuuntelemaan Arduinoa
}


void loop() {  // Arduinoa suorittaa loopissa olevaa koodia jatkuvasti
  // put your main code here, to run repeatedly:
float duration;  //Määritellään kesto desimaaliluvuksi
float distance;   //Määritellään etäisyys desimaaaliluvuksi
digitalWrite(trigPin, HIGH);  //Laitetaan trigPin päälle, HC-SR04 lähettää ääntä
delayMicroseconds(1000);       //Odotetaan 1000 mikrosekuntia eli 1 millisekunti
digitalWrite(trigPin, LOW);    // Otetaan trigPin pois päältä
duration = pulseIn(echoPin, HIGH);  //echoPin ottaa vastaan HC-SR04:n lähettämän ääniaalloon ja laskee siitä ääniaallon kulkeman matkan
distance = ("%.2f", duration/2) /29,1 ; // Tässä saatu muttuja muutetaan kahdella desimaalilla määritellyksi senttimetri arvoksi
Serial.print (distance); //Saatu etäisyys tulostetaan SerialMonitoriin
Serial.println (" cm");  // Laitetaan vielä yksikkö perään ;)
delay(40);  //Odotetaan 40 millisekuntia

if (distance < 30)  // Tarkistetaan onko saatu etäisyys < 30 cm ja jos on...
  analogWrite(5, 200);   // ... laitetaan pinni 5 eli Buzzer päälle...
else                      //... muuten...
  analogWrite(5, 0);   // ... sen annetaan olla hiljaa.

}  // Tähän loppuu loop jonka jälkeen loop alkaa alusta
