#include "SpatialHashMap.h"
#include "EVector.h"
#include "Aabb.h"
#include "Algorithms/Deduplication.h"
using namespace SGE_Physics;
using namespace SGE_Math;
using namespace SGE_Math_Algorithms;


SpatialHashMap::SpatialHashMap()
{
    _sceneWidth = (int)600.0_fp;
    _sceneHeight = (int)480.0_fp;
    _cellSize = (int)20.0_fp;

    ClearGrid();
}

SpatialHashMap::SpatialHashMap(FixedPointInt sceneWidth, FixedPointInt sceneHeight, FixedPointInt cellSize)
{
    _sceneWidth = (int)sceneWidth;
    _sceneHeight = (int)sceneHeight;
    _cellSize = (int)cellSize;

    ClearGrid();
}

SpatialHashMap::~SpatialHashMap()
{
    ClearGrid();
}

SpatialHashMap::CellKey SpatialHashMap::HashEVector(const EVector& ev){
    CellKey ck;

    ck.X = ((int)ev.X / _cellSize);
    ck.Y = ((int)ev.Y / _cellSize);

    return ck;
}

void SpatialHashMap::ClearGrid(){
    for (int i = 0; i < _rows; i++){
        for (int j = 0; j < _columns; j++){
            if (_cells[i][j] != nullptr){
                _cells[i][j].reset();
            }
        }
    }
}

std::vector<int> SpatialHashMap::GetEntityIds(Aabb aabb){
    std::vector<int> entityIds;

    CellKey minHash, maxHash;

    minHash = HashEVector(aabb.MinCoordinate());
    maxHash = HashEVector(aabb.MaxCoordinate());

    // get all entityIds in the buckets between the min and max hashes
    for (int x = minHash.X; x <= maxHash.X; x++){
        for (int y = minHash.Y; y <= maxHash.Y; y++){
            if (_cells[x][y] != nullptr){
                // get all items in the bucket
                std::shared_ptr<Node> currentNode = _cells[x][y];
                while (currentNode != nullptr){
                    entityIds.push_back(currentNode->EntityId);
                    currentNode = currentNode->Next;
                }
            }
        }
    }

    Deduplication::Unique(entityIds);

    return entityIds;
}


void SpatialHashMap::AddBody(const int& entityId, Body body){
    CellKey minHash, maxHash;

    Aabb bodyAabb = body.GetRoughAabb();

    minHash = HashEVector(bodyAabb.MinCoordinate());
    maxHash = HashEVector(bodyAabb.MaxCoordinate());

    // add to all cells in between the min hash and max hash
    for (int x = minHash.X; x <= maxHash.X; x++){
        for (int y = minHash.Y; y <= maxHash.Y; y++){
            if (_cells[x][y] == nullptr){
                // add new cell and set it's value
                _cells[x][y] = std::make_shared<Node>();
                _cells[x][y]->EntityId = entityId;

            }else{
                _cells[x][y]->Add(entityId);
            }
        }
    }
}
