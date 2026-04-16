#include "motors.h"
#include "encoders.h"

const int left10 = 10;
const int right11 = 11;

const float distParImpulsion = 0.325;

void pulseServo(int servoPin, int pulseLg) {
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseLg);
  digitalWrite(servoPin, LOW);
}

void roulerPrecis(float distanceCm) {
  count_r = 0;
  count_l = 0;

  int cible = abs(distanceCm) / distParImpulsion;

  while (count_l < cible && count_r < cible) {
    if (count_l < cible)
      pulseServo(left10, (distanceCm > 0) ? 1700 : 1300);

    if (count_r < cible)
      pulseServo(right11, (distanceCm > 0) ? 1300 : 1700);

    delay(20);
  }
}

void tournerSurLuiPrecis(int angle) {
  count_r = 0;
  count_l = 0;

  int cible = (abs(angle) * 33.24) / (360 * distParImpulsion);

  int varL = (angle > 0) ? 1700 : 1300;
  int varR = (angle > 0) ? 1700 : 1300;

  while (count_l < cible && count_r < cible) {
    if (count_l < cible)
      pulseServo(left10, varL);

    if (count_r < cible)
      pulseServo(right11, varR);

    delay(20);
  }
}

void tournerSurRouePrecis(int angle, int roue) {
  count_r = 0;
  count_l = 0;

  int cible = (abs(angle) * 66.48) / (360 * distParImpulsion);

  while ((roue == left10 && count_r < cible) ||
         (roue == right11 && count_l < cible)) {

    if (roue == left10)
      pulseServo(right11, (angle > 0) ? 1300 : 1700);
    else if (roue == right11)
      pulseServo(left10, (angle > 0) ? 1700 : 1300);

    delay(20);
  }
}

void rouler(int len) {
  int compt = 0;
  int n = abs(len) * 10 / 3.25;

  int roue1;
  int roue2;

  if (len > 0) {
    roue1 = left10;
    roue2 = right11;
  } else {
    roue1 = right11;
    roue2 = left10;
  }

  while (compt < n) {
    pulseServo(roue1, 1700);
    pulseServo(roue2, 1300);
    compt++;
    delay(20);
  }
}

void tournerSurRoue(int angle, int roue) {
  if (angle > 0) {
    pulseServo(roue, 1300);
  } else if (angle < 0) {
    pulseServo(roue, 1700);
  }
}

void tournerSurLui(int angle) {
  int compt = 0;
  int n = (abs(angle) * 332.2) / (360 * 3.25) * 1.5;

  int var = (angle > 0) ? 1300 : 1700;

  while (compt < n) {
    pulseServo(left10, var);
    pulseServo(right11, var);
    compt++;
    delay(20);
  }
}