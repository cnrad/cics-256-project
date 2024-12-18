// matrix.h
#ifndef MATRIX_FUNCTIONS
#define MATRIX_FUNCTIONS

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

void matrixSetup();
void setCursor(int x, int y);
void clearCursor(int x, int y);
void showMatrix();
void clearMatrix();
void drawRect(int x, int y, int w, int h, uint16_t color);
void fillRect(int x, int y, int w, int h, uint16_t color);
void drawChar(int x, int y, char letter, uint16_t color);
void drawString(int x, int y, String text, uint16_t color);
void scrollText(String text, uint16_t color, int y = 5);
uint16_t color(int r, int g, int b);

#endif