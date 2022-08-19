#include "game.h"
#include "Log.h"
#include "Mouse.h"

Game::Game(): 
    m_mousePos(0.f,0.f){
    //init
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Intrusion");
    SetTargetFPS(60);
    
    //config
        //Grid
    Vec2<int> gridSize = {5000,5000};
    m_grid = new Grid(gridSize);
        //Player
    Vec2<float> playerPos = {200.f,200.f};
    float playerRadius = 10.f;
    float playerSpeed = 1000.f;
    m_player = new Player(playerPos, playerRadius, playerSpeed);

    //debug
}

Game::~Game(){
    delete m_player;
    delete m_grid;
}

void Game::run(){
    while (!WindowShouldClose())
    {
        handleInput();
        update(); 
        render();
    }

    CloseWindow();
}

void Game::handleInput(){
    m_mousePos = Mouse::getPosition();
    if(m_grid->isWithinWorldSize(m_mousePos)){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            m_grid->flipCell(m_mousePos);
        }
    }

    m_player->handleInput();
}

void Game::update(){
    float dt = GetFrameTime();
    m_player->update(dt);

    if(m_grid->isWithinWorldSize(m_player->getPos())){
        m_grid->findVisibility(m_player->getPos().x, m_player->getPos().y, 500.f);
    }
}

void Game::render(){
    ClearBackground(BLACK);
    BeginDrawing();
        m_grid->draw(m_player->getPos());
        m_player->draw();
        DrawText(std::to_string(GetFPS()).c_str(), 50, 50, 50, RAYWHITE);
    EndDrawing();
}


