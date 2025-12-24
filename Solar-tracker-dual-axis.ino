#include <Servo.h>

// Servos
Servo trackerLR;
Servo trackerTB;

// LDR Pins
int leftLDRpin = A1;
int bottomLDRpin = A2;
int rightLDRpin = A3;

// Sensor values
int leftLDR = 0;
int rightLDR = 0;
int bottomLDR = 0;
int topLDR = 0;

// PID Variables for Horizontal
float KpH = 0.3, KiH = 0.005, KdH = 0.1;
float integralH = 0, previousErrorH = 0;
int trackerLRPos = 90;

// PID Variables for Vertical
float KpV = 0.3, KiV = 0.005, KdV = 0.1;
float integralV = 0, previousErrorV = 0;
int trackerTBPos = 90;

// Timing
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long startMillis = 0;
int interval = 2000;
unsigned long pidInterval = 100;  // PID loop every 100 ms

void setup() {
  startMillis = millis();
  trackerLR.attach(10);
  trackerTB.attach(11);

  trackerLR.write(90); // Middle position for Left-Right
  trackerTB.write(90); // Middle position for Top-Bottom (adjustable if needed)
  delay(1000);

  // Start-up melody
  tone(2, 2637); delay(200); noTone(2); delay(50);
  tone(2, 2637); delay(300); noTone(2); delay(100);
  tone(2, 2637); delay(200); noTone(2); delay(200);
  tone(2, 2093); delay(200); noTone(2); delay(100);
  tone(2, 2637); delay(100); noTone(2); delay(300);
  tone(2, 3136); delay(200); noTone(2); delay(600);
  tone(2, 1568); delay(300); noTone(2); delay(1000);


  Serial.begin(9600);

  for (int i = 2; i <= 7; i++) pinMode(i, OUTPUT);
}

void loop() {
  currentMillis = millis();

  // Buzzer every 2 seconds
  if (currentMillis - startMillis >= interval) {
    tone(2, 1000);
    digitalWrite(6, HIGH);
    delay(100);
    noTone(2);
    digitalWrite(6, LOW);
    startMillis = currentMillis;
  }

  // Sensor Readings
  rightLDR = analogRead(rightLDRpin);
  leftLDR = analogRead(leftLDRpin);
  bottomLDR = analogRead(bottomLDRpin);
  topLDR = (rightLDR + leftLDR) / 2;

  Serial.print("Right: "); Serial.print(rightLDR);
  Serial.print(" Left: "); Serial.print(leftLDR);
  Serial.print(" Bottom: "); Serial.print(bottomLDR);
  Serial.println();

  // PID loop every pidInterval ms
  if (currentMillis - previousMillis >= pidInterval) {
    previousMillis = currentMillis;

    // ---------- Horizontal PID ----------
    float errorH = rightLDR - leftLDR;
    integralH += errorH * (pidInterval / 1000.0);
    float derivativeH = (errorH - previousErrorH) / (pidInterval / 1000.0);
    float outputH = KpH * errorH + KiH * integralH + KdH * derivativeH;
    previousErrorH = errorH;

    // Limit the output movement per cycle (example: max ±3 degrees)
    outputH = constrain(outputH, -3, 3);

    trackerLRPos += outputH;
    trackerLRPos = constrain(trackerLRPos, 10, 170);
    trackerLR.write(trackerLRPos);

    // LED Feedback
    if (errorH > 50) {
      digitalWrite(4, HIGH); // Right
      digitalWrite(5, LOW);
    } else if (errorH < -50) {
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH); // Left
    } else {
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
    }

    // ---------- Vertical PID ----------
    float errorV = topLDR - bottomLDR;
    integralV += errorV * (pidInterval / 1000.0);
    float derivativeV = (errorV - previousErrorV) / (pidInterval / 1000.0);
    float outputV = KpV * errorV + KiV * integralV + KdV * derivativeV;
    previousErrorV = errorV;

    outputV = constrain(outputV, -3, 3);

    trackerTBPos += outputV;
    trackerTBPos = constrain(trackerTBPos, 70, 179);
    trackerTB.write(trackerTBPos);

    // LED Feedback
    if (errorV > 40) {
      digitalWrite(7, HIGH); // Up
      digitalWrite(3, LOW);
    } else if (errorV < -40) {
      digitalWrite(3, HIGH); // Down
      digitalWrite(7, LOW);
    } else {
      digitalWrite(3, LOW);
      digitalWrite(7, LOW);
    }
  }
}

