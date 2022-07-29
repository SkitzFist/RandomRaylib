#pragma once
#ifndef _SimpleMovement
#define _SimpleMovement

#include "Movement.h"

class SimpleMovement : public Movement{
public:
    SimpleMovement() = default;
    virtual ~SimpleMovement();
    virtual const Vec2<float> move(float dt, const Vec2<float>& _pos, 
                                const Vec2<float>& _dir, float _speed) const override;

};

#endif