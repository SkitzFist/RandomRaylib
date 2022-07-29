#pragma once
#ifndef _Movement
#define _Movement

#include "Vec2.h"

class Movement{
public:
    virtual const Vec2<float>& move(float dt, const Vec2<float>& _pos, 
                                    const Vec2<float>& _dir, float _speed) const;
};

#endif