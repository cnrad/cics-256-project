#include <stdint.h>
#include "src/matrix/matrix.h";
#include "src/cursor/cursor.h";

class GameObject
{
public:
    std::function<void()> onHover;
    std::function<void()> onClick;
    int x, y, w, h;
    uint16_t color;

    // member initializer list
    GameObject(int x, int y, int w, int h, uint16_t color)
        : x(x), y(y), w(w), h(h), color(color), onHover(nullptr), onClick(nullptr)
    {
    }

    void onLoop()
    {
        int cursorX = getCursorCoords()[0];
        int cursorY = getCursorCoords()[1];

        if (cursorX >= x && cursorX <= x + w && cursorY >= y && cursorY <= y + h)
        {
            onHover();
            if (buttonPressed())
            {
                onClick();
            }
        }
    }
};

class GameRect : public GameObject
{
public:
    GameRect(int x, int y, int w, int h, uint16_t color) : GameObject(x, y, w, h, color) {}
    void draw()
    {
        drawRect(x, y, w, h, color);
    }
};
