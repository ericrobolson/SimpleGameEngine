#ifndef BUCKETTREE_H
#define BUCKETTREE_H

#include "EVector.h"
#include "Algorithms/Deduplication.h"
#include <memory>
#include <vector>
#include "Body.h"
#include "Aabb.h"

using namespace SGE_Math;

namespace SGE_Physics{

//todo: abstract out methods into a generic 'Repository' class, e.g. get entities, search, etc. So that the implementation can be swapped out with what's needed

class BucketTree{
public:
    // remember: (0,0) starts at top left corner, (100,100) would be bottom right

    // Child buckets
    std::shared_ptr<BucketTree> NeBucketTreePtr;
    std::shared_ptr<BucketTree> NwBucketTreePtr;

    std::shared_ptr<BucketTree> SeBucketTreePtr;
    std::shared_ptr<BucketTree> SwBucketTreePtr;

    BucketTree(int levels, EVector minCoordinate, EVector maxCoordinate){
        _parentPtr = nullptr;
        OrderVectors(minCoordinate, maxCoordinate);

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

        FixedPointInt halfWidth = ((maxCoordinate.X - minCoordinate.X).abs()) / 2.0_fp;
        FixedPointInt halfHeight = ((maxCoordinate.Y - minCoordinate.Y).abs()) / 2.0_fp;

        // Create SW quadrant
            // calculate min SW quadrant
            calculatedMin = minCoordinate;
            calculatedMin.Y += halfHeight;

            // calculate max SW quadrant
            calculatedMax.X = calculatedMin.X + halfWidth;
            calculatedMax.Y = maxCoordinate.Y;

        SwBucketTreePtr = std::make_shared<BucketTree>(levels, calculatedMin, calculatedMax);
        SwBucketTreePtr->_parentPtr = this;

        // Create NW quadrant
            // calculate min NW quadrant
            calculatedMin = minCoordinate;

            // calculate max NW quadrant
            calculatedMax.X = calculatedMin.X + halfWidth;
            calculatedMax.Y = calculatedMin.Y + halfHeight;

        NwBucketTreePtr = std::make_shared<BucketTree>(levels, calculatedMin, calculatedMax);
        NwBucketTreePtr->_parentPtr = this;

        // Create SE quadrant
            // calculate min SE quadrant
            calculatedMin = maxCoordinate;
            calculatedMin.X -= halfWidth;
            calculatedMin.Y -= halfHeight;

            // calculate max SE quadrant
            calculatedMax = maxCoordinate;

        SeBucketTreePtr = std::make_shared<BucketTree>(levels, calculatedMin, calculatedMax);
        SeBucketTreePtr->_parentPtr = this;

        // Create NE quadrant
            // calculate min NE quadrant
            calculatedMin = minCoordinate;
            calculatedMin.X += halfWidth;

            // calculate max NE quadrant
            calculatedMax = maxCoordinate;
            calculatedMax.Y -= halfHeight;


        NeBucketTreePtr = std::make_shared<BucketTree>(levels, calculatedMin, calculatedMax);
        NeBucketTreePtr->_parentPtr = this;

        _hasChildren = true;
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

        // delete bucket
        _bucket.clear();
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

        // cleanup bucket
        _bucket.clear();
    }

    std::vector<int> GetEntityIds(Aabb aabb){
        return GetEntities(aabb.MinCoordinate(), aabb.MaxCoordinate());
    }

