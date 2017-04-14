int ledPin = 13; // Määritellään pinni 13 ledPinniksi 
int ledPin2 = 12;  // Määritellään pinni 12 ledPinniksi
int state = 0;  // Määritellään alun tilaksi 0-tila
void setup() { // Tästä alkaa setup, setup suoritetaan vain kerran
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);  // Määritellään ledPin eli pin 13 OUTPUTiksi eli se on Arduinon ulostulo
  pinMode(ledPin2, OUTPUT);   // Määritellään ledPin2 eli pin 12 OUTPUTiksi eli se on Arduinon ulostulo
  digitalWrite(ledPin, LOW); // Asetetaan ledPin eli pin 13 pois päältä
  digitalWrite(ledPin2, LOW);  // Asetetaan ledPin2 eli pin 12 pois päältä
  Serial.begin(9600);  // Käynnistä Serialin kuuntelu eli Bluetooth Moduulin kuuntelu tässä tapauksessa 
}

void loop() {  // Aloitetaan looppi jota koodi suorittaa jatkuvasti
  state=0; // Asetetaan state 0
if(Serial.available() >0){   // Jos Bluetooth on hereillä/luettavissa
    state = Serial.read();     // Lue  Bluetoothilta saatava arvo ja aseta tila(state) vastaamaan Bluetoothita saatavaa arvoa
}

if (state == '0'){  // Jos Bluetoothilta luettava arvo on 0 niin...
    digitalWrite(ledPin, LOW);  // ... Sammuta ledPin 1 eli pinnissä 13 oleva led..
    digitalWrite(ledPin2, LOW);   // ... ja sammuta ledPin2 eli pinnissä 12 oleva led.
}

if (state == '3'){   // Jos Bluetoothilta luettava arvo on 3 niin...
for(int i=0; i<30; i++){  // Suorita for silmukka 30 kertaa.. 
  digitalWrite(ledPin, HIGH);  // .. Aseta ledPin eli pinnissä 13 oleva led päälle..
  delay(80);                  // .. odota 80 millisekuntia..
  digitalWrite(ledPin, LOW);  //.. aseta ledPin eli pinnissä 13 oleva led pois päältä..
  digitalWrite(ledPin2, HIGH);  //  .. Aseta ledPin2 eli pinnissä 12 oleva led päälle..
  delay(80);                     //  .. odota 80 millisekuntia..
  digitalWrite(ledPin2, LOW); // Aseta ledpin2 eli pinnissä 12 oleva led pin pois päältä.
}
}
if (state == '2'){    // Jos arvo Bluetoothilta luettava arvo on 2 niin...
for(int i=0; i<1; i++) {   // Suorita kerran
  digitalWrite(ledPin2, HIGH);  //.. Aseta ledPin2 eli pinnissä 12 oleva led päälle..
  delay(1000);                 //Odota 1000 millisekuntia
  digitalWrite(ledPin2,LOW);       // .. Aseta ledPin2 eli pinnissä 12 oleva led pois päältä.
  delay(200);                 // Odota 200 millisekuntia
}
}
else if (state == '1'){       // Muuten jos Bluetoothilta luettava arvo on 1 niin...
for(int i=0; i<1; i++){  // Tee kerran
  digitalWrite(ledPin, HIGH);   // .. Aseta ledPin eli pinnissä 13 oleva led päälle..
  delay(1000);                      // .. Odota 1000 millisekuntia
  digitalWrite(ledPin,LOW);         // ...aseta ledPin eli pinnissä 13 oleva led pois päältä.
}
}

}         /// Loop loppuu tähän jonka jälkeen alkaa uusi suoritus

