#include <stdlib.h>
#include <iostream>
#include <random>
#include "src/Matrix/Matrix.h"
#include "src/Cursor/Cursor.h"
#include <string>
#include <sstream>
#include "src/Games/Game.h"

int sequence[25];        // The sequence of the game
int score;               // The score of the player
int playerSequenceIndex; // The index of the player's sequence repetition
bool playerTurn = false; // Player turn? or nahh

bool isSimonInitialized = false;

/*
 * int random (int a, int b)
 * @returns a random integer between a and b, inclusive
 */
int random(int a, int b)
{
    int random_number = (rand() % (b - a + 1)) + a; // Returns 0-3,
    return random_number;
}

// Returns the quadrant of the screen the cursor is in, 0 <= x <= 32, 0 <= y <= 16
int getSection(int x, int y)
{
    if (x < 16 && y < 8) // Upper left
    {
        return 0;
    }
    else if (x >= 16 && y < 8) // Upper right
    {
        return 1;
    }
    else if (x < 16 && y >= 8) // Lower left
    {
        return 2;
    }
    else if (x >= 16 && y >= 8) // Lower right
    {
        return 3;
    }
    return -1;
};

void showSection(int section)
{
    if (section == 0)
    {
        fillRect(0, 0, 16, 8, color(255, 0, 0));
    }
    else if (section == 1)
    {
        fillRect(16, 0, 16, 8, color(0, 255, 0));
    }
    else if (section == 2)
    {
        fillRect(0, 8, 16, 8, color(0, 0, 255));
    }
    else if (section == 3)
    {
        fillRect(16, 8, 16, 8, color(255, 255, 0));
    }
}

void clearSection(int section)
{
    if (section == 0)
    {
        fillRect(0, 0, 16, 8, color(0, 0, 0));
    }
    else if (section == 1)
    {
        fillRect(16, 0, 16, 8, color(0, 0, 0));
    }
    else if (section == 2)
    {
        fillRect(0, 8, 16, 8, color(0, 0, 0));
    }
    else if (section == 3)
    {
        fillRect(16, 8, 16, 8, color(0, 0, 0));
    }
}

void SimonSetup()
{
    // Generate sequence and set variables
    srand(millis());

    score = 0;
    playerTurn = false;
    playerSequenceIndex = 0;

    for (int i = 0; i < 25; i++)
    {
        sequence[i] = random(0, 3);
    }
}

void SimonLoop()
{
    if (!isSimonInitialized)
    {
        SimonSetup();
        isSimonInitialized = true;
    }

    if (!playerTurn)
    {
        // In this case, player cursor doesn't matter since we are showing them the sequence, so we can interrupt the main program flow
        for (int i = 0; i < score + 1; i++)
        {
            showSection(sequence[i]);
            showMatrix();
            delay(400);
            clearSection(sequence[i]);
            showMatrix();
            delay(100);
        }

        playerTurn = true;
        playerSequenceIndex = 0;
    }
    else
    {
        // In this case, player cursor does matter since we are waiting for the player to input the sequence, so we can't interrupt the main program flow
        if (buttonPressed())
        {
            int *coords = getCursorCoords();
            int section = getSection(coords[0], coords[1]);

            showSection(section); // Breaking out of the event loop both to show the color, and as a natural debounce
            showMatrix();
            delay(150);
            clearSection(section);
            showMatrix();

            // If it's correct
            if (section == sequence[playerSequenceIndex])
            {

                playerSequenceIndex++;
                if (playerSequenceIndex == score + 1)
                {
                    // Player completed the sequence correctly
                    score++;
                    playerTurn = false;
                    delay(500); // A little time in between
                }
            }
            else
            {
                playerTurn = false;

                drawString(2, 1, "Score: ", color(255, 255, 255));
                drawString(2, 9, String(score), color(255, 255, 255));

                showMatrix();
                delay(2000);
                isSimonInitialized = false;
                game = MENU; // Send back to main menu
            }
        }
    }
}
