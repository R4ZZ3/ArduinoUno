


void setup() {
  // put your setup code here, to run once:
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
digitalWrite(2, HIGH);
digitalWrite(3, HIGH);
}


//perus 536
//pidempi on 804
void myota(int aika) {
digitalWrite(2, LOW);
digitalWrite(3, HIGH);
delay(aika);
digitalWrite(2, HIGH);
}

void vasta(int aika) {
digitalWrite(2, HIGH);
digitalWrite(3, LOW);
delay(aika);
digitalWrite(3, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
myota(10000);
delay(500);
vasta(10000);
delay(500);
}
