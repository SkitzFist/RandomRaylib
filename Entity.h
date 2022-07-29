#pragma once
#ifndef _Entity
#define _Entity

#include "Vec2.h"
#include "include/raylib.h"

class Entity{
public:
    virtual ~Entity();
    const Vec2<float>& getPos() const;
    void setPos(const Vec2<float>& _pos);
    void setPos(float x, float y);

    virtual void update(float dt) = 0;
    virtual void draw() const = 0;

protected:
    Entity();
    Vec2<float> m_pos;

private:
};

#endif