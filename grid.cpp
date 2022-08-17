#include "grid.h"
#include "Log.h"
#include "ray.h"
#include "sort.h"
#include "Renderer.h"
#include "random" // se om denna behövs eller inte

/*
    Optimeringsplan:
        1. Kasta endast rays till unika points. [x]
            1.2 behöver skriva egen hash och set för att plocka ut unika points. [x]
            1.3 eliminera points som ligger på samma edge så det bara är en start och endpoint [x] - fick det inte att bli bra
    Ray 2.  Fixa stepsize & mapCheck []
            2.1 stepsize borde vara cellSize / dir för att det ska bli längre steps. []
            2.2 Mapcheck måste gå på gridPos istället för worldPos []
                2.2.1 måste ändra mapcheck i init värdet för raylength. []
*/

Grid::Grid(Vec2<int> _worldSize){
    worldSize = _worldSize;
    gridSize = {worldSize.x / CELL_SIZE, worldSize.y / CELL_SIZE};
    cells = new Cell[gridSize.x * gridSize.y];
    initWalls();
    randomTiles();
    findEdges();
}

Grid::~Grid(){

}

void Grid::initWalls(){
     for(int y = 0; y < gridSize.y; ++y){
        for(int x = 0; x < gridSize.x; ++x){
            bool isBorderCell = x == 1 || y == 1 || y == gridSize.y -2 || x == gridSize.x -2;
            cells[y * gridSize.x + x].exists = isBorderCell;
        }
    }
}

void Grid::randomTiles(){
    for(int y = 2; y < gridSize.y - 2; ++y ){
        for(int x = 2; x < gridSize.x - 2; ++x){
            int random = std::rand() % 100;
            cells[y * gridSize.x +x].exists = random < 25? true : false; 
        }
    }
}

void Grid::draw(Vec2<float> mousePos)const{
    drawCells();
    drawEdges();
    drawVisibility(mousePos);
}

void Grid::drawCells() const{
    for(int y = 0; y < gridSize.y; ++y){
        for(int x = 0; x < gridSize.x; ++x){
            if(cells[y * gridSize.x + x].exists){
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLUE);
            }
        }
    }
}

void Grid::drawEdges()const{
    for(const auto& edge : edges){
        DrawLine(edge.start.x, edge.start.y, edge.end.x, edge.end.y, WHITE);
    }
}

void Grid::drawVisibility(Vec2<float> mousePos)const {

    //std::vector<VisibilityPoint*>* pointsWithinReach = getPointsWithinReach(mousePos.x, mousePos.y, 15.f);
    //Log::info("Number of points within reach: " + std::to_string(pointsWithinReach->size()));
    if(visibilityPoints.size() > 0){
        for(int i = 1; i < visibilityPoints.size() - 2; ++i){
            Renderer::drawTriangle(visibilityPoints[i].pos, mousePos,visibilityPoints[i+1].pos, YELLOW);
        }
        Renderer::drawTriangle(visibilityPoints[0].pos, visibilityPoints[visibilityPoints.size() -1].pos, mousePos, YELLOW);
    }

   unsigned char red = 0;
   for(const auto& point : visibilityPoints){
       red += 3 % 255;
       Color c {red, 100, 100,255};
       DrawCircle(point.pos.x, point.pos.y, 2.f, c);
   }
}

void Grid::flipCell(Vec2<float> _point){
    int index = getIndexFromWorldPos(_point);
    cells[index].exists = !cells[index].exists;
    findEdges();
}

const Vec2<int> Grid::getWorldSize() const{
    return worldSize;
}

const int Grid::getCellSize()const{
    return CELL_SIZE;
}

const int Grid::getIndexFromWorldPos(Vec2<float> _pos) const{
    Vec2<int> iPos = {static_cast<int>(_pos.x), static_cast<int>(_pos.y)};
    return getIndexFromWorldPos(iPos);
}

const int Grid::getIndexFromWorldPos(Vec2<int> _pos)const{
    Vec2<int> gridPos = {_pos.x / CELL_SIZE, _pos.y / CELL_SIZE};
    return gridPos.y * gridSize.x + gridPos.x;
}

