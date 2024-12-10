#include "Game.h"
#include "src/game/GameObject/GameObject.h"

class MenuGame : public Game
{
    GameObject **gameObjects;

    MenuGame()
    {
        gameObjects = new GameObject *[10];
        for (int i = 0; i < 10; ++i)
        {
            gameObjects[i] = nullptr;
        }

        gameObjects[0] = new GameRect(0, 0, 32, 32, color(255, 0, 0));
    }

    void start() override
    {
        gameObjects[0] = new GameRect(0, 0, 32, 32, color(255, 0, 0));
    }

    void update() override
    {
        for (int i = 0; i < 10; ++i)
        {
            if (gameObjects[i] != nullptr)
            {
                gameObjects[i]->onLoop();
            }
        }
    }

    ~MenuGame()
    {
        for (int i = 0; i < 10; ++i)
        {
            delete gameObjects[i];
        }
        delete[] gameObjects;
    }
};