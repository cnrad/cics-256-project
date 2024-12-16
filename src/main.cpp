// #include "gyro/gyro.h"
#include "Matrix/Matrix.h"
#include "Cursor/Cursor.h"
#include "Games/Simon/Simon.h"
#include "Games/Menu/Menu.h"
#include <stdlib.h>

enum Game
{
    MENU,
    SIMON,
};

static enum Game game = MENU;

void setup()
{
    Serial.begin(115200);

    matrixSetup();
    cameraSetup();
}

void loop()
{
    clearMatrix(); // Reset matrix state so we can redraw it from scratch every time

    // Determine which event loop to run
    if (game == SIMON)
    {
        SimonLoop();
    }
    else
    {
        MenuLoop();
    }

    cameraLoop(); // For cursor positioning and display
    showMatrix(); // Shows the matrix lmao
    delay(10);    // This runs every time and determines the game speed!!!
}

// TODO: spamming the button (3 times within a short time frame) should take them to the menu - aka setting game to MENU