const Vec2<int> Grid::getCellPosition(Vec2<float> worldPos)const{
    Vec2<int> pos{static_cast<int>(worldPos.x / CELL_SIZE), static_cast<int>(worldPos.y / CELL_SIZE)};
    pos.x *= CELL_SIZE;
    pos.y *= CELL_SIZE;
    return pos;
}

const bool Grid::isWithinWorldSize(Vec2<float> pos)const{
    return pos.x >= 0 && pos.x < worldSize.x && pos.y >= 0 && pos.y < worldSize.y;
}

const bool Grid::isWithinWorldSize(Vec2<int> pos)const{
    return pos.x >= 0 && pos.x < worldSize.x && pos.y >= 0 && pos.y < worldSize.y;
}

const bool Grid::isWithinGridSize(Vec2<float> pos)const{
    return pos.x >= 0 && pos.x < gridSize.x && pos.y >= 0 && pos.y < gridSize.y;
}

const bool Grid::isWithinGridSize(Vec2<int> pos)const{
    return pos.x >= 0 && pos.x < gridSize.x && pos.y >= 0 && pos.y < gridSize.y;
}

const bool Grid::cellExists(const Vec2<int>& pos)const{
    int index = getIndexFromWorldPos(pos);
    return cells[index].exists;
}

void Grid::findEdges(){
    clearCellSEdgeData();
    edges.clear();

    for(int y = 0; y < gridSize.y; ++y){
        for(int x = 0; x < gridSize.x; ++x){
            int index = y * gridSize.x + x;
            Cell* cell = getCellOrNull(index);
            
            if(cellExists(cell)){
                Cell* n = getCellOrNull(index - gridSize.x);
                Cell* s = getCellOrNull(index + gridSize.x);
                Cell* e = getCellOrNull(index + 1);
                Cell* w = getCellOrNull(index - 1);

                if(!cellExists(w)){
                    if(hasNeighbourEdge(n, WEST)){
                        edges[n->edgeID[WEST]].end.y += CELL_SIZE;
                        cell->edgeExists[WEST] = true;
                        cell->edgeID[WEST] = n->edgeID[WEST];
                    }else{
                        cell->edgeExists[WEST] = true;
                        cell->edgeID[WEST] = edges.size();
                        edges.emplace_back(Edge{
                            Vec2<int>{(x * CELL_SIZE),(y * CELL_SIZE)},//start
                            Vec2<int>{(x * CELL_SIZE), (y*CELL_SIZE) + CELL_SIZE} // end
                        });
                    }
                }

                if(!cellExists(n)){
                    if(hasNeighbourEdge(w, NORTH)){
                        edges[w->edgeID[NORTH]].end.x += CELL_SIZE;
                        cell->edgeExists[NORTH] = true;
                        cell->edgeID[NORTH] = w->edgeID[NORTH];
                    }else{
                        cell->edgeExists[NORTH] = true;
                        cell->edgeID[NORTH] = edges.size();
                        edges.emplace_back(Edge{
                            Vec2<int>{(x * CELL_SIZE),(y * CELL_SIZE)},//start
                            Vec2<int>{(x * CELL_SIZE) + CELL_SIZE, (y*CELL_SIZE)} // end
                        });
                    }
                }
            
                if(!cellExists(e)){
                    if(hasNeighbourEdge(n, EAST)){
                        edges[n->edgeID[EAST]].end.y += CELL_SIZE;
                        cell->edgeExists[EAST] = true;
                        cell->edgeID[EAST] = n->edgeID[EAST];
                    }else{
                        cell->edgeExists[EAST] = true;
                        cell->edgeID[EAST] = edges.size();
                        edges.emplace_back(Edge{
                            Vec2<int>{(x * CELL_SIZE) + CELL_SIZE, (y * CELL_SIZE)},//start
                            Vec2<int>{(x * CELL_SIZE) + CELL_SIZE, (y*CELL_SIZE) + CELL_SIZE} // end
                        });
                    }
                }
              
                if(!cellExists(s)){
                    if(hasNeighbourEdge(w, SOUTH)){
                        edges[w->edgeID[SOUTH]].end.x += CELL_SIZE;
                        cell->edgeExists[SOUTH] = true;
                        cell->edgeID[SOUTH] = w->edgeID[SOUTH];
                    }else{
                        cell->edgeExists[SOUTH] = true;
                        cell->edgeID[SOUTH] = edges.size();
                        edges.emplace_back(Edge{
                            Vec2<int>{(x * CELL_SIZE),(y * CELL_SIZE) + CELL_SIZE},//start
                            Vec2<int>{(x * CELL_SIZE) + CELL_SIZE, (y*CELL_SIZE) + CELL_SIZE} // end
                        });
                    }
                }
                
            }
        }
    }
}

