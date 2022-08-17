#pragma once

#include "grid.h"
#include "Player.h"
#include "Vec2.h"

class Game {
public:
    Game();
    ~Game();
    void run();
private:
    static constexpr int WINDOW_WIDTH = 1920;
    static constexpr int WINDOW_HEIGHT = 1080;
    Grid* grid;
    Player* m_player;

    Vec2<float> m_mousePos;

    void handleInput();
    void update();
    void render();
};
