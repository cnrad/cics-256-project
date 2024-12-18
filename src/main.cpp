// #include "gyro/gyro.h"
#include "Matrix/Matrix.h"
#include "Cursor/Cursor.h"
#include "Games/Simon/Simon.h"
#include "Games/Menu/Menu.h"
#include "Games/Game.h"
#include "Games/AimTrainer/AimTrainer.h"
#include "Games/Draw/Draw.h"
#include <stdlib.h>

Game game = MENU;

void setup()
{
    Serial.begin(115200);

    matrixSetup();
    cameraSetup();

    // scrollText("abcdefghijklmnopqrstuvwxyz1234567890:", color(255, 255, 255)); // Font testing
}

void loop()
{
    clearMatrix(); // Reset matrix state so we can redraw it from scratch every time

    // Determine which event loop to run
    if (game == SIMON)
    {
        SimonLoop();
    }
    else if (game == AIM_TRAINER)
    {
        AimTrainerLoop();
    }
    else if (game == DRAW)
    {
        DrawLoop();
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