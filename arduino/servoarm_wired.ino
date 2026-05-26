/*
 * ============================================================
 *  Flex Sensor Controlled Robotic Hand — Wired Version
 * ============================================================
 *  Description : Reads 5 flex sensors on analog pins A1–A5
 *                and drives 5 servo motors on pins D2–D6
 *                to mirror finger gestures in real-time.
 *
 *  Hardware    : Arduino UNO, 5x Flex Sensors, 5x SG90 Servos,
 *                5x 10kΩ resistors (voltage divider)
 *
 *  Author      : (Your Name)
 *  Version     : 1.0
 *  License     : MIT
 * ============================================================
 *
 *  CALIBRATION:
 *    1. Open Serial Monitor at 9600 baud
 *    2. Note analog readings for each finger at IDLE and CLOSED
 *    3. Update the calibration constants below accordingly
 *
 *  Default calibration (adjust for your sensors):
 *    Flex1  IDLE=840  CLOSED=900
 *    Flex2  IDLE=879  CLOSED=882
 *    Flex3  IDLE=828  CLOSED=824
 *    Flex4  IDLE=874  CLOSED=878
 *    Flex5  IDLE=855  CLOSED=851
 * ============================================================
 */

#include <Servo.h>

// ----- Servo objects -----
Servo servo1;  // Index finger
Servo servo2;  // Middle finger
Servo servo3;  // Ring finger
Servo servo4;  // Pinky finger
Servo servo5;  // Thumb

// ----- Analog input pins -----
const int FLEX1_PIN = A1;
const int FLEX2_PIN = A2;
const int FLEX3_PIN = A3;
const int FLEX4_PIN = A4;
const int FLEX5_PIN = A5;

// ----- Servo output pins -----
const int SERVO1_PIN = 2;
const int SERVO2_PIN = 3;
const int SERVO3_PIN = 4;
const int SERVO4_PIN = 5;
const int SERVO5_PIN = 6;

// ----- Calibration values -----
const int FLEX1_IDLE = 840, FLEX1_CLOSED = 900;
const int FLEX2_IDLE = 879, FLEX2_CLOSED = 882;
const int FLEX3_IDLE = 828, FLEX3_CLOSED = 824;
const int FLEX4_IDLE = 874, FLEX4_CLOSED = 878;
const int FLEX5_IDLE = 855, FLEX5_CLOSED = 851;

const int LOOP_DELAY = 50;

// ============================================================
void setup() {
  Serial.begin(9600);
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  servo4.attach(SERVO4_PIN);
  servo5.attach(SERVO5_PIN);
  Serial.println("Robotic Hand — Ready. Flex readings: F1--F2--F3--F4--F5");
}

// Helper: map flex sensor reading to servo angle
int flexToServo(int pin, int idleVal, int closedVal, bool invertDir) {
  int rawVal = analogRead(pin);
  int angle;
  if (invertDir) {
    angle = map(rawVal, idleVal, closedVal, 180, 0);
  } else {
    angle = map(rawVal, idleVal, closedVal, 0, 180);
  }
  return constrain(angle, 0, 180);
}

// ============================================================
void loop() {
  servo1.write(flexToServo(FLEX1_PIN, FLEX1_IDLE, FLEX1_CLOSED, true));
  servo2.write(flexToServo(FLEX2_PIN, FLEX2_IDLE, FLEX2_CLOSED, false));
  servo3.write(flexToServo(FLEX3_PIN, FLEX3_IDLE, FLEX3_CLOSED, true));
  servo4.write(flexToServo(FLEX4_PIN, FLEX4_IDLE, FLEX4_CLOSED, false));
  servo5.write(flexToServo(FLEX5_PIN, FLEX5_IDLE, FLEX5_CLOSED, true));

  // Serial output for calibration / debugging
  Serial.print(analogRead(FLEX1_PIN)); Serial.print("--");
  Serial.print(analogRead(FLEX2_PIN)); Serial.print("--");
  Serial.print(analogRead(FLEX3_PIN)); Serial.print("--");
  Serial.print(analogRead(FLEX4_PIN)); Serial.print("--");
  Serial.print(analogRead(FLEX5_PIN)); Serial.println("--");

  delay(LOOP_DELAY);
}
