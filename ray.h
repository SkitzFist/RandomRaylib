#pragma once
#ifndef _ray
#define _ray

#include "include/raylib.h"
#include "grid.h"
#include <math.h>
#include "Log.h"

namespace Line{
    static Vec2<float> getIntersection(Vec2<int> _start, float _angle, Grid* grid, float _maxDistance = 100.f){
        //Log::info("---------RAY--------------");
        Vec2<float> start = Vec2<float>{static_cast<float>(_start.x), static_cast<float>(_start.y)};
        Vec2<float> dir = Vec2<float>{ cosf(_angle), sinf(_angle)};

        Vec2<float> unitStepSize = Vec2<float>{
            abs(1.f/ dir.x),
            abs(1.f/ dir.y)
        }; 
        //Log::point("dir: ", dir);
        //Log::point("Stepsize", unitStepSize);
        
        Vec2<int> mapCheck = grid->getCellPosition(start);
        Vec2<float> rayLength = {0.f,0.f};
        Vec2<int> mapStep = {0,0};
        //Log::point("Mapcheck start", mapCheck );
        if(dir.x < 0){
            mapStep.x = -1;
            //mapStep.x = -grid->getCellSize();
            rayLength.x = (start.x - static_cast<float>(mapCheck.x)) * unitStepSize.x;
        }else{
            mapStep.x = 1;
            //mapStep.x = grid->getCellSize();
            rayLength.x = (static_cast<float>(mapCheck.x + 1) - start.x) * unitStepSize.x;
        }

        if(dir.y < 0){
            mapStep.y = -1;
            //mapStep.y = -grid->getCellSize();
            rayLength.y = (start.y - static_cast<float>(mapCheck.y)) * unitStepSize.y;
        }else{
            mapStep.y = 1;
            //mapStep.y = grid->getCellSize();
            rayLength.y = (static_cast<float>(mapCheck.y + 1) - start.y) * unitStepSize.y;
        }

        bool foundTile = false;
        float distance = 0.0f;
        while (!foundTile && distance < _maxDistance)
        {
            //Log::info("______");
            if(rayLength.x < rayLength.y){
                mapCheck.x += mapStep.x;
                distance = rayLength.x;
                rayLength.x += unitStepSize.x;
            }else{
                mapCheck.y += mapStep.y;
                distance = rayLength.y;
                rayLength.y += unitStepSize.y;
            }
            //Log::point("\tMapcheck", mapCheck);
            //Log::point("\tRaylength", rayLength);
            //Log::info("\tDistance: " + std::to_string(distance));    
            
            if(grid->isWithinWorldSize(mapCheck)){
                if(grid->cellExists(mapCheck)){
                    foundTile = true;
                }
            }
            
        }
        if(foundTile){
            //Log::info("FoundTile: true");
        }else{
            //Log::info("FoundTile: false");
        }
        
        Vec2<float> point{
            start.x + (dir.x * distance),
            start.y + (dir.y* distance)
        };
        return point;
    }
}

#endif