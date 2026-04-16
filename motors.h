#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

extern const int left10;
extern const int right11;

extern const float distParImpulsion;

void pulseServo(int servoPin, int pulseLg);

void roulerPrecis(float distanceCm);
void tournerSurLuiPrecis(int angle);
void tournerSurRouePrecis(int angle, int roue);

void rouler(int len);
void tournerSurRoue(int angle, int roue);
void tournerSurLui(int angle);

#endif