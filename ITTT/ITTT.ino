#include <Servo.h>
#include <NewPing.h>

const int trigPin = 11;
const int echoPin = 10;
int distance;
int distance2;
int marginDistance = 2;
Servo headServo;
NewPing sonar(trigPin, echoPin);

void setup() {
  Serial.begin(9600);
  headServo.attach(12);
  distance = sonar.ping_cm();
  distance2 = distance;
}

void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for (int i = 15; i <= 165; i++) {
    headServo.write(i);
    delay(10);
    distance = sonar.ping_cm();
    if (distance - distance2 > marginDistance || distance2 - distance > marginDistance)
    {
      Serial.print("MOVED AT ");
      Serial.println(i);
    }
  }

  // Repeats the previous lines from 165 to 15 degrees
  for (int i = 165; i > 15; i--) {
    headServo.write(i);
    delay(10);
    distance2 = sonar.ping_cm();
    if (distance - distance2 > marginDistance || distance2 - distance > marginDistance)
    {
      Serial.print("MOVED AT ");
      Serial.println(i);
    }
  }

}
