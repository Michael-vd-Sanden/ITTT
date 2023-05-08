#include <Servo.h>

//VCC to 5V
//GND to GND
//COMP/TRIG to trigPin
//DAC_OUT to sensorPin

const int trigPin = 5;
const int sensorPin = A0;
const int ledPin = 13;
const int btnPin = 4;
const int headPin = 9;
const int shoulderPin = 10;
const int armPin = 11;

Servo headServo;
Servo shoulderServo;
Servo armServo;
int sensorValue = 0;
int distance;
int distance2;
int marginDistance = 5;


int down = 180;
int front = 90;

bool isON = true;  //turn to false if button works
int buttonState;
bool check = false;

void setup() 
{
  Serial.begin(9600);
  headServo.attach(headPin);
  shoulderServo.attach(shoulderPin);
  armServo.attach(armPin);
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);
  pinMode(trigPin, OUTPUT);                   // A low pull on pin COMP/TRIG
  digitalWrite(trigPin, HIGH);                // Set to HIGH
  delay(500);
  Serial.println("Init the sensor");
  distance = readDistance();
  distance2 = distance;

  shoulderServo.write(down);
  headServo.write(front);
  armServo.write(front);
}

void loop() 
{
  buttonState = digitalRead(btnPin);
  if(isON)
  {
      eyesOpen();
      eyesClosed();
  }
  checkBtn();
}

void checkBtn()
{
  buttonState = digitalRead(btnPin);
  if(buttonState == 1)
  {
    check = true;
  }
  if(buttonState == 0 && check == true)
  {
     check = false;
    Serial.println("ToggledON");
    // isON = !isON;
  }
  
}

void eyesOpen()
{
  digitalWrite(ledPin, HIGH);
  // rotates the servo motor from 0 to 180 degrees
  for (int i = 90; i <= 180; i++) 
  {
    checkBtn();
    if(isON == false)
    {
      return;
    }
    headServo.write(i);
    delay(20);
    if (i == 90 || i == 100 || i == 120 || i == 140 || i == 160 || i == 180)
    {
      distance = readDistance();
      Serial.print(distance);
      if (distance - distance2 > marginDistance || distance2 - distance > marginDistance)
      {
        Serial.print("MOVED AT ");
        Serial.println(i);
        //triggeredGoblin(i);
      }
    }
  }

  // Repeats the previous lines from 180 to 0 degrees
  for (int i = 180; i > 0; i--) 
  {
    checkBtn();
    if(isON == false)
    {
      return;
    }
    headServo.write(i);
    delay(20);
    if (i == 0 || i == 20 || i == 40 || i == 60 || i == 80 || i == 100 || i == 120 || i == 140 || i == 160 || i == 180)
    {
      distance2 = readDistance();
      Serial.print(distance);
      if (distance - distance2 > marginDistance || distance2 - distance > marginDistance)
      {
        Serial.print("MOVED AT ");
        Serial.println(i);
        //triggeredGoblin(i);
      }
    }
  }

  // rotates the servo motor from 180 to 90 degrees
  for (int i = 0; i <= 90; i++) 
  {
    checkBtn();
    if(isON == false)
    {
      return;
    }
    headServo.write(i);
    delay(20);
    if (i == 0 || i == 20 || i == 40 || i == 60 || i == 80 || i == 100 || i == 120 || i == 140 || i == 160 || i == 180)
    {
      distance = readDistance();
      Serial.print(distance);
      if (distance - distance2 > marginDistance || distance2 - distance > marginDistance)
      {
        Serial.print("MOVED AT ");
        Serial.println(i);
        //triggeredGoblin(i);
      }
    }
  }
}

void eyesClosed()
{
  checkBtn();
  if(isON == false)
    {
      return;
    }
  digitalWrite(ledPin, LOW);
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
  shoulderServo.write(angle);
  Serial.println(angle);
  delay(5000);
  armServo.write(down);
  //reset values for checking distance
}
