#ifndef SAFEQUADTREE_H
#define SAFEQUADTREE_H

#include <mutex>
#include <memory>

template <typename T>
class SafeQuadTree
{
    public:
        SafeQuadTree() {
        }

        SafeQuadTree(std::shared_ptr<SafeQuadTree> parentNode) {
            std::unique_lock<std::mutex> lock(_mutex);
            _parentNode = parentNode;
        }

        virtual ~SafeQuadTree() {}

        const int QuadTreeCapacity = 4;
        const int QuadTreeMaxDepth = 8;

        std::shared_ptr<SafeQuadTree> GetParentNode(){
            std::unique_lock<std::mutex> lock(_mutex);
            return GetParentNodeSafe();
        }

        int GetDepth(){
            std::unique_lock<std::mutex> lock(_mutex);
            return GetDepthSafe();
        }

        std::shared_ptr<T> GetValue(){
            std::unique_lock<std::mutex> lock(_mutex);
            return GetValueSafe();
        }

        void CombineNodes(){
            std::unique_lock<std::mutex> lock(_mutex);
            CombineNodesSafe();
        }

    protected:
        std::shared_ptr<T> GetValueSafe(){
            return _value;
        }

        void CombineNodesSafe(){
            if (_southWestNode != nullptr && _northWestNode != nullptr && _northEastNode != nullptr && _southEastNode != nullptr){
                // check to see if all child node values are the same; if so, then combine them, set this value, then delete.

                std::shared_ptr<T> swValue = *_southWestNode.GetValueSafe();
                std::shared_ptr<T> seValue = *_southEastNode.GetValueSafe();
                std::shared_ptr<T> neValue = *_northEastNode.GetValueSafe();
                std::shared_ptr<T> nwValue = *_northWestNode.GetValueSafe();

                if (swValue == seValue == neValue == nwValue){
                    // set this value, then delete the children
                    _value = swValue;
                    _southWestNode.reset();
                    _southEastNode.reset();
                    _northWestNode.reset();
                    _northEastNode.reset();
                }
            }
        }


    private:
        std::shared_ptr<T> _value;

        _northWestNode;
        std::shared_ptr<SafeQuadTree> _southWestNode;
        std::shared_ptr<SafeQuadTree> _northEastNode;
        std::shared_ptr<SafeQuadTree> _southEastNode


        std::shared_ptr<SafeQuadTree> GetParentNodeSafe(){
            return _parentNode;
        }

        int GetDepthSafe(){
            int depth = 1;

            if (_parentNode != nullptr){
                depth += *_parentNode.GetDepth();
            }

            return depth;
        }


        std::mutex _mutex;

        std::shared_ptr<SafeQuadTree> _parentNode;

        std::shared_ptr<SafeQuadTree> _northWestNode;
        std::shared_ptr<SafeQuadTree> _southWestNode;
        std::shared_ptr<SafeQuadTree> _northEastNode;
        std::shared_ptr<SafeQuadTree> _southEastNode;
};

#endif // SAFEQUADTREE_H
