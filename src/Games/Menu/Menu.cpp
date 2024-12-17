#include "src/Matrix/Matrix.h"
#include "src/Cursor/Cursor.h"
#include "src/Games/Game.h"

bool isMenuInitialized = false;

struct ButtonBounds
{
    int x1;
    int y1;
    int x2;
    int y2;
} SimonBounds, DrawBounds, AimTrainerBounds;

bool isWithinBounds(int cursorX, int cursorY, ButtonBounds *bounds)
{
    return cursorX < bounds->x2 && cursorX >= bounds->x1 && cursorY < bounds->y2 && cursorY >= bounds->y1;
}

void fillBounds(ButtonBounds *bounds, uint16_t color)
{
    fillRect(bounds->x1, bounds->y1, bounds->x2 - bounds->x1, bounds->y2 - bounds->y1, color);
}

// I don't know if we really need to set anything up for the menu
void MenuSetup()
{
    // we should put a cool little loader here tbh
    // also what if one of the games was literally just a 'screensaver' cause matrices can look cool and gradienty
}

void MenuLoop()
{
    if (!isMenuInitialized)
    {
        MenuSetup();
        isMenuInitialized = true;
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

    AimTrainerBounds.x1 = 22;
    AimTrainerBounds.x2 = 30;
    AimTrainerBounds.y1 = 10;
    AimTrainerBounds.y2 = 15;

    int SimonHovered = isWithinBounds(cursorX, cursorY, &SimonBounds);
    int DrawHovered = isWithinBounds(cursorX, cursorY, &DrawBounds);
    int AimTrainerHovered = isWithinBounds(cursorX, cursorY, &AimTrainerBounds);

    if (!SimonHovered && !DrawHovered && !AimTrainerHovered)
    {
        drawString(8, 2, "Vii", color(255, 255, 255));
    }

    // Is the cursor over the Simon button?
    if (SimonHovered)
    {
        fillBounds(&SimonBounds, color(255, 255, 255));
        drawString(2, 2, "Simon", color(255, 0, 255));

        if (buttonPressed())
        {
            game = SIMON;
        }
    }
    else
    {
        fillBounds(&SimonBounds, color(255, 0, 255));
    }

    // Is the cursor over the Draw mode button?
    if (DrawHovered)
    {
        fillBounds(&DrawBounds, color(255, 255, 255));
        drawString(2, 2, "Draw Mode", color(0, 255, 0));
    }
    else
    {
        fillBounds(&DrawBounds, color(0, 255, 0));
    }

    // Is the cursor over the Aim button?
    if (AimTrainerHovered)
    {
        fillBounds(&AimTrainerBounds, color(255, 255, 255));
        drawString(2, 2, "Aim", color(255, 255, 0));

        if (buttonPressed())
        {
            game = AIM_TRAINER;
        }
    }
    else
    {
        fillBounds(&AimTrainerBounds, color(255, 255, 0));
    }
}
