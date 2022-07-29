#include "SimpleMovement.h"
#include <utility>

SimpleMovement::~SimpleMovement(){
    
}

const Vec2<float> SimpleMovement::move(float dt, const Vec2<float>& _pos, 
                                    const Vec2<float>& _dir, float _speed) const{
    Vec2 newPos = {
        _pos + (_dir * dt * _speed)
    };
    return std::move(newPos);
}