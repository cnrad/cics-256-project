#ifndef CURSOR_H
#define CURSOR_H

#include <Wire.h>
#include <Arduino.h>

void Write_2bytes(byte d1, byte d2);
void cameraSetup();
void cameraLoop();
int *getCursorCoords();
boolean buttonPressed();

#endif
