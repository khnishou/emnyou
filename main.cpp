#include <Arduino.h>
#include "motors.h"
#include "encoders.h"

void setup() {
  pinMode(left10, OUTPUT);
  pinMode(right11, OUTPUT);

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(2), roue_r, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), roue_l, CHANGE);
}

void loop() {
  roulerPrecis(30);
  delay(5000);
}