#ifndef ENCODERS_H
#define ENCODERS_H

#include <Arduino.h>

extern volatile int count_r;
extern volatile int count_l;

void roue_r();
void roue_l();

void sensor_r();
void sensor_l();

#endif