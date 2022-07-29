#include "Player.h"
#include "include/raylib.h"
#include "SimpleMovement.h"

Player::Player(Vec2<float> _pos, float _radius, float _speed) : 
    m_radius(_radius), m_speed(_speed), m_dir(0.f,0.f){
    m_movement = new SimpleMovement();
}

Player::~Player(){
    delete m_movement;
}

void Player::handleInput(){
    onKeyDown();
    onKeyUp();
}

void Player::update(float dt){
    //Vec2<float> newPos = m_movement->move(dt, m_pos, m_dir, m_speed);
}

void Player::draw()const{
    int xCenter = static_cast<int>(m_pos.x / m_radius);
    int yCenter = static_cast<int>(m_pos.y / m_radius);
    DrawCircle(xCenter, yCenter, m_radius, GREEN);
}

void Player::onKeyDown(){

}

void Player::onKeyUp(){

}

