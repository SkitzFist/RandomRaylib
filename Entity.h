#pragma once
#ifndef _Entity.h
#define _Entity.h

#include "Vec2.h"
#include "include/raylib.h"

class Entity{
public:
    virtual ~Entity();
    const Vec2<float>& getPos() const;
    
    void setPos(const Vec2<float>& _pos);
    void setPos(float x, float y);

protected:
    Entity();
    Vec2<float> m_pos;

private:
};

Entity::Entity() :
     m_pos(0.f,0.f){
}

Entity::~Entity(){

}

const Vec2<float>& Entity::getPos() const{
    return m_pos;
}

void Entity::setPos(const Vec2<float>& _pos){
    m_pos = _pos;
}

void Entity::setPos(float _x, float _y){
    m_pos.x = _x;
    m_pos.y = _y;
}

#endif