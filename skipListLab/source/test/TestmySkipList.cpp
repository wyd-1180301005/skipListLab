# include <iostream>
# include <random>
# include <cstdlib>
# include <vector>
# include <set>
#include <list>

// # include "skipList.hpp"
# include "myAllocator.hpp"
# include "gtest/gtest.h"
# include "testHelper.cpp"


class test
{
private:
    int m=0;
public:
    test(/* args */);
    ~test();
};

test::test(/* args */)
{
}

test::~test()
{
}

TEST(TestMETA, is_builtin_type) 
{
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "hello");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
TEST(TestMETA, is_builtin_type1) 
{
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "hello");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}