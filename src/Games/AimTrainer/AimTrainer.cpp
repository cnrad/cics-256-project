#include <stdlib.h>
#include <iostream>
#include <random>
#include "src/Matrix/Matrix.h"
#include "src/Cursor/Cursor.h"
#include "src/Games/Game.h"
#include <string>
#include <sstream>

int aimScore; // The score of the player
int timer;
int x;
int y;
static const int totalTime = 16000;

bool isAimTrainerInitialized = false;

int generateXCoord()
{
    return (rand() % 24) + 4;
}
int generateYCoord()
{
    return (rand() % 12) + 4;
}
void drawTarget(int x, int y)
{
    drawTarget(x, y, color(255, 255, 255));
}
void clearTarget(int x, int y)
{
    drawTarget(x, y, color(0, 0, 0));
}

void drawProgressBar(int timeLeft, int totalTime)
{
    int barWidth = map(timeLeft, 0, totalTime, 0, 32);
    fillRect(0, 0, 32, 1, color(0, 0, 0));         // Clear previous bar
    fillRect(0, 0, barWidth, 1, color(0, 255, 0)); // Draw new bar
}

void AimTrainerSetup()
{
    // Generate sequence and set variables
    srand(millis());

    aimScore = 0;
    timer = totalTime;
    x = generateXCoord();
    y = generateYCoord();
}

void AimTrainerLoop()
{
    static unsigned long lastTime = millis();
    static unsigned long targetLastTime = millis();
    static bool targetVisible = true;

    if (!isAimTrainerInitialized)
    {
        AimTrainerSetup();
        isAimTrainerInitialized = true;
    }
    else
    {
        unsigned long currentTime = millis();

        if (buttonPressed())
        {
            int *coords = getCursorCoords();

            if (targetVisible && coords[0] >= x - 1 && coords[0] <= x + 1 && coords[1] >= y - 1 && coords[1] <= y + 1)
            {

                clearTarget(x, y);
                targetVisible = false;
                targetLastTime = currentTime;
                x = generateXCoord();
                y = generateYCoord();
                drawTarget(x, y);
                targetVisible = true;
                targetLastTime = currentTime;
                aimScore++;
            }
            else
            {
                aimScore--;
            }
            delay(100);
        }

        if (timer > 0)
        {
            // Every second
            if (currentTime - lastTime >= 1000)
            {
                timer -= 1000;
                lastTime = currentTime;
            }

            if (targetVisible)
            {
                drawTarget(x, y);
            }

            drawProgressBar(timer, totalTime);

            showMatrix();
        }
        else
        {
            drawString(2, 1, "Score:", color(255, 255, 255));
            drawString(2, 9, String(aimScore), color(255, 255, 255));
            showMatrix();

            delay(2000);
            isAimTrainerInitialized = false;

            game = MENU;
        }
    }
}
