#define trigPin 7
#define echoPin 8
#define buzzerPin 5


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(buzzerPin, OUTPUT);
}


void loop() {
digitalWrite(buzzerPin, LOW);
  // put your main code here, to run repeatedly:
int i = 0;
float duration;
float distance = 0.00;


  digitalWrite(trigPin, HIGH);
  delayMicroseconds(50);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = ("%.2f", duration/2) /29,1 ;
  



if (distance < 30.00 && distance >0) {
    digitalWrite(buzzerPin, HIGH);
    delay(500);
}

Serial.print (distance);
Serial.println (" cm");
delay(10);


}
