#ifndef CAMERA_H
#define CAMERA_H

#include <Wire.h>
#include <Arduino.h>

extern int IRsensorAddress;
extern int slaveAddress;
extern int ledPin;
extern boolean ledState;
extern byte data_buf[16];
extern int Ix[4];
extern int Iy[4];
extern int s;

void Write_2bytes(byte d1, byte d2);
void cameraSetup();
void cameraLoop();

#endif // CAMERA_H
