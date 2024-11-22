// matrix.h
#ifndef MATRIX_FUNCTIONS
#define MATRIX_FUNCTIONS

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

void matrixSetup();
void matrixLoop();
void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait);
void theaterChase(uint32_t c, uint8_t wait);
uint32_t Wheel(byte WheelPos);

#endif