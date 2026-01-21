const byte triger = 4;
const byte echo = 3;

float distanceMesured = 0;          // FIX: initialize
const float distancetotal = 17.9;     // container height (cm)

float distance = 0;                // FIX: calculated in loop

const float diameter = 11.5;
const float rayon = diameter / 2;

const float volumetotal = 3.14 * pow(rayon, 2) * distancetotal;

const byte buzzer = 11;
const byte red = 8;
const byte yellow = 12;

void setup() {
  Serial.begin(9600);
  pinMode(triger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
}

void loop() {

  // Trigger ultrasonic sensor (FIXED pulse)
  digitalWrite(triger, LOW);
  delayMicroseconds(2);
  digitalWrite(triger, HIGH);
  delayMicroseconds(10);
  digitalWrite(triger, LOW);

  long duration = pulseIn(echo, HIGH, 25000);

  // Measured distance (air)
  distanceMesured = duration * 0.017;

  // Limit distance
  if (distanceMesured > distancetotal) distanceMesured = distancetotal;
  if (distanceMesured < 0) distanceMesured = 0;

  // FIX: liquid height
  distance = distancetotal - distanceMesured;

  float volumeCM = 3.14 * pow(rayon, 2) * distance;
  float volumeLiters = volumeCM / 1000.0;

  Serial.print(volumeLiters);
  Serial.println(" liters");

  // Reset outputs (FIX)
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  noTone(buzzer);

  if (volumeCM >= volumetotal * 0.8) {
    digitalWrite(red, HIGH);
    tone(buzzer, 2000);
  }
  else if (volumeCM <=volumetotal *0.79 ) {
    digitalWrite(yellow, HIGH);
  }

  delay(300);
}
