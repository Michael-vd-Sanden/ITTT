#include <Servo.h>

const int trigPin = 5;
const int sensorPin = A0;
int sensorValue = 0;
int distance;
int distance2;
int marginDistance = 5;
Servo headServo;
Servo armServo;
Servo pitchServo;

int down = 0;

void setup() {
  Serial.begin(9600);
  headServo.attach(13);
  armServo.attach(12);
  pitchServo.attach(8);
  pinMode(trigPin, OUTPUT);                   // A low pull on pin COMP/TRIG
  digitalWrite(trigPin, HIGH);                // Set to HIGH
  delay(500);
  Serial.println("Init the sensor");
  distance = readDistance();
  distance2 = distance;

  armServo.write(down);
}

void loop() {
  for (int t = 0; t <= 1; t++)
  {
    eyesOpen();
  }
  eyesClosed();
}
void eyesOpen()
{
  // rotates the servo motor from 0 to 180 degrees
  for (int i = 0; i <= 180; i++) {
    headServo.write(i);
    delay(10);
    if (i == 0 || i == 20 || i == 40 || i == 60 || i == 80 || i == 100 || i == 120 || i == 140 || i == 160 || i == 180)
    {
      distance = readDistance();
      Serial.print(distance);
      if (distance - distance2 > marginDistance || distance2 - distance > marginDistance)
      {
        Serial.print("MOVED AT ");
        Serial.println(i);
        triggeredGoblin(i);
      }
    }
  }

  // Repeats the previous lines from 180 to 0 degrees
  for (int i = 180; i > 0; i--) {
    headServo.write(i);
    delay(10);
    if (i == 0 || i == 20 || i == 40 || i == 60 || i == 80 || i == 100 || i == 120 || i == 140 || i == 160 || i == 180)
    {
      distance2 = readDistance();
      Serial.print(distance);
      if (distance - distance2 > marginDistance || distance2 - distance > marginDistance)
      {
        Serial.print("MOVED AT ");
        Serial.println(i);
        triggeredGoblin(i);
      }
    }
  }
}

void eyesClosed()
{
  Serial.println("eyes closed");
  delay(3000);
}

int readDistance()
{
  //Serial.print("Distance=");
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin, HIGH);
  delay(20);
  sensorValue = analogRead(sensorPin);

  sensorValue = sensorValue * 1.1; //  (sensorValue * 5000 / 1024 ) / 4.125 = sensorValue * 1.1 , calculate the voltage value ADC collected and divide it by 4.125mV /cm.
  //Serial.print(sensorValue);
  //Serial.println("cm");
  return (sensorValue);
}

int triggeredGoblin(int angle)
{
  int up = 90;
  armServo.write(up);
  pitchServo.write(angle);
  Serial.println(angle);
  delay(5000);
  armServo.write(down);
}
