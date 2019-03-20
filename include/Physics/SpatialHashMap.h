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

class BucketNode{
public:



//    std::shared_ptr<BucketTree> _treePtr;


};

class BucketTree{
public:

    BucketTree(int levels, EVector minCoordinate, EVector maxCoordinate){
        _parentPtr = nullptr;

        //todo: check that it doesn't matter which coordinate is larger and which is smaller; if it does, need to order them

        _minCoordinate = minCoordinate;
        _maxCoordinate = maxCoordinate;

        if (levels <= 0){
            // recursive stop
            return;
        }

        // Initialize children
        levels -= 1;

        EVector calculatedMax;
        EVector calculatedMin;

        FixedPointInt halfWidth = (maxCoordinate.X - minCoordinate.X).abs();
        FixedPointInt halfHeight = (maxCoordinate.Y - minCoordinate.Y).abs();

        // Create SW quadrant
            // calculate min NE quadrant
            calculatedMin = minCoordinate;

            // calculate max NE quadrant
            calculatedMax.X = minCoordinate.X + halfWidth;
            calculatedMax.Y = minCoordinate.Y + halfHeight;

        NeBucketTreePtr = std::make_shared<BucketTree>(levels, calculatedMin, calculatedMax);
        NeBucketTreePtr->_parentPtr = this;

        // Create NW quadrant
            // calculate min NW quadrant
            calculatedMin.X = minCoordinate.X;
            calculatedMin.Y = minCoordinate.Y + halfHeight;

            // calculate max NW quadrant
            calculatedMax.X = minCoordinate.X + halfWidth;
            calculatedMax.Y = maxCoordinate.Y;

        NwBucketTreePtr = std::make_shared<BucketTree>(levels, calculatedMin, calculatedMax);
        NwBucketTreePtr->_parentPtr = this;

        // Create SE quadrant
            // calculate min SE quadrant
            calculatedMin.X = minCoordinate.X + halfWidth;
            calculatedMin.Y = minCoordinate.Y;

            // calculate max SE quadrant
            calculatedMax.X = maxCoordinate.X;
            calculatedMax.Y = minCoordinate.Y + halfHeight;

        SeBucketTreePtr = std::make_shared<BucketTree>(levels, calculatedMin, calculatedMax);
        SeBucketTreePtr->_parentPtr = this;

        // Create NE quadrant
            // calculate min NE quadrant
            calculatedMin.X = minCoordinate.X + halfWidth;
            calculatedMin.Y = minCoordinate.Y + halfHeight;

            // calculate max NE quadrant
            calculatedMax.X = maxCoordinate.X;
            calculatedMax.Y = maxCoordinate.Y;

        NeBucketTreePtr = std::make_shared<BucketTree>(levels, calculatedMin, calculatedMax);
        NeBucketTreePtr->_parentPtr = this;
    }

    std::shared_ptr<BucketTree> NeBucketTreePtr;
    std::shared_ptr<BucketTree> NwBucketTreePtr;

    std::shared_ptr<BucketTree> SeBucketTreePtr;
    std::shared_ptr<BucketTree> SwBucketTreePtr;

    virtual ~BucketTree(){
        if (NeBucketTreePtr != nullptr){
            NeBucketTreePtr.reset();
        }

        if (SeBucketTreePtr != nullptr){
            SeBucketTreePtr.reset();
        }

        if (NwBucketTreePtr != nullptr){
            NwBucketTreePtr.reset();
        }

        if (SwBucketTreePtr != nullptr){
            SwBucketTreePtr.reset();
        }

        // Delete bucket?
    }

    //todo: searching
    std::vector<int> GetEntities(EVector minCoordinate, EVector maxCoordinate){

        // Check if it's in the box
            // If not, return nullptr/empty vector?
        // If it is,
        // Check children and return their entities
        // If no children, return bucket

    }

    //todo: moving of items in buckets
    //todo:adding?

private:
    BucketTree* _parentPtr;
    EVector _minCoordinate;
    EVector _maxCoordinate;

};

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
