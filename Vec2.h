#pragma once
#ifndef _Vec2
#define _Vec2

template <class T>
class Vec2{
public:
    Vec2() = default;
    constexpr Vec2(T _x, T _y) :  x(_x), y(_y) {}

    T x;
    T y;

    inline constexpr Vec2 operator+(const Vec2& rhs)const{ return {x + rhs.x, y + rhs.y}; }
    inline constexpr Vec2& operator+=(const Vec2& rhs){ return *this = *this + rhs;}

    inline constexpr Vec2 operator-(const Vec2& rhs)const{ return {x - rhs.x, y - rhs.y}; }
    inline constexpr Vec2& operator-=(const Vec2& rhs){ return *this = *this - rhs;}

    inline constexpr Vec2 operator*(const Vec2& rhs)const{ return {x * rhs.x, y * rhs.y}; }
    inline constexpr Vec2& operator*=(const Vec2& rhs){ return *this = *this * rhs;}
    
    inline constexpr Vec2 operator/(const Vec2& rhs)const{ return {x / rhs.x, y / rhs.y}; }
    inline constexpr Vec2& operator/=(const Vec2& rhs){ return *this = *this / rhs;}

    inline constexpr bool operator==(const Vec2& rhs) const {return x == rhs.x && y == rhs.y;}
    inline constexpr bool operator!=(const Vec2& rhs) const {return !(*this == rhs);}

private:

};

#endif