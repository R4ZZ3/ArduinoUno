


void setup() {
  // put your setup code here, to run once:
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
digitalWrite(2, HIGH);
digitalWrite(3, HIGH);
}


//perus 536
//pidempi on 804

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(2, LOW); // 0
delay(536);
digitalWrite(3,LOW); // 3
delay(536);
digitalWrite(3,HIGH); // 5
digitalWrite(2, HIGH);
delay(804);

digitalWrite(2, LOW); // 0
delay(536);
digitalWrite(3,LOW); // 3
delay(536);
digitalWrite(2,HIGH); // 6
delay(268);
digitalWrite(3,HIGH); // 5
delay(1072);

digitalWrite(2, LOW); // 0
delay(536);
digitalWrite(3,LOW); // 3
delay(536);
digitalWrite(3,HIGH); // 5
delay(804);

digitalWrite(3,LOW); // 3
delay(536);
digitalWrite(2, LOW); // 0
digitalWrite(2, HIGH);
digitalWrite(3, HIGH);
delay(268+1072+536);

}