void Grid::clearCellSEdgeData(){
    for(int i =0; i < gridSize.x * gridSize.y; ++i){
        for(int j = 0; j < 4; ++j){
            cells[i].edgeExists[j] = false;
            cells[i].edgeID[j] = -1;
        }
    }
}

Cell* Grid::getCellOrNull(int index) const{
    if(index < 0 || index > gridSize.x * gridSize.y){
        return nullptr;
    }
    return &cells[index];
}

const bool Grid::cellExists(Cell* cell) const{
    if(cell == nullptr){
        return false;
    }
    if(!cell->exists){
        return false;
    }
    //return true if cell is not nullptr && cell exists
    return true;
}

const bool Grid::hasNeighbourEdge(Cell* neighbour, int direction)const{
    if(neighbour == nullptr){
        return false;
    }
    return neighbour->edgeExists[direction];
}

void Grid::findVisibility(float ox, float oy, float radius){
    visibilityPoints.clear();

    std::unordered_set<TargetPoint,TargetPoint::HashFunction> edgePoints = getUniquePoints(ox, oy, radius);
    for(const auto& edgePoint : edgePoints){
            float base_Ang = atan2f(edgePoint.y - oy , edgePoint.x - ox);
            float ang = 0.f;
            for(int j = 0; j < 3; ++j){
                if(j == 0){ang = base_Ang - 0.0001;}
                if(j == 1){ang = base_Ang;}
                if(j == 2){ang = base_Ang + 0.0001;}
                VisibilityPoint point;
                point.angle = ang;
                point.pos = Line::getIntersection(Vec2<int>{static_cast<int>(ox), static_cast<int>(oy)}, ang, this, radius);
                visibilityPoints.emplace_back(point);
            }
    }
    //Log::info("---------------------------------");
    //Log::info("points before: " + std::to_string(visibilityPoints.size()));    
    Sort::quickSort(visibilityPoints, 0, visibilityPoints.size() - 1);
    //eliminatePoints2();
    //Log::info("points after: " + std::to_string(visibilityPoints.size()));    
}

std::unordered_set<TargetPoint, TargetPoint::HashFunction> Grid::getUniquePoints(float ox, float oy, float radius){
    std::unordered_set<TargetPoint, TargetPoint::HashFunction> uniquePoints;

    for(const Edge& edge : edges){
        for(int i = 0; i < 2; ++i){
            float x = i == 0 ? static_cast<float>(edge.start.x) : static_cast<float>(edge.end.x);
            float y = i == 0 ? static_cast<float>(edge.start.y) : static_cast<float>(edge.end.y);
            
            Vec2<float> diff = { x - ox, y - oy};
            float length = sqrt((diff.x * diff.x) + (diff.y * diff.y));
            if(length <= radius){
                TargetPoint point(x,y);
                uniquePoints.insert(point);
            }    
        }
    }
    return std::move(uniquePoints); 
}

void Grid::eliminatePoints(){
 
   for(int i = 0; i < visibilityPoints.size() - 1; ++i){
        int ii = i + 1;
        if(ii >= visibilityPoints.size()){
            break;
        } 

        VisibilityPoint* p1 = &visibilityPoints[i];
        VisibilityPoint* p2 = &visibilityPoints[ii];

        if(p1->pos.y == p2->pos.y){
            i = eliminatePointsY(i);
        }else if(p1->pos.x == p2->pos.x){
            i = eliminatePointsX(i);
        }
   }
}

