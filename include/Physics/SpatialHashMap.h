#ifndef SPATIALHASHMAP_H
#define SPATIALHASHMAP_H

#include "FixedPointInt.h"
#include "EVector.h"
#include "Aabb.h"
#include "Body.h"
#include <vector>
#include <memory>
#include <utility>
using namespace SGE_Math;
#include <unordered_map>


namespace SGE_Physics{

// todo: implement R/W lock? or multithreading
// make an array of linked lists that take ints for entity ids?


class SpatialHashMap
{
    public:
        ///todo: Change to use a hashmap instead of an array; as the array doesn't allow negative values
        SpatialHashMap(EVector minVector, EVector maxVector);
        virtual ~SpatialHashMap();

        void ClearGrid();
        std::vector<int> GetEntityIds(Aabb aabb); // takes an AABB and gets all entities in it

        void AddBody(const int& entityId, Body body);// Todo: when hashing an object, get it's basic AABB and hash the Min/Max of that. Then add the entity to all cells/buckets in between that

    private:
        EVector _minVector;
        EVector _maxVector;

        class Node {
        public:
            int EntityId;
            std::shared_ptr<Node> Next;

            void Add(int entityId){
                if (Next != nullptr){
                    Next->Add(entityId);
                }else{
                    // add new cell and set it's value
                    Next = std::make_shared<Node>();
                    Next->EntityId = entityId;
                }
            }

            virtual ~Node(){
                if (Next != nullptr){
                    Next.reset();
                }
            }
        };

        class CellKey{
        public:
            int X;
            int Y;
        };

        CellKey HashEVector(const EVector& ev);

        int _sceneSize;
        int _cellSize;

        static const int _numberOfBuckets = 10;

        std::shared_ptr<Node> _cells[_numberOfBuckets][_numberOfBuckets];
};


}

#endif // SPATIALHASHMAP_H
