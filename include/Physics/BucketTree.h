#ifndef BUCKETTREE_H
#define BUCKETTREE_H

#include "EVector.h"
#include "Algorithms/Deduplication.h"
#include <memory>
#include <vector>

using namespace SGE_Math;

namespace SGE_Physics{


class BucketTree{
public:
    class BucketNode{
        public:
        BucketTree* TreePtr;

        int EntityId;

        BucketNode* NextPtr;
        BucketNode* PreviousPtr;

        BucketNode(int entityId){
            NextPtr = nullptr;
            PreviousPtr = nullptr;
            EntityId = entityId;
        }

        virtual ~BucketNode(){
            if (NextPtr != nullptr){
                delete NextPtr;
            }
        }
    };


    // Child buckets
    std::shared_ptr<BucketTree> NeBucketTreePtr;
    std::shared_ptr<BucketTree> NwBucketTreePtr;

    std::shared_ptr<BucketTree> SeBucketTreePtr;
    std::shared_ptr<BucketTree> SwBucketTreePtr;

    BucketTree(int levels, EVector minCoordinate, EVector maxCoordinate){
        _parentPtr = nullptr;
        _bucketPtr = nullptr;

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

    void FlushBuckets(){
        if (NeBucketTreePtr != nullptr){
            NeBucketTreePtr->FlushBuckets();
        }

        if (NwBucketTreePtr != nullptr){
            NwBucketTreePtr->FlushBuckets();
        }

        if (SeBucketTreePtr != nullptr){
            SeBucketTreePtr->FlushBuckets();
        }

        if (SwBucketTreePtr != nullptr){
            SwBucketTreePtr->FlushBuckets();
        }

        if (_bucketPtr != nullptr){
            delete _bucketPtr;
        }
    }

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

        if (_bucketPtr != nullptr){
            delete _bucketPtr;
        }
    }

    //todo: searching
    std::vector<int> GetEntities(EVector minCoordinate, EVector maxCoordinate){
        std::vector<int> entityIds;

        // Check if it's in the box at all
        bool insideBox; //todo:

        if (!insideBox){
            return entityIds;
        }

        // Check children that are inside the box and return their entities
        if (NeBucketTreePtr != nullptr){
            std::vector<int> entities2 = NeBucketTreePtr->GetEntities(minCoordinate, maxCoordinate);

            entityIds.insert(entityIds.end(), entities2.begin(), entities2.end());
        }

        if (NwBucketTreePtr != nullptr){
            std::vector<int> entities2 = NwBucketTreePtr->GetEntities(minCoordinate, maxCoordinate);

            entityIds.insert(entityIds.end(), entities2.begin(), entities2.end());
        }

        if (SwBucketTreePtr != nullptr){
            std::vector<int> entities2 = SwBucketTreePtr->GetEntities(minCoordinate, maxCoordinate);

            entityIds.insert(entityIds.end(), entities2.begin(), entities2.end());
        }


        if (SeBucketTreePtr != nullptr){
            std::vector<int> entities2 = SeBucketTreePtr->GetEntities(minCoordinate, maxCoordinate);

            entityIds.insert(entityIds.end(), entities2.begin(), entities2.end());
        }

        // Add all entities inside bucket
        BucketNode* bucketPtr = _bucketPtr;
        while(bucketPtr != nullptr){
            entityIds.push_back(bucketPtr->EntityId);

            bucketPtr = bucketPtr->NextPtr;
        }

        // If no parent, dedup entities as this will be returning all calculated entities
        if (_parentPtr == nullptr){
            SGE_Math_Algorithms::Deduplication::Unique(entityIds);
        }

        return entityIds;
    }

    //todo: moving of items in buckets
    //todo:adding?

private:
    BucketTree* _parentPtr;
    BucketNode* _bucketPtr;

    EVector _minCoordinate;
    EVector _maxCoordinate;

};
}
#endif // BUCKETTREE_H
