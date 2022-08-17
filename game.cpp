#include "game.h"
#include "Log.h"
#include "Mouse.h"

Game::Game(): 
    m_mousePos(0.f,0.f){
    //init
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Intrusion");
    SetTargetFPS(60);
    
    //config
    Vec2<int> gridSize = {5000,5000};
    grid = new Grid(gridSize);

    Vec2<float> playerPos = {200.f,200.f};
    float playerRadius = 10.f;
    float playerSpeed = 100.f;
    m_player = new Player(playerPos, playerRadius, playerSpeed);

    //debug
}

Game::~Game(){
    delete m_player;
    delete grid;
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
    if(GetMousePosition().x > 0 && GetMousePosition().x < grid->getWorldSize().x 
    && GetMousePosition().y > 0 && GetMousePosition().y < grid->getWorldSize().y){
        m_mousePos = Mouse::getPosition();
        
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            grid->flipCell(m_mousePos);
        }
        grid->findVisibility(m_mousePos.x, m_mousePos.y, 500.f);
    }
}

void Game::update(){
    float dt = GetFrameTime();
    m_player->update(dt);
}

void Game::render(){
    ClearBackground(BLACK);
    BeginDrawing();
        grid->draw(m_mousePos);
        m_player->draw();
        DrawText(std::to_string(GetFPS()).c_str(), 50, 50, 50, RAYWHITE);
    EndDrawing();
}


