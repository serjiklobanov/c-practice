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
    
    int **array = new int *[data.size()];
    for (int i = 0; i < data.size(); ++i)
    {
        array[i] = &data[i];
    }
    templates::heapSort(array, data.size(), intComparator);

    std::vector<int> copyData = data;
    std::sort(copyData.begin(), copyData.end());
    for (int i = 0; i < data.size(); ++i)
    {
        assert(copyData[i] == *array[i]);
    }
    delete[] array;
}

int main()
{
    TestSortFunction();
    return 0;
}
