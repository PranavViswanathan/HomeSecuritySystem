// file name on system : hcsr.ino

#include <SoftwareSerial.h>
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define buzzer 8
SoftwareSerial espSerial(5, 6);
// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
String str;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
    pinMode(buzzer, OUTPUT);
  Serial.begin(115200); // // Serial Communication is starting with 9600 of baudrate speed
  espSerial.begin(115200);
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if(distance < 10) {
    digitalWrite(buzzer, HIGH);
    delay(1000);
  }
  digitalWrite(buzzer, LOW);
  espSerial.println(distance);
  delay(5000);
}
