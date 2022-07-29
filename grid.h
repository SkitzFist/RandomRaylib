#pragma once
#ifndef _grid
#define _grid
#include <vector>
#include <unordered_set>
#include <cstddef>
#include "include/raylib.h"


struct Cell{
    bool exists;
    bool* edgeExists = new bool[4]{false,false,false,false};
    int* edgeID = new int[4]{0,0,0,0};
};

struct Edge{
    Vector2i start;
    Vector2i end;
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
    Vector2 pos;

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
    Grid(Vector2i worldSize);
    ~Grid();

    void draw(Vector2 mousePos) const;

    const Vector2i getWorldSize() const;
    const int getCellSize() const;

    const Vector2i getCellPosition(Vector2 worldPos) const;
    const Vector2i getCellPosition(Vector2i worldPos) const;
    const bool isWithinWorldSize(const Vector2i) const;
    const bool isWithinWorldSize(const Vector2) const;
    const bool isWithinGridSize(const Vector2) const;
    const bool isWithinGridSize(const Vector2i) const;
    const bool cellExists(const Vector2i& pos) const;

    void flipCell(Vector2 point);
    void findVisibility(float ox, float oy, float radius);
    
private:
    Vector2i worldSize;
    Vector2i gridSize;
    Cell* cells;
    std::vector<Edge> edges;
    std::vector<VisibilityPoint> visibilityPoints;
    static constexpr int CELL_SIZE = 32;
    static constexpr int NORTH = 0;
    static constexpr int SOUTH = 1;
    static constexpr int EAST = 2;
    static constexpr int WEST = 3;

    void initWalls();
    void randomTiles();

    void drawCells() const;
    void drawEdges() const;
    void drawVisibility(Vector2 mousePos) const;

    const int getIndexFromWorldPos(Vector2 pos) const;
    const int getIndexFromWorldPos(Vector2i pos) const;

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