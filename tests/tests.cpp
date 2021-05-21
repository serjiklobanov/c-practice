#include "hash.h"
#include "sort.h"
#include <iostream>

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <chrono> 
 
class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;
	
	std::chrono::time_point<clock_t> m_beg;
 
public:
	Timer() : m_beg(clock_t::now())
	{
	}
	
	void reset()
	{
		m_beg = clock_t::now();
	}
	
	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};


struct TestStruct
{
    std::string key;
    std::string value1;
    std::string value2;


    TestStruct()
    {
    }

    TestStruct(const TestStruct& struct_)
    {
        key = struct_.key;
        value1 = struct_.value1;
        value2 = struct_.value2;
    }
    bool operator==(const TestStruct& t) const
    {
        return (key == t.key) && (value1 == t.value1) && (value2 == t.value2);
    }

};

static std::string makeRandomString(int minL = 7, int maxL = 14)
{
        int length = rand() % maxL + minL;
        static const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";

        std::string s;
        s.reserve(length);
        // сделать случайную строку
        for (int i = 0; i < length; ++i) 
        {
                s += alphanum[rand() % (sizeof(alphanum) - 1)];
        }
        s += "tmp";
        return s;
}

static void generate(TestStruct *pts)
{
        pts->key = makeRandomString();
        pts->value1 = makeRandomString();
        pts->value2 = makeRandomString();
}

unsigned int hash(const TestStruct* pStruct )
{
    const int p = 13;
    unsigned int hash = 0;
    size_t pPow = 1;

    for (char c: pStruct->key)
    {
        std::srand(c - 'A');
        hash += rand() * pPow;
        pPow *= p;
    }

    return hash;
}

int testComparator (const TestStruct* pStruct1, const TestStruct* pStruct2) 
{
    return pStruct1->key < pStruct2->key ? 1 : (pStruct1->key > pStruct2->key ? -1 : 0);
}

TestStruct* binSearch(const TestStruct& element, TestStruct** ppArray, int size) 
{
    if (0 == size) 
    {
        return nullptr;
    }
    
    TestStruct el = element;
    int cmp = testComparator(&el, ppArray[size / 2]);

    if (cmp > 0) 
    {
        return binSearch(element, ppArray, size / 2);
    } 
    else if (cmp < 0) 
    {
        if (size == 1)
        {
            return nullptr;
        }
        return binSearch(element, ppArray + size / 2, size - size / 2);
    } 
    else 
    {
        return ppArray[size / 2];
    }
}



int main() 
{
    int size = 5;
    int *Ns = new int[size]{10000, 50000, 100000, 500000, 1000000};
    Timer t;

    /*int N = 200;
    TestStruct* data = new TestStruct[N];
    lab618::CHash<TestStruct, hash, Compare> Table(13, 2);*/

    for (int i = 4; i < size; ++i)
    {
        int N = Ns[i];
        
        std::vector<TestStruct> data(N);
        for (int i = 0; i < N; ++i)
        {
            generate(&(data[i]));
        }

        TestStruct **array = new TestStruct *[N];
        for (int i = 0; i < N; ++i)
        {
            array[i] = &data[i];
        }
        // размещение
        // сортировка

        t.reset();
        templates::heapSort(array, N, testComparator);
        std::cout << "placing, sort, " << N << ", " << t.elapsed() << '\n';

        // размещение
        // хэш-таблица
        lab618::CHash<TestStruct, hash, testComparator> Table(N / 10, 10);

        t.reset();
        for (int i = 0; i < N; ++i)
        {
            Table.add(&data[i]);
        }
        std::cout << "placing, hash, " << N << ", " << t.elapsed() << '\n';

        // поиск исходных
        // сортировка
        t.reset();
        for (int i = 0; i < N; ++i)
        {
            binSearch(data[i], array, data.size());
        }
        std::cout << "search source, sort, " << N << ", " << t.elapsed() << '\n';

        // поиск исходных
        // хэш-таблица

        t.reset();
        for (int i = 0; i < N; ++i)
        {
            binSearch(data[i], array, data.size());
        }
        std::cout << "search source, hash, " << N << ", " << t.elapsed() << '\n';

        // поиск случайных
        // сортировка

        std::vector<TestStruct> doubleData(N * 2);
        for (int i = 0; i < N * 2; ++i)
        {
            generate(&(doubleData[i]));
        }

        t.reset();
        for (int i = 0; i < N * 2; ++i)
        {
            binSearch(doubleData[i], array, data.size());
        }
        std::cout << "search random, sort, " << N << ", " << t.elapsed() << '\n';

        // поиск случайных
        // хэш-таблица

        t.reset();
        for (int i = 0; i < N * 2; ++i)
        {
            binSearch(doubleData[i], array, data.size());
        }
        std::cout << "search random, hash, " << N << ", " << t.elapsed() << '\n';

        // удаление по одному
        // хэш-таблица

        t.reset();
        for (int i = 0; i < N; ++i)
        {
            Table.remove(data[i]);
        }
        std::cout << "delete by one, hash, " << N << ", " << t.elapsed() << '\n';

        // удаление
        // сортировка

        t.reset();
        delete[] array;
        std::cout << "delete, sort, " << N << ", " << t.elapsed() << '\n';

        // удаление
        // хэш-таблица

        for (int i = 0; i < N; ++i)
        {
            Table.add(&data[i]);
        }

        t.reset();
        Table.clear();
        std::cout << "delete, hash, " << N << ", " << t.elapsed() << '\n';
    }
    return 0;
}