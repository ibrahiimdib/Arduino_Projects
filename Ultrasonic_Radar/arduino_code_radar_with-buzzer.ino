#include <Servo.h>

// Pins
const int trigPin = 2;
const int echoPin = 4;

// Servo
Servo myServo;

// Variables
int angle = 0;
bool forward = true; // servo direction
int distance;        // measured distance

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(9); // servo connected to pin 9
}

void loop() {
  // Move servo
  myServo.write(angle);

  // Measure distance
  distance = calculateDistance();

  // Send to Serial
  Serial.print(angle);
  Serial.print(",");
  Serial.println(distance);

  // Delay to make 180° sweep in ~5 seconds
  delay(28); // 28 ms per degree -> 180° in 5040 ms (~5 sec)

  // Update angle for next step
  if (forward) {
    angle += 1;
    if (angle >= 180) {
      angle = 180;
      forward = false; // reverse direction
    }
  } else {
    angle -= 1;
    if (angle <= 0) {
      angle = 0;
      forward = true;  // reverse direction
    }
  }
  if (distance< 40){
    tone(7 , 2000);
  }
  else {
    noTone(7);
    
  }
}

// Function to measure distance using HC-SR04
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int dist = duration * 0.034 / 2; // distance in cm
  return dist;
}
