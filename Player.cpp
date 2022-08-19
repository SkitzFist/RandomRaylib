#include "Player.h"
#include "include/raylib.h"
#include "SimpleMovement.h"
#include <math.h>

//debug
#include "Log.h"

Player::Player(Vec2<float> _pos, float _radius, float _speed) : 
    m_radius(_radius), m_speed(_speed), m_dir(0.f,0.f){
    m_movement = new SimpleMovement();
    setPos(_pos);
}

Player::~Player(){
    delete m_movement;
}

void Player::handleInput(){
    onKeyDown();
    onKeyReleased();
}

void Player::update(float dt){
    Vec2<float> newPos = m_movement->move(dt, m_pos, m_dir, m_speed);
    setPos(newPos);
}

void Player::draw()const{
    DrawCircle(getPos().x, getPos().y, m_radius, GREEN);
}

void Player::onKeyDown(){
    bool right = IsKeyDown(KEY_D);
    bool left = IsKeyDown(KEY_A);
    bool up = IsKeyDown(KEY_W);
    bool down = IsKeyDown(KEY_S);
    
    if(right && !left){
        m_dir.x = 1.0f;
    }else if(left && !right){
        m_dir.x = -1.0f;
    }else if(right && left){
        if(IsKeyPressed(KEY_D)){
            m_dir.x = 1.f;
        }else if(IsKeyPressed(KEY_A)){
            m_dir.x = -1.f;
        }
    }

    if(up && !down){
        m_dir.y = -1.f;
    }else if(down && !up){
        m_dir.y = 1.f;
    }else if(down && up){
        if(IsKeyPressed(KEY_W)){
            m_dir.y = -1.f;
        }else if(IsKeyPressed(KEY_S)){
            m_dir.y = 1.f;
        }
    }
    float absX = abs(m_dir.x);
    float absY = abs(m_dir.y);
    if(absX == 1.f && absY == 1.f){
        float length = static_cast<float>(sqrt((m_dir.x * m_dir.x) + (m_dir.y * m_dir.y)));
        m_dir.x /= length;
        m_dir.y /= length;
    }
}

void Player::onKeyReleased(){
    bool rightDown = IsKeyDown(KEY_D);
    bool leftDown = IsKeyDown(KEY_A);
    bool upDown = IsKeyDown(KEY_W);
    bool downDown = IsKeyDown(KEY_S);

    if(IsKeyReleased(KEY_D) && !leftDown || IsKeyReleased(KEY_A) && !rightDown){
        m_dir.x = 0.f;
    }

    if(IsKeyReleased(KEY_W) && !downDown || IsKeyReleased(KEY_S) && !upDown){
        m_dir.y = 0.f;
    }
}

