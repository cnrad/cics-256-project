#ifndef DRAW_H
#define DRAW_H

#include <stdlib.h>
#include <iostream>
#include <random>
#include "src/Matrix/Matrix.h"
#include "src/Cursor/Cursor.h"

void updateColorTransition();
int getClickCount(unsigned long currentTime);
void drawRectMatrix(int x, int y, int w, int h, uint16_t color);
void DrawSetup();
void DrawLoop();

#endif