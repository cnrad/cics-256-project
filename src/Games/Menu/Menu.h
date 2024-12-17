#ifndef MENU_H
#define MENU_H

#include "src/Matrix/Matrix.h"
#include "src/Cursor/Cursor.h"

struct ButtonBounds
{
    int x1;
    int y1;
    int x2;
    int y2;
};

extern ButtonBounds SimonBounds, DrawBounds;

bool isWithinBounds(int cursorX, int cursorY, ButtonBounds *bounds);
void fillBounds(ButtonBounds *bounds, uint16_t color);
void MenuSetup();
void MenuLoop();

#endif // MENU_H