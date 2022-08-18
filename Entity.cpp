#include "Entity.h"

    Entity::Entity(){
    
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