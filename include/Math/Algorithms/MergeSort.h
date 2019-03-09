#ifndef MERGESORT_H
#define MERGESORT_H

#include <memory>

namespace SGE_Math_Algorithms
{


/// MergeSort algorithm (https://en.wikipedia.org/wiki/Merge_sort)
class MergeSort
{
    public:
        template <class TComponent>
        static void Sort(std::vector<TComponent>& a){
            std::vector<TComponent> copyArray = a;

            TopDownSplitMerge(copyArray, 0, a.size(), a);   // sort data from B[] into A[]
        }

    protected:

    private:
        template <class TComponent>
        static void Sort(std::vector<TComponent>& a, std::vector<TComponent>& copyArray, int n){
            CopyArray(a, 0, n, copyArray);
            TopDownSplitMerge(copyArray, 0, n, a);   // sort data from B[] into A[]
        }


        template <class TComponent>
        static void TopDownSplitMerge(std::vector<TComponent>& b, int iBegin, int iEnd, std::vector<TComponent>& a){
             if(iEnd - iBegin < 2)                       // if run size == 1
                return;                                 //   consider it sorted
            // split the run longer than 1 item into halves
            int iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
            // recursively sort both runs from array A[] into B[]
            TopDownSplitMerge(a, iBegin,  iMiddle, b);  // sort the left  run
            TopDownSplitMerge(a, iMiddle,    iEnd, b);  // sort the right run
            // merge the resulting runs from array B[] into A[]
            TopDownMerge(b, iBegin, iMiddle, iEnd, a);
        }

        template <class TComponent>
        static void TopDownMerge(std::vector<TComponent>& a, int iBegin, int iMiddle, int iEnd, std::vector<TComponent>& b){
            int i = iBegin, j = iMiddle;

            // While there are elements in the left or right runs...
            for (int k = iBegin; k < iEnd; k++) {
                // If left run head exists and is <= existing right run head.
                if (i < iMiddle && (j >= iEnd || a[i] <= a[j])) {
                    b[k] = a[i];
                    i = i + 1;
                } else {
                    b[k] = a[j];
                    j = j + 1;
                }
            }
        }

        template <class TComponent>
        static void CopyArray(std::vector<TComponent>& a, int iBegin, int iEnd, std::vector<TComponent>& b){
            for (int i = iBegin; i < iEnd; i++){
                b[i] = a[i];
            }
        }
};

}

#endif // MERGESORT_H
