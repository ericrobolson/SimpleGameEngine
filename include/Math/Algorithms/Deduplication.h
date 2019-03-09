#ifndef DEDUPLICATION_H
#define DEDUPLICATION_H

#include <memory>
#include <set>

namespace SGE_Math_Algorithms
{

class Deduplication
{
    public:
        ///Returns a sorted, unique list
        template <class TComponent>
        static void Unique(std::vector<TComponent>& a){
            std::vector<TComponent> copyArray;

            auto cmp = [](TComponent a, TComponent b) {return a < b;};

            std::set<TComponent, decltype(cmp)> s(cmp);

            for( int i = 0; i < a.size(); ++i ) s.insert( a[i] );
            a.assign( s.begin(), s.end() );
        }

    protected:
};

}

#endif // DEDUPLICATION_H
