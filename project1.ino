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
}

/* ---------------- LOOP ---------------- */

void loop() {
  roulerPrecis(30);
  delay(2000);
}

/* ---------------- MOTOR ---------------- */

void pulseServo(int servoPin, int pulseLg) {
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseLg);
  digitalWrite(servoPin, LOW);
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

/* ---------------- MOVE ---------------- */

void roulerPrecis(float distanceCm) {
  count_r = 0;
  count_l = 0;

  int cible = abs(distanceCm) / distParImpulsion;

  while (count_l < cible && count_r < cible) {

    if (wallLeft() || wallRight()) {
      stopRobot();

      if (wallLeft()) {
        Serial.println("LEFT WALL DETECTED");
      }

      if (wallRight()) {
        Serial.println("RIGHT WALL DETECTED");
      }

      return;
    }

    if (count_l < cible)
      pulseServo(left10, (distanceCm > 0) ? 1700 : 1300);

    if (count_r < cible)
      pulseServo(right11, (distanceCm > 0) ? 1300 : 1700);

    delay(20);
  }
}