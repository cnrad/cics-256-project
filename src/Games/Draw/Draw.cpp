#include <stdlib.h>
#include <iostream>
#include <random>
#include "src/Matrix/Matrix.h"
#include "src/Cursor/Cursor.h"
#include <string>
#include <sstream>
#include "src/Games/Game.h"

// We need to keep a 'copy' of the matrix, because we clear it every frame in the main loop
uint16_t m[32][16];

bool isDrawInitialized = false;
int lastDrawTime = 0;

bool buttonLastPressed = false;
unsigned long lastClickTime = 0;
int clickCount = 0;

enum TransitionState
{
    RED_TO_YELLOW,
    YELLOW_TO_GREEN,
    GREEN_TO_CYAN,
    CYAN_TO_BLUE,
    BLUE_TO_MAGENTA,
    MAGENTA_TO_RED
};

int colorR = 255;
int colorG = 0;
int colorB = 0;
TransitionState currentState = RED_TO_YELLOW;

void updateColorTransition()
{
    switch (currentState)
    {
    case RED_TO_YELLOW:
        if (colorG < 255)
        {
            colorG += 3;
        }
        else
        {
            currentState = YELLOW_TO_GREEN;
        }
        break;

    case YELLOW_TO_GREEN:
        if (colorR > 0)
        {
            colorR -= 3;
        }
        else
        {
            currentState = GREEN_TO_CYAN;
        }
        break;

    case GREEN_TO_CYAN:
        if (colorB < 255)
        {
            colorB += 3;
        }
        else
        {
            currentState = CYAN_TO_BLUE;
        }
        break;

    case CYAN_TO_BLUE:
        if (colorG > 0)
        {
            colorG -= 3;
        }
        else
        {
            currentState = BLUE_TO_MAGENTA;
        }
        break;

    case BLUE_TO_MAGENTA:
        if (colorR < 255)
        {
            colorR += 3;
        }
        else
        {
            currentState = MAGENTA_TO_RED;
        }
        break;

    case MAGENTA_TO_RED:
        if (colorB > 0)
        {
            colorB -= 3;
        }
        else
        {
            currentState = RED_TO_YELLOW;
        }
        break;
    }
}

int getClickCount(unsigned long currentTime)
{
    // Check if the button is pressed
    if (buttonPressed() && !buttonLastPressed)
    {
        buttonLastPressed = true;
        clickCount++;
        lastClickTime = currentTime;
    }
    else if (!buttonPressed() && buttonLastPressed)
    {
        buttonLastPressed = false;
    }

    // Reset click count if more than 200 milliseconds
    if (currentTime - lastClickTime > 200)
    {
        clickCount = 0;
    }

    // Return true if more than 2 clicks detected within the last second
    return clickCount;
}

void drawRectMatrix(int x, int y, int w, int h, uint16_t color)
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            m[x + i][y + j] = color;
        }
    }
}

void DrawSetup()
{
    lastDrawTime = millis();
    drawRectMatrix(0, 0, 32, 16, color(0, 0, 0)); // Clear the matrix
}

void DrawLoop()
{
    if (!isDrawInitialized)
    {
        DrawSetup();
        isDrawInitialized = true;
    }

    unsigned long currentTime = millis();
    updateColorTransition(); // Runs every time

    // Triple-click to leave
    if (getClickCount(currentTime) >= 3)
    {
        game = MENU;
    }

    // Double-click to clear
    if (getClickCount(currentTime) >= 2)
    {
        // Clear the matrix
        for (int i = 0; i < 32; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                m[i][j] = color(0, 0, 0);
            }
        }
    }

    // If it's pressed, start drawing
    if (buttonPressed())
    {
        drawRectMatrix(getCursorCoords()[0], getCursorCoords()[1], 1, 1, color(colorR, colorG, colorB));
    }

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            drawRect(i, j, 1, 1, m[i][j]);
        }
    }
}