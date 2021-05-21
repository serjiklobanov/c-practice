#ifndef SORT_HEAD_H_2021_02_25
#define SORT_HEAD_H_2021_02_25

#include <iostream>

namespace templates
{
    /** Определение типа функции сравнения элементов
    \return
    \li > 0  - pElem1 меньше pElem2
    \li 0   - элементы pElem1 и pElem2 равны
    \li < 0 - pElem1 больше pElem2
    */
    typedef  int (CompareSortType)(const void *pElem1, const void *pElem2);

    void heapSort(void **ppArray, int length, CompareSortType pCompareFunc);

    template <class T>
    void heapSort(T **ppArray, int length, int (pCompareFunc)(const T *pElem1, const T *pElem2))
    {
        heapSort(reinterpret_cast<void**>(ppArray), length, (CompareSortType*)pCompareFunc);
    }
    
    int Left(int index) 
    {
	    return index * 2;
    }

    int Right(int index) 
    {
    	return index * 2 + 1;
    }

    void Sift_down(void **heap, int index, int length, CompareSortType pCompareFunc) 
    {
	    int max;
	    if (Left(index) <= length && pCompareFunc(heap[Left(index) - 1], heap[index - 1]) < 0) 
        {
		    max = Left(index);
	    }
	    else 
        {
		    max = index;
	    }
	    if (Right(index) <= length && pCompareFunc(heap[Right(index) - 1], heap[max - 1]) < 0) 
        {
		    max = Right(index);
	    }
	    if (max != index) 
        {
		    std::swap(heap[index - 1], heap[max - 1]);
		    Sift_down(heap, max, length, pCompareFunc);
	    }
    }

    void Build_Heap(void **heap, int length, CompareSortType pCompareFunc) 
    {
	    for (int i = length / 2; i > 0; i--) 
        {
		    Sift_down(heap, i, length, pCompareFunc);
	    }
    }

    void heapSort(void **ppArray, int length, CompareSortType pCompareFunc)
    {
	    Build_Heap(ppArray, length, pCompareFunc);
	    for (int i = length; i > 1; i--) 
        {
		    std::swap(ppArray[0], ppArray[i - 1]);
	    	Sift_down(ppArray, 1, i - 1, pCompareFunc);
	    }
    }
}; // namespace templates

#endif // #define SORT_HEAD_H_2021_02_25
