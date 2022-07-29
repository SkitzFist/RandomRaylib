#pragma once
#ifndef _Player
#define _Player

#include "Entity.h"
#include "Movement.h"

class Player : Entity{
public:
    Player(Vec2<float> _pos, float _radius, float _speed);
    ~Player();
    
    void handleInput();
    
    virtual void update(float dt) override;
    virtual void draw() const override;

private:
    float m_radius;
    float m_speed;
    Vec2<float> m_dir;
    Movement* m_movement;

    void onKeyDown();
    void onKeyUp();
};

#endif