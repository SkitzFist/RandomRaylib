#pragma once
#ifndef _grid
#define _grid

#include <vector>
#include <unordered_set>
#include <cstddef>

#include "include/raylib.h"
#include "Vec2.h"


struct Cell{
    bool exists;
    bool* edgeExists = new bool[4]{false,false,false,false};
    int* edgeID = new int[4]{0,0,0,0};
};

struct Edge{
    Vec2<int> start;
    Vec2<int> end;
};

struct TargetPoint{
    float x;
    float y;
    TargetPoint(){
        TargetPoint(0.f,0.f);
    }
    TargetPoint(float _x, float _y){
        x = _x;
        y = _y;
    }

    bool operator==(const TargetPoint& other) const{
        return x == other.x && y == other.y;
    }
    
    struct HashFunction{
    size_t operator()(const TargetPoint& point) const
    {
      size_t xHash = std::hash<float>()(point.x);
      size_t yHash = std::hash<float>()(point.y) << 1;
      return xHash ^ yHash;
    }
  };
};

struct VisibilityPoint{ 
    float angle;
    Vec2<float> pos;

    const bool operator==(const VisibilityPoint& other) const{
        if(angle == other.angle){
            return true;
        }else{
            return false;
        }
    }
    const bool operator!=(const VisibilityPoint& other) const{
        if(angle != other.angle){
            return true;
        }else{
            return false;
        }
    }
    const bool operator<(const VisibilityPoint& other) const{
        if(angle < other.angle){
            return true;
        }else{
            return false;
        }
    }

    const bool operator>(const VisibilityPoint& other) const{
        if(angle > other.angle){
            return true;
        }else{
            return false;
        }
    }
};

class Grid{
public:
    Grid(Vec2<int> worldSize);
    ~Grid();

    void draw(Vec2<float> mousePos) const;

    const Vec2<int> getWorldSize() const;
    const int getCellSize() const;

    const Vec2<int> getCellPosition(Vec2<float> worldPos) const;
    const bool isWithinWorldSize(const Vec2<int>) const;
    const bool isWithinWorldSize(const Vec2<float>) const;
    const bool isWithinGridSize(const Vec2<float>) const;
    const bool isWithinGridSize(const Vec2<int>) const;
    const bool cellExists(const Vec2<int>& pos) const;

    void flipCell(Vec2<float> point);
    void findVisibility(float ox, float oy, float radius);
    
private:
    Vec2<int> worldSize;
    Vec2<int> gridSize;
    Cell* cells;
    std::vector<Edge> edges;
    std::vector<VisibilityPoint> visibilityPoints;
    static constexpr int CELL_SIZE = 64;
    static constexpr int NORTH = 0;
    static constexpr int SOUTH = 1;
    static constexpr int EAST = 2;
    static constexpr int WEST = 3;

    void initWalls();
    void randomTiles();

    void drawCells() const;
    void drawEdges() const;
    void drawVisibility(Vec2<float> mousePos) const;

    const int getIndexFromWorldPos(Vec2<float> pos) const;
    const int getIndexFromWorldPos(Vec2<int> pos) const;

    void findEdges();
    void clearCellSEdgeData();
    Cell* getCellOrNull(int index) const;
    const bool cellExists(Cell* cell) const;
    const bool hasNeighbourEdge(Cell* neighbour, int direction) const;

    std::unordered_set<TargetPoint, TargetPoint::HashFunction> getUniquePoints(float ox, float oy, float radius);
    void eliminatePoints();
    int eliminatePointsX(int i);
    int eliminatePointsY(int i);

    void eliminatePoints2();
    const std::vector<int> getPointsToBeRemovedX(int i);
    const std::vector<int> getPointsToBeRemovedY(int i);
};
#endif