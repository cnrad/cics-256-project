#ifndef SIMON_H
#define SIMON_H

#include <stdlib.h>
#include <iostream>
#include <random>
#include "src/Matrix/matrix.h"
#include "src/Cursor/cursor.h"

extern int sequence[25];
extern int score;
extern int playerSequenceIndex;
extern bool playerTurn;

int random(int a, int b);
void SimonSetup();
void SimonLoop();
int getSection(int x, int y);
void showSection(int section);
void clearSection(int section);

#endif