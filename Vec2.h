#pragma once
#ifndef _Vec2
#define _Vec2

#include "include/raylib.h"

template <class T>
class Vec2{
public:
    Vec2() = default;
    constexpr Vec2(T _x, T _y) :  x(_x), y(_y) {}

    T x;
    T y;

    inline constexpr const Vec2 operator+(const Vec2& rhs)const{ return {x + rhs.x, y + rhs.y}; }
    inline constexpr const Vec2& operator+=(const Vec2& rhs){ return *this = *this + rhs;}
    inline constexpr const Vec2 operator+(const int& rhs)const{return{x + rhs, y + rhs};}
    inline constexpr const Vec2& operator+=(const int& rhs) {return *this = *this + rhs;}
    inline constexpr const Vec2 operator+(const float& rhs)const{return{x + rhs, y + rhs};}
    inline constexpr const Vec2& operator+=(const float& rhs) {return *this = *this + rhs;}

    inline constexpr const Vec2 operator-(const Vec2& rhs)const{ return {x - rhs.x, y - rhs.y}; }
    inline constexpr const Vec2& operator-=(const Vec2& rhs){ return *this = *this - rhs;}
    inline constexpr const Vec2 operator-(const int& rhs)const{return{x - rhs, y - rhs};}
    inline constexpr const Vec2& operator-=(const int& rhs) {return *this = *this - rhs;}
    inline constexpr const Vec2 operator-(const float& rhs)const{return{x - rhs, y - rhs};}
    inline constexpr const Vec2& operator-=(const float& rhs) {return *this = *this - rhs;}

    inline constexpr const Vec2 operator*(const Vec2& rhs)const{ return {x * rhs.x, y * rhs.y}; }
    inline constexpr const Vec2& operator*=(const Vec2& rhs){ return *this = *this * rhs;}
    inline constexpr const Vec2 operator*(const int& rhs)const{return{x * rhs, y * rhs};}
    inline constexpr const Vec2& operator*=(const int& rhs) {return *this = *this * rhs;}
    inline constexpr const Vec2 operator*(const float& rhs)const{return{x * rhs, y * rhs};}
    inline constexpr const Vec2& operator*=(const float& rhs) {return *this = *this * rhs;}

    inline constexpr const Vec2 operator/(const Vec2& rhs)const{ return {x / rhs.x, y / rhs.y}; }
    inline constexpr const Vec2& operator/=(const Vec2& rhs){ return *this = *this / rhs;}
    inline constexpr const Vec2 operator/(const int& rhs)const{return{x / rhs, y / rhs};}
    inline constexpr const Vec2& operator/=(const int& rhs) {return *this = *this / rhs;}
    inline constexpr const Vec2 operator/(const float& rhs)const{return{x / rhs, y / rhs};}
    inline constexpr const Vec2& operator/=(const float& rhs) {return *this = *this / rhs;}

    inline constexpr bool operator==(const Vec2& rhs) const {return x == rhs.x && y == rhs.y;}
    inline constexpr bool operator!=(const Vec2& rhs) const {return !(*this == rhs);}

private:

};

#endif