#include <iostream>

#include "sort.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>


const int ELEMENTS_COUNT = 1e6;

int intComparator(const int *pElem1, const int *pElem2)
{
  return *pElem1 < *pElem2 ? 1 : (*pElem1 > *pElem2 ? -1 : 0);
}


void TestSortFunction()
{
    std::vector<int> data(ELEMENTS_COUNT);
    for (int i = 0; i < ELEMENTS_COUNT; ++i)
    {
        data[i] = rand();
    }
    
    int **numbs = new int *[data.size()];
    for (int i = 0; i < data.size(); ++i)
    {
        numbs[i] = &data[i];
    }
    templates::heapSort(numbs, data.size(), intComparator);

    std::vector<int> copyData = data;
    std::sort(copyData.begin(), copyData.end());
    for (int i = 0; i < data.size(); ++i)
    {
        assert(copyData[i] == *numbs[i]);
    }
}

int main()
{
    TestSortFunction();
    return 0;
}
