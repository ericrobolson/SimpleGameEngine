#include "SpatialHashMap.h"
#include "EVector.h"
#include "Aabb.h"
#include "Algorithms/Deduplication.h"
#include "Debugger.h"
using namespace SGE_Physics;
using namespace SGE_Math;
using namespace SGE_Math_Algorithms;





SpatialHashMap::SpatialHashMap(EVector minVector, EVector maxVector)
{
    _minVector = minVector;
    _maxVector = maxVector;

    // Data structure:
        // Quad Tree that ends with Buckets

    _cellSize = (int)50.0_fp;

    _sceneSize = _numberOfBuckets * _cellSize;

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
/*
    if (ck.X >= _cellSize * _numberOfBuckets){
        ck.X = (_cellSize * _numberOfBuckets) -1;
    }

    if (ck.Y >= _cellSize * _numberOfBuckets){
        ck.Y = (_cellSize * _numberOfBuckets) -1;
    }
*/
    return ck;
}

void SpatialHashMap::ClearGrid(){
    for (int i = 0; i < _numberOfBuckets; i++){
        for (int j = 0; j < _numberOfBuckets; j++){
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
            SGE::Debugger::Instance().WriteMessage("Bucket: X: " + std::to_string(x) + ", Y: " + std::to_string(y));

            if (_cells[x][y] != nullptr){
                // get all items in the bucket
                std::shared_ptr<Node> currentNode = _cells[x][y];
                while (currentNode != nullptr){
                    entityIds.push_back(currentNode->EntityId);
                    SGE::Debugger::Instance().WriteMessage("Bucket: " + std::to_string(currentNode->EntityId));
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
                            SGE::Debugger::Instance().WriteMessage("Add entity " + std::to_string(entityId));

            }
        }
    }
}
