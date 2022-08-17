#include <utility>

#include "include/raylib.h"
#include "Vec2.h"

namespace Mouse{
    const Vec2<float> getPosition(){
        return std::move(Vec2<float>{GetMousePosition().x, GetMousePosition().y});
    }
}