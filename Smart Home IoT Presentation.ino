#include <Servo.h>



Servo doorServo;

// Pin Definitions
const int pirPin = 2;
const int tempPin = A0;
const int ledPin = 13;
const int buzzerPin = 8;
const int motorPin = 5;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  doorServo.attach(9);
  doorServo.write(0);

  Serial.begin(9600);
}

void loop() {

  // -------- Motion Detection --------
  int motion = digitalRead(pirPin);

  if (motion == HIGH) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    doorServo.write(90);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    doorServo.write(0);
  }

  // -------- Temperature --------
  int sensorValue = analogRead(tempPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float tempC = (voltage - 0.5) * 100;

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" C");

  // -------- Fan Control --------
  if (tempC > 28) {
    analogWrite(motorPin, 200);   // Fan ON
  } else {
    analogWrite(motorPin, 0);     // Fan OFF
  }

  delay(500);
}