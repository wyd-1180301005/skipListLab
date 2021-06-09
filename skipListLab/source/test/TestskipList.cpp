# include <iostream>
# include <typeinfo>
# include <set>

# include "myAllocator.hpp"
# include "skipList.hpp"
# include "gtest/gtest.h"


// 用来进行对skipList的test的test fixture 类
class TestskipList: public ::testing::Test
{
  protected:
    skipList<int>* a1;
    skipList<int>* a2;
    TestskipList()
    {
      a1=new skipList<int>(20,0.5,100,20,3);
      a2=new skipList<int>(1,0.5,1000,30,2);
    }
    ~TestskipList()
    {
      delete a1;
      delete a2;
    }
};
// 测试查找的正确性
TEST_F(TestskipList,test_insert_find)
{
    a1->insert(29,10);
    ASSERT_EQ(true,a1->find(29));
    ASSERT_EQ(false,a1->find(10));

    for(int i=30;i<1000;i++)
        a1->insert(i,((i*i+11*i)%37));
    for(int i=30;i<1000;i++)
        ASSERT_EQ(true,a1->find(i));
    for(int i=1000;i<100000;i++)
       ASSERT_EQ(false,a1->find(i)); 
    for(int i=0;i<29;i++)
       ASSERT_EQ(false,a1->find(i)); 

    a2->insert(29,10);
    ASSERT_EQ(true,a2->find(29));
    ASSERT_EQ(false,a2->find(10));

    for(int i=30;i<1000;i++)
        a2->insert(i,((i*i+11*i)%47));
    for(int i=30;i<1000;i++)
        ASSERT_EQ(true,a2->find(i));
    for(int i=1000;i<100000;i++)
       ASSERT_EQ(false,a2->find(i)); 
    for(int i=0;i<29;i++)
       ASSERT_EQ(false,a2->find(i)); 
}
// 测试插入-删除的正确性
TEST_F(TestskipList,test_insert_remove)
{
    using rpt=skipListNode<int>;
    using pt=rpt*;
    myAllocator<rpt>* alloc1=a1->debug_getallocator();

    int num_layer=10;
    int num=29;
    a1->insert(num,num_layer);
    pt p_in=alloc1->pt;
    a1->erase(num);
    pt p_out=alloc1->pt_free;
    int num_layer_out=alloc1->last_size_free;
    ASSERT_EQ(p_in,p_out);
    ASSERT_EQ(p_in,alloc1->debug_get_memo(num_layer+1));
    ASSERT_EQ(num_layer+1,num_layer_out);

    for(int i=100;i<10000;i+=std::max(1,(i*i+11*i)%7))
    {
      num_layer=(i*i+11*i)%77;
      num=i;
      a1->insert(num,num_layer);
      pt p_in=alloc1->pt;
      a1->erase(num);
      pt p_out=alloc1->pt_free;
      int num_layer_out=alloc1->last_size_free;
      ASSERT_EQ(p_in,p_out);
      ASSERT_EQ(p_in,alloc1->debug_get_memo(num_layer+1));
      ASSERT_EQ(num_layer+1,num_layer_out);
    }
}

// 和stlmultiset对照,确保正确性
TEST_F(TestskipList,test_insert_remove_find)
{
  std::multiset<int> s0;
  for(int i=0;i<10000;i+=std::max(1,(i*i+11*i)%7))
  {
    a1->insert(i,(i*i+11*i)%77);
    s0.insert(i);
  }
  for(int i=0;i<10000;i+=std::max(1,(i*i*i+11*i*i+17*i)%13))
  {
    bool success=a1->erase(i);
    ASSERT_EQ(success,s0.find(i)!=s0.end());
    s0.erase(i);
  }
  for(int i=0;i<10000;i+=std::max(1,(i*i+11*i)%7))
  {
    ASSERT_EQ(a1->find(i),s0.find(i)!=s0.end());
  }
}

// 和stlmultiset对照,确保正确性
TEST_F(TestskipList,test_empty_remove_find)
{
  for(int i=0;i<10;i++)
  {
    a1->erase(i);
    a1->find(i);
    a1->insert(i);
  }
  // for(int i=0;i<100000;i++)
  // {
  //   a1->erase(i);
  //   a1->find(i);
  //   a1->insert(i);
  // }
  // for(int i=0;i<100000;i++)
  // {
  //   a1->erase(i);
  //   a1->erase(i);
  // }
  // for(int i=0;i<100000;i++)
  // {
  //   a1->find(i);
  // }
}

// 和stlmultiset对照,确保正确性
TEST_F(TestskipList,test_multi_insert_remove_find)
{
  for(int i=0;i<1000;i++)
  {
        ASSERT_EQ(false,a1->erase(i));
        ASSERT_EQ(false,a1->find(i));
        a1->insert(i);
        if(!a1->find(i))
          a1->insert(i);
        if(!a1->find(i))
          a1->insert(i);
        if(!a1->find(i))
          a1->insert(i);
        if(!a1->find(i))
          a1->insert(i);
        // a1->insert(i);
        ASSERT_EQ(true,a1->find(i));
        ASSERT_EQ(true,a1->find(i));
        ASSERT_EQ(true,a1->find(i));
        ASSERT_EQ(true,a1->find(i));
        ASSERT_EQ(true,a1->find(i));
        ASSERT_EQ(true,a1->find(i));
        ASSERT_EQ(true,a1->erase(i));
        if(!a1->find(i))
          a1->insert(i);
        ASSERT_EQ(true,a1->erase(i));
        if(!a1->find(i))
          a1->insert(i);
        ASSERT_EQ(true,a1->erase(i));
        ASSERT_EQ(false,a1->erase(i));
  }
  // for(int i=0;i<100000;i++)
  // {
  //   a1->erase(i);
  //   a1->find(i);
  //   a1->insert(i);
  // }
  // for(int i=0;i<100000;i++)
  // {
  //   a1->erase(i);
  //   a1->erase(i);
  // }
  // for(int i=0;i<100000;i++)
  // {
  //   a1->find(i);
  // }
}