//kan optimera genom att spara alla indexes som ska tas bort och göra det i reverser order, då omalokeras mindre element
int Grid::eliminatePointsY(int i){
    int startIndex = i;
    int currentIndex = i+1;
    VisibilityPoint* p1 = &visibilityPoints[startIndex];
    VisibilityPoint* p2 = &visibilityPoints[currentIndex];
    while(p1->pos.y == p2->pos.y && currentIndex < visibilityPoints.size())
    {
        ++currentIndex;
        if(currentIndex < visibilityPoints.size()){
            p2 = &visibilityPoints[currentIndex];
        }
    }
    visibilityPoints.erase(visibilityPoints.begin() + (startIndex + 1), visibilityPoints.begin() + (currentIndex));
    return startIndex + 2;
}

int Grid::eliminatePointsX(int i){
    int startIndex = i;
    int currentIndex = i+1;
    VisibilityPoint* p1 = &visibilityPoints[startIndex];
    VisibilityPoint* p2 = &visibilityPoints[currentIndex];
    while(p1->pos.x == p2->pos.x && currentIndex < visibilityPoints.size())
    {
        ++currentIndex;
        if(currentIndex < visibilityPoints.size()){
            p2 = &visibilityPoints[currentIndex];
        }
    }
    visibilityPoints.erase(visibilityPoints.begin() + (startIndex + 1), visibilityPoints.begin() + (currentIndex));
    return startIndex + 2;
}

void Grid::eliminatePoints2(){
    std::vector<std::vector<int>> pointsToBeRemoved;

    for(int i = 0; i < visibilityPoints.size(); ++i){
        int ii = i + 1;
        if(ii >= visibilityPoints.size()) { break; }

        VisibilityPoint* p1 = &visibilityPoints[i];
        VisibilityPoint* p2 = &visibilityPoints[ii];
        int newI = i;
        if(p1->pos.x == p2->pos.x){
            std::vector<int> points = getPointsToBeRemovedX(i);
            i += points.size();
            pointsToBeRemoved.emplace_back(std::move(points));
        }else if(p1->pos.y == p2->pos.y){
            std::vector<int> points = getPointsToBeRemovedY(i);
            i += points.size();
            pointsToBeRemoved.emplace_back(std::move(points));
        }
        if(i >= visibilityPoints.size()){
            break;
        }
    }

   std::vector<VisibilityPoint> newPoints;
   for(int i = 0; i < pointsToBeRemoved.size(); ++i){
        int start = pointsToBeRemoved[i][0];
        int end = pointsToBeRemoved[i][(pointsToBeRemoved[i].size() - 1)];
        int mid = (pointsToBeRemoved[i].size() / 2);

        newPoints.emplace_back(visibilityPoints[start]);
        newPoints.emplace_back(visibilityPoints[end]);

        if(mid != end && mid != start){
            newPoints.emplace_back(visibilityPoints[pointsToBeRemoved[i][mid]]);
        }
   }
   visibilityPoints = newPoints;
}

const std::vector<int> Grid::getPointsToBeRemovedY(int i){
    std::vector<int> points;
    points.emplace_back(i);
    points.emplace_back(i + 1);
    
    float yPos = visibilityPoints[i].pos.y;
    int nextIndex = i + 2;
    while(nextIndex < visibilityPoints.size()){
        if(visibilityPoints[nextIndex].pos.y == yPos){
            points.emplace_back(nextIndex);
        }else{
            break;
        }
        ++nextIndex;
    }
    return std::move(points);
}

const std::vector<int> Grid::getPointsToBeRemovedX(int i){
    std::vector<int> points;
    points.emplace_back(i);
    points.emplace_back(i + 1);
    
    float xPos = visibilityPoints[i].pos.x;
    int nextIndex = i + 2;
    while(nextIndex < visibilityPoints.size()){
        if(visibilityPoints[nextIndex].pos.x == xPos){
            points.emplace_back(nextIndex);
        }else{
            break;
        }
        ++nextIndex;
    }

    return std::move(points);
}