#include "gyro/gyro.h"
#include "matrix/matrix.h"
#include "cursor/cursor.h"
#include "game/GameObject/GameObject.h"
#include "game/Games/Simon/Simon.h"
#include <stdlib.h>

void setup()
{
    Serial.begin(115200);

    matrixSetup();
    cameraSetup();
}

void loop()
{
    // Reset matrix state every loop so we can redraw it from scratch
    clearMatrix();

    // GameManager gameManager;
    // gameManager.run();

    // games[gameIndex].update()

    SimonLoop();

    cameraLoop();

    showMatrix();
    delay(10); // This runs every time and determines the game speed!!!
}