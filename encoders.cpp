#include "encoders.h"

volatile int count_r = 0;
volatile int count_l = 0;

void roue_r() {
  count_r++;
}

void roue_l() {
  count_l++;
}

void sensor_r() {
  Serial.print("RRRRRR");
}

void sensor_l() {
  Serial.print("LLLLLL");
}