#pragma once

#include "grid.h"

class Game {
public:
    Game();
    ~Game();
    void run();
private:
    static constexpr int WINDOW_WIDTH = 1920;
    static constexpr int WINDOW_HEIGHT = 1080;
    Grid* grid;

    Vector2 mousePos;

    void handleInput();
    void update();
    void render();
};
