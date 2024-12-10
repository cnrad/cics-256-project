#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <stdint.h>
#include "src/matrix/matrix.h"
#include "src/cursor/cursor.h"

class GameObject
{
public:
    void onLoop();
    void onHover();
    void onClick();
    int x, y, w, h;
    uint16_t color;

    GameObject(int x, int y, int w, int h, uint16_t color);
};

class GameRect : public GameObject
{
public:
    GameRect(int x, int y, int w, int h, uint16_t color);
    void draw();
};

#endif // GAMEOBJECT_H