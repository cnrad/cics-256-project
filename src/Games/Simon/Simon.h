#ifndef SIMON_H
#define SIMON_H

#include <stdlib.h>
#include <iostream>
#include <random>
#include "src/Matrix/Matrix.h"
#include "src/Cursor/Cursor.h"

int random(int a, int b);
void SimonSetup();
void SimonLoop();
int getSection(int x, int y);
void showSection(int section);
void clearSection(int section);

#endif