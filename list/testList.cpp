#include <iostream>

#include "list.h"
#include <string>

const int ELEMENTS_COUNT = 10;

struct TestStruct
{
    std::string key;
    std::string value1;
    std::string value2;
};

typedef lab618::CSingleLinkedList<TestStruct> TestSingleList;
typedef lab618::CDualLinkedList<TestStruct> TestList;

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

static void generate(TestStruct *pts)
{
    pts->key = makeRandomString();
    pts->value1 = makeRandomString();
    pts->value2 = makeRandomString();
}

void TestListFunction()
{
    // тест односвязного списка

    TestSingleList single_list;
    for (int i = 0; i < ELEMENTS_COUNT; ++i)
    {
        TestStruct ts;
        generate(&ts);
        single_list.pushBack(ts);
    }

    _ASSERT(single_list.getSize() == ELEMENTS_COUNT);

    for (TestSingleList::CIterator it = single_list.begin(); it.isValid(); ++it)
    {
        it.getLeaf();
        TestStruct ts = *it;
        single_list.erase(it);
    }

    _ASSERT(single_list.getSize() == 0);

    /// тест двусвязного списка

    TestList list;
    for (int i = 0; i < ELEMENTS_COUNT; ++i)
    {
        TestStruct ts;
        generate(&ts);
        list.pushBack(ts);
    }

    _ASSERT(list.getSize() == ELEMENTS_COUNT);

    for (TestList::CIterator it = list.begin(); it.isValid(); ++it)
    {
        it.getLeaf();
        TestStruct ts = *it;
        list.erase(it);
    }

    _ASSERT(single_list.getSize() == 0);

    for (int i = 0; i < ELEMENTS_COUNT; ++i)
    {
        TestStruct ts;
        generate(&ts);
        list.pushFront(ts);
    }

    _ASSERT(list.getSize() == ELEMENTS_COUNT);

    for (TestList::CIterator it = list.end(); it.isValid(); --it)
    {
        it.getLeaf();
        TestStruct ts = *it;
        list.erase(it);
    }

    _ASSERT(single_list.getSize() == 0);

    for (int i = 0; i < ELEMENTS_COUNT; ++i)
    {
        TestStruct ts;
        generate(&ts);
        list.pushFront(ts);
    }

    list.clear();

    _ASSERT(single_list.getSize() == 0);

}

int main()
{
    TestListFunction();
    return 0;
}
