#include <iostream>

#include "mm.h"
#include <string>

const int ELEMENTS_COUNT = 4;

struct TestStruct
{
    std::string key;
    std::string value1;
    std::string value2;
};

typedef lab618::CMemoryManager<TestStruct> TestMM;

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
    for (int i = 0; i < length; ++i) {
        s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s += "tmp";
    return s;
}

static void generate(TestStruct* pts)
{
    pts->key = makeRandomString();
    pts->value1 = makeRandomString();
    pts->value2 = makeRandomString();
}

void TestMMFunction()
{

    TestMM mem_manager(2, true);
    for (int i = 0; i < ELEMENTS_COUNT; ++i)
    {
        TestStruct* ts = mem_manager.newObject();
        generate(ts);
    }

    mem_manager.clear();

    TestStruct* tsarr[ELEMENTS_COUNT];

    for (int i = 0; i < ELEMENTS_COUNT; ++i)
    {
        tsarr[i] = mem_manager.newObject();
        mem_manager.deleteObject(tsarr[i]);
        tsarr[i] = mem_manager.newObject();
        generate(tsarr[i]);
    }

    for (int i = 0; i < ELEMENTS_COUNT; ++i)
    {
        mem_manager.deleteObject(tsarr[i]);
    }

}

int main()
{
    TestMMFunction();
    return 0;
}
