#include "src/Matrix/Matrix.h"
#include "src/Cursor/Cursor.h"

bool isInitialized = false;

struct ButtonBounds
{
    int x1;
    int y1;
    int x2;
    int y2;
} SimonBounds, DrawBounds;

// I don't know if we really need to set anything up for the menu
void MenuSetup()
{
    // we should put a cool little loader here tbh
    // also what if one of the games was literally just a 'screensaver' cause matrices can look cool and gradienty
}

void MenuLoop()
{
    if (!isInitialized)
    {
        MenuSetup();
        isInitialized = true;
    }

    int cursorX = getCursorCoords()[0];
    int cursorY = getCursorCoords()[1];

    SimonBounds.x1 = 2;
    SimonBounds.x2 = 10;
    SimonBounds.y1 = 10;
    SimonBounds.y2 = 15;

    DrawBounds.x1 = 12;
    DrawBounds.x2 = 20;
    DrawBounds.y1 = 10;
    DrawBounds.y2 = 15;

    // Is the cursor over the Simon button?
    if (isWithinBounds(cursorX, cursorY, &SimonBounds))
    {
        fillBounds(&SimonBounds, color(255, 255, 255));
        drawString(2, 2, "Simon", color(255, 0, 0));
    }
    else
    {
        fillBounds(&SimonBounds, color(255, 0, 0));
    }

    // Is the cursor over the Draw mode button?
    if (isWithinBounds(cursorX, cursorY, &DrawBounds))
    {
        fillBounds(&DrawBounds, color(255, 255, 255));
        drawString(2, 2, "Draw Mode", color(0, 255, 0));
    }
    else
    {
        fillBounds(&DrawBounds, color(0, 255, 0));
    }
}

bool isWithinBounds(int cursorX, int cursorY, ButtonBounds *bounds)
{
    return cursorX < bounds->x2 && cursorX > bounds->x1 && cursorY < bounds->y2 && cursorY > bounds->y1;
}

void fillBounds(ButtonBounds *bounds, uint16_t color)
{
    fillRect(bounds->x1, bounds->y1, bounds->x2 - bounds->x1, bounds->y2 - bounds->y1, color);
}