    void AddEntity(EVector minCoordinate, EVector maxCoordinate, int entityId){
        bool insideBox = InsideBox(minCoordinate, maxCoordinate);

        if (!insideBox){
            return;
        }

        // boundary checking
        if (minCoordinate.X < _minCoordinate.X){
            minCoordinate.X = _minCoordinate.X;
        }

        if (minCoordinate.X > _maxCoordinate.X){
            minCoordinate.X = _maxCoordinate.X;
        }

        if (minCoordinate.Y < _minCoordinate.Y){
            minCoordinate.Y = _minCoordinate.Y;
        }

        if (minCoordinate.Y > _maxCoordinate.Y){
            minCoordinate.Y = _maxCoordinate.Y;
        }

        if (maxCoordinate.X < _minCoordinate.X){
            maxCoordinate.X = _minCoordinate.X;
        }

        if (maxCoordinate.X > _maxCoordinate.X){
            maxCoordinate.X = _maxCoordinate.X;
        }

        if (maxCoordinate.Y < _minCoordinate.Y){
            maxCoordinate.Y = _minCoordinate.Y;
        }

        if (maxCoordinate.Y > _maxCoordinate.Y){
            maxCoordinate.Y = _maxCoordinate.Y;
        }


        if (!_hasChildren){
            // add to bucket
            _bucket.push_back(entityId);
        }
        else{
            // add to children
            if (SwBucketTreePtr != nullptr){
                SwBucketTreePtr->AddEntity(minCoordinate, maxCoordinate, entityId);
            }

            if (SeBucketTreePtr != nullptr){
                SeBucketTreePtr->AddEntity(minCoordinate, maxCoordinate, entityId);
            }

            if (NwBucketTreePtr != nullptr){
                NwBucketTreePtr->AddEntity(minCoordinate, maxCoordinate, entityId);
            }

            if (NeBucketTreePtr != nullptr){
                NeBucketTreePtr->AddEntity(minCoordinate, maxCoordinate, entityId);
            }
      }
    }


    EVector GetMinCoordinate(){
        return _minCoordinate;
    }

    EVector GetMaxCoordinate(){
        return _maxCoordinate;
    }

    bool HasEntities(){
        return !_bucket.empty();
    }

private:

    std::vector<int> GetEntities(EVector minCoordinate, EVector maxCoordinate){
        std::vector<int> entityIds;

        // Check if it's in the box at all
        bool insideBox = InsideBox(minCoordinate, maxCoordinate);


        if (!insideBox){
            return entityIds;
        }

        if (_hasChildren){
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
        }
        else{
            // Add all entities inside bucket

        }

        entityIds.insert(entityIds.end(), _bucket.begin(), _bucket.end());

        // If no parent, dedup entities as this will be returning all calculated entities
        if (_parentPtr == nullptr){
            SGE_Math_Algorithms::Deduplication::Unique(entityIds);
        }

        return entityIds;
    }

    bool InsideBox(EVector & minCoordinate, EVector& maxCoordinate){
        bool insideBox;
    //todo: simplify and rework

        bool yAxisIntersects = (minCoordinate.Y >= _minCoordinate.Y && minCoordinate.Y <= _maxCoordinate.Y)
            || (maxCoordinate.Y >= _minCoordinate.Y && maxCoordinate.Y <= _maxCoordinate.Y);

        bool xAxisIntersects = (minCoordinate.X >= _minCoordinate.X && minCoordinate.X <= _maxCoordinate.X)
            || (maxCoordinate.X >= _minCoordinate.X && maxCoordinate.X <= _maxCoordinate.X);

        // Check to see if min and max are totally inside the bucket
        if (minCoordinate.X <= _minCoordinate.X && minCoordinate.Y <= _minCoordinate.Y
            && maxCoordinate.X >= _maxCoordinate.X && maxCoordinate.Y >= _maxCoordinate.Y){
                insideBox = true;
            }


        else if (minCoordinate.X >= _minCoordinate.X && maxCoordinate.X <= _maxCoordinate.X
        && minCoordinate.Y >= _minCoordinate.Y && maxCoordinate.Y <= _maxCoordinate.Y){
            insideBox = true;
        }

        else if (yAxisIntersects && xAxisIntersects){
            insideBox = true;
        }
        else if (yAxisIntersects && minCoordinate.X <= _minCoordinate.X && maxCoordinate.X >= _maxCoordinate.X){
            insideBox = true;
        }
        else if (xAxisIntersects && minCoordinate.Y <= _minCoordinate.Y && maxCoordinate.Y >= _maxCoordinate.Y){
            insideBox = true;
        }




        // yaxis intersects


         return insideBox;
    }

    // Sort the vectors, so that vec1 is the minimum and vec2 is the maximum
    void OrderVectors(EVector& vec1, EVector& vec2){
        return;

        FixedPointInt i;

        if (vec1.X > vec2.X){
            i = vec2.X;
            vec2.X = vec1.X;
            vec1.X = i;
        }

        if (vec1.Y > vec2.Y){
            i = vec2.X;
            vec2.Y = vec1.Y;
            vec1.Y = i;
        }

    }

    bool _hasChildren;

    BucketTree* _parentPtr;

    std::vector<int> _bucket;

    EVector _minCoordinate;
    EVector _maxCoordinate;

};
}
#endif // BUCKETTREE_H
