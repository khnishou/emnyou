#include <stdlib.h>

int left10 = 10;
int right11 = 11;

int sensorLeftPin = 5;
int sensorRightPin = 6;

volatile int count_r = 0;
volatile int count_l = 0;

const float distParImpulsion = 0.325;

/* ---------------- WHEEL COUNTERS ---------------- */

void roue_r() {
  count_r++;
}

void roue_l() {
  count_l++;
}

/* ---------------- MOTOR ---------------- */

void pulseServo(int servoPin, int pulseLg) {
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseLg);
  digitalWrite(servoPin, LOW);
}

/* ---------------- SETUP ---------------- */

void setup() {
  pinMode(left10, OUTPUT);
  pinMode(right11, OUTPUT);

  pinMode(sensorLeftPin, INPUT_PULLUP);
  pinMode(sensorRightPin, INPUT_PULLUP);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(2), roue_r, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), roue_l, CHANGE);

  Serial.begin(9600);

  randomSeed(analogRead(A0));
}

/* ---------------- SENSOR CHECK ---------------- */

bool wallLeft() {
  return digitalRead(sensorLeftPin) == LOW;
}

bool wallRight() {
  return digitalRead(sensorRightPin) == LOW;
}

/* ---------------- STOP ---------------- */

void stopRobot() {
  digitalWrite(left10, LOW);
  digitalWrite(right11, LOW);
}

/* ---------------- ESCAPE BEHAVIOR ---------------- */

void reculerPetit() {
  for (int i = 0; i < 40; i++) {
    pulseServo(left10, 1300);
    pulseServo(right11, 1700);
    delay(15);
  }
}

void tournerRandom(int direction) {
  int angle = random(30, 120);

  int varL, varR;

  if (direction == 1) {
    // turn LEFT
    varL = 1300;
    varR = 1300;
  } else {
    // turn RIGHT
    varL = 1700;
    varR = 1700;
  }

  int steps = angle * 2;

  for (int i = 0; i < steps; i++) {
    pulseServo(left10, varL);
    pulseServo(right11, varR);
    delay(15);
  }
}

/* ---------------- MAIN MOVE ---------------- */

void roulerPrecis(float distanceCm) {
  count_r = 0;
  count_l = 0;

  int cible = abs(distanceCm) / distParImpulsion;

  while (count_l < cible && count_r < cible) {

    /* SENSOR CHECK */
    if (wallLeft()) {
      stopRobot();
      Serial.println("LEFT WALL");

      reculerPetit();
      tournerRandom(1); // turn RIGHT
      return;
    }

    if (wallRight()) {
      stopRobot();
      Serial.println("RIGHT WALL");

      reculerPetit();
      tournerRandom(0); // turn LEFT
      return;
    }

    /* MOTOR CONTROL */
    if (count_l < cible)
      pulseServo(left10, (distanceCm > 0) ? 1700 : 1300);

    if (count_r < cible)
      pulseServo(right11, (distanceCm > 0) ? 1300 : 1700);

    delay(20);
  }
}

/* ---------------- LOOP ---------------- */

void loop() {
  roulerPrecis(30);
  delay(2000);
}