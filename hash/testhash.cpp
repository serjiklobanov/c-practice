#include "hash.h"
#include <iostream>

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>


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

int Compare (const TestStruct* pStruct1, const TestStruct* pStruct2) 
{
  return pStruct1->key < pStruct2->key ? 1 : (pStruct1->key > pStruct2->key ? -1 : 0);
}

int main() 
{
  int N = 200;
  TestStruct* data = new TestStruct[N];
  lab618::CHash<TestStruct, hash, Compare> Table(13, 2);

  for (int i = 0; i < N; ++i)
  {
    generate(&(data[i]));
  }

  for (int i = 0; i < N/2; ++i)
  {
    Table.add(&data[i]);
  }

  for (int i = 0; i < N/2; ++i) {
    auto pT = Table.find(data[i]);
    assert(*pT == data[i]);
  }

  for (int i = N/2; i < N; ++i) {
    auto pT = Table.find(data[i]);
    assert(pT == nullptr);
  }

  for (int i = 0; i < N/2; ++i)
  {
    data[i].value2 += "_updated";
    Table.update(&data[i]);
  }

  for (int i = 0; i < N/2; ++i) {
    auto pT = Table.find(data[i]);
    assert(*pT == data[i]);
  }

  for (int i = 0; i< N/2; ++i) {
    auto pT = Table.find(data[i]);
    Table.remove(*pT);
  }

  for (int i = 0; i < N/2; ++i) {
    auto pT = Table.find(data[i]);
    assert(pT == nullptr);
  }


  return 0;
}