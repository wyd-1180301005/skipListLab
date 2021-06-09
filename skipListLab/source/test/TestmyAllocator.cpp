# include <iostream>
# include <typeinfo>

# include "myAllocator.hpp"
# include "gtest/gtest.h"

class classA
{
public:
    int v;
    classA* nxt=nullptr;
    classA* lst=nullptr;
};

template<typename T>
class classA_tmpl
{
public:
    int v;
    T& v1;
    classA* nxt=nullptr;
    classA* lst=nullptr;
};

// 测试is_builtin_type<>
TEST(Test_is_builtin_type, built_in_type) 
{
  // typical built_in type
  ASSERT_TRUE(is_builtin_type<int>);
  ASSERT_TRUE(is_builtin_type<int*>);
  ASSERT_TRUE(is_builtin_type<int&>);
  ASSERT_TRUE(is_builtin_type<float&>);
  ASSERT_TRUE(is_builtin_type<float**>);
  ASSERT_TRUE(is_builtin_type<float*&>);
  ASSERT_TRUE(is_builtin_type<float***>);

  // reference and pointer (considered as built_in type)
  ASSERT_TRUE(is_builtin_type<classA*>);
  ASSERT_TRUE(is_builtin_type<classA&>);
  ASSERT_TRUE(is_builtin_type<classA*&>);
  ASSERT_TRUE(is_builtin_type<const classA&>);
  ASSERT_TRUE(is_builtin_type<const classA*>);

  ASSERT_TRUE(is_builtin_type<classA_tmpl<int>*>);
  ASSERT_TRUE(is_builtin_type<classA_tmpl<int>&>);
  ASSERT_TRUE(is_builtin_type<classA_tmpl<int>*&>);
  ASSERT_TRUE(is_builtin_type<const classA_tmpl<int>&>);
  ASSERT_TRUE(is_builtin_type<const classA_tmpl<int>*>);

  ASSERT_TRUE(is_builtin_type<classA_tmpl<classA>*>);
  ASSERT_TRUE(is_builtin_type<classA_tmpl<classA>&>);
  ASSERT_TRUE(is_builtin_type<classA_tmpl<classA>*&>);
  ASSERT_TRUE(is_builtin_type<const classA_tmpl<classA>&>);
  ASSERT_TRUE(is_builtin_type<const classA_tmpl<classA>*>);
  
}
TEST(Test_is_builtin_type, not_built_in_type) 
{
  ASSERT_FALSE(is_builtin_type<classA>);
  ASSERT_FALSE(is_builtin_type<const classA>);
  ASSERT_FALSE(is_builtin_type<classA_tmpl<int>>);
  ASSERT_FALSE(is_builtin_type<const classA_tmpl<int>>);
  ASSERT_FALSE(is_builtin_type<classA_tmpl<classA>>);
  ASSERT_FALSE(is_builtin_type<const classA_tmpl<classA>>);
}

// 测试is_ref<>
TEST(Test_is_ref,is_ref)
{
  ASSERT_TRUE(is_ref<int&>);
  ASSERT_TRUE(is_ref<float&>);
  ASSERT_TRUE(is_ref<float*&>);
  ASSERT_TRUE(is_ref<classA*&>);
  ASSERT_TRUE(is_ref<classA&>);
  ASSERT_TRUE(is_ref<classA_tmpl<int>&>);
  ASSERT_TRUE(is_ref<classA_tmpl<int*>&>);
  ASSERT_TRUE(is_ref<classA_tmpl<classA>&>);
  ASSERT_TRUE(is_ref<classA_tmpl<classA>*&>);
}
TEST(Test_is_ref,is_not_ref)
{
  ASSERT_FALSE(is_ref<int>);
  ASSERT_FALSE(is_ref<float>);
  ASSERT_FALSE(is_ref<float*>);
  ASSERT_FALSE(is_ref<classA*>);
  ASSERT_FALSE(is_ref<classA>);
  ASSERT_FALSE(is_ref<classA_tmpl<int>>);
  ASSERT_FALSE(is_ref<classA_tmpl<int*>>);
  ASSERT_FALSE(is_ref<classA_tmpl<classA>>);
  ASSERT_FALSE(is_ref<classA_tmpl<classA>*>);
}


// 测试ref_unless_builtin
TEST(Test_ref_unless_builtin,is_built_in)
{
  ASSERT_FALSE(is_ref<ref_unless_builtin<int>>);
  ASSERT_FALSE(is_ref<ref_unless_builtin<float>>);
  ASSERT_FALSE(is_ref<ref_unless_builtin<int*>>);
  ASSERT_FALSE(is_ref<ref_unless_builtin<float*>>);
  ASSERT_FALSE(is_ref<ref_unless_builtin<const int*>>);
  ASSERT_FALSE(is_ref<ref_unless_builtin<const float*>>);
  ASSERT_FALSE(is_ref<ref_unless_builtin<classA*>>);

  // 对于ref本身,变化后还是ref
  ASSERT_TRUE(is_ref<ref_unless_builtin<classA&>>);
  ASSERT_TRUE(is_ref<ref_unless_builtin<const classA&>>);
  ASSERT_TRUE(is_ref<ref_unless_builtin<classA_tmpl<int>&>>);
  ASSERT_TRUE(is_ref<ref_unless_builtin<const classA_tmpl<int>&>>);
  ASSERT_TRUE(is_ref<ref_unless_builtin<classA_tmpl<classA>&>>);
  ASSERT_TRUE(is_ref<ref_unless_builtin<const classA_tmpl<classA>&>>);

  ASSERT_FALSE(is_ref<ref_unless_builtin<const classA*>>);
  ASSERT_FALSE(is_ref<ref_unless_builtin<classA_tmpl<int>*>>);
  ASSERT_FALSE(is_ref<ref_unless_builtin<const classA_tmpl<int>*>>);
  ASSERT_FALSE(is_ref<ref_unless_builtin<classA_tmpl<classA>*>>);
  ASSERT_FALSE(is_ref<ref_unless_builtin<const classA_tmpl<classA>*>>);
}
TEST(Test_ref_unless_builtin,is_not_built_in)
{

  ASSERT_TRUE(is_ref<ref_unless_builtin<classA>>);
  ASSERT_TRUE(is_ref<ref_unless_builtin<const classA>>);
  ASSERT_TRUE(is_ref<ref_unless_builtin<classA_tmpl<int>>>);
  ASSERT_TRUE(is_ref<ref_unless_builtin<classA_tmpl<int*>>>);
  ASSERT_TRUE(is_ref<ref_unless_builtin<classA_tmpl<classA>>>);
  ASSERT_TRUE(is_ref<ref_unless_builtin<const classA_tmpl<int>>>);
  ASSERT_TRUE(is_ref<ref_unless_builtin<const classA_tmpl<int*>>>);
  ASSERT_TRUE(is_ref<ref_unless_builtin<const classA_tmpl<classA>>>);
}


// 用来进行对myAllocator的test的test fixture 类
class TestmyAllocator: public ::testing::Test
{
  protected:
    myAllocator<classA>* a1;
    myAllocator<classA>* a2;
    TestmyAllocator()
    {
      a1=new myAllocator<classA>(100,10,3);
      a2=new myAllocator<classA>(1000,10,3);
    }
    ~TestmyAllocator()
    {
      delete a1;
      delete a2;
    }
};

TEST_F(TestmyAllocator,test_count)
{
  ASSERT_EQ(1,a1->debug_count_pool());
  ASSERT_EQ(1,a2->debug_count_pool());
  for(int i=0;i<10;i++)
  {
    a1->apply_alloc(50);
  }
  ASSERT_EQ(5,a1->debug_count_pool());
  for(int i=0;i<10;i++)
  {
    a2->apply_alloc(100);
  }
  ASSERT_EQ(1,a2->debug_count_pool());
}

TEST_F(TestmyAllocator,test_alloc1)
{
  classA* p1=a1->apply_alloc(20);
  classA* p2=a1->apply_alloc(30);
  classA* p3=a1->apply_alloc(1);
  ASSERT_EQ(p1+20,p2);
  ASSERT_EQ(p2+20,p3-10);
  ASSERT_EQ(p1+50,p3);
}

TEST_F(TestmyAllocator,test_alloc2)
{
  classA* p1=a1->apply_alloc(20); 
  classA* p2=a1->apply_alloc(30);
  a1->free_alloc(p2,30);
  classA* p3=a1->apply_alloc(20);
  classA* p4=a1->apply_alloc(5);
  classA* p5=a1->apply_alloc(5);
  ASSERT_EQ(p1+20,p2);
  ASSERT_EQ(p2,p3);
  ASSERT_EQ(p2+20,p4);
  ASSERT_EQ(p2+25,p5);
}
