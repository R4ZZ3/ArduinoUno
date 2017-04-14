/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 8;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
pinMode(12, OUTPUT);
pinMode(11, OUTPUT);
pinMode(10, OUTPUT);
pinMode(9, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial.println(buttonState);
  delay(1000);        // delay in between reads for stability
    if (buttonState == 1){
      Serial.println("loopissa");
    digitalWrite(12, HIGH);
    delay(500);
    digitalWrite(11, HIGH);
    delay(500);
    digitalWrite(10, HIGH);
    delay(500);
    digitalWrite(9, HIGH);
    delay(1000);
    digitalWrite(9, LOW);
    delay(500);
    digitalWrite(10, LOW);
    delay(500);
    digitalWrite(11, LOW);
    delay(500);
    digitalWrite(12,LOW);
    delay(1000);
  }


}


