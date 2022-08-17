#pragma once
#ifndef _Renderer
#define _Renderer

#include "include/raylib.h"
#include "Vec2.h"

namespace Renderer{
    static void drawTriangle(const Vec2<float>& p1, const Vec2<float>& p2, const Vec2<float>& p3, Color color){
        DrawTriangle(Vector2{p1.x, p1.y}, Vector2{p2.x, p2.y}, Vector2{p3.x, p3.y}, color);
    }
}

#endif