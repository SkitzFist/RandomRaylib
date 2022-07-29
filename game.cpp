#include "game.h"
#include "include/raylib.h"
#include "ray.h"
#include "Log.h"

Game::Game(){
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Intrusion");
    SetTargetFPS(60);
}

Game::~Game(){
    delete grid;
}

void Game::run(){
    grid = new Grid(Vector2i{5000,5000});
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
        mousePos = GetMousePosition();

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            grid->flipCell(mousePos);
        }
        grid->findVisibility(mousePos.x, mousePos.y, 500.f);
    }
}

void Game::update(){
    float dt = GetFrameTime();
}

void Game::render(){
    ClearBackground(BLACK);
    BeginDrawing();
        grid->draw(mousePos);
        DrawText(std::to_string(GetFPS()).c_str(), 50, 50, 50, RAYWHITE);
    EndDrawing();
}


