int napintila1 = 0;
int nappilaskuri = 0;
int napintila2 = 0;
const int NAPPIPIN = 2;
int redled = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(NAPPIPIN, INPUT);
pinMode(redled, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
napintila1 = digitalRead(NAPPIPIN);
if (napintila1 != napintila2){
  nappilaskuri = nappilaskuri + 1;
}
if (nappilaskuri % 3 == 0){
  digitalWrite(redled, HIGH);
} else{
  digitalWrite(redled, LOW);
}
napintila2 = digitalRead(NAPPIPIN);
Serial.println(nappilaskuri);
}
