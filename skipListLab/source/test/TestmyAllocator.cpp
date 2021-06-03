# include <iostream>
# include <typeinfo>

# include "myAllocator.hpp"
# include "gtest/gtest.h"

class NodeType
{
public:
    int v;
    NodeType* nxt=nullptr;
    NodeType* lst=nullptr;
};

template<typename T>
class NodeType_tmpl
{
public:
    int v;
    T& v1;
    NodeType* nxt=nullptr;
    NodeType* lst=nullptr;
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
  ASSERT_TRUE(is_builtin_type<NodeType*>);
  ASSERT_TRUE(is_builtin_type<NodeType&>);
  ASSERT_TRUE(is_builtin_type<NodeType*&>);
  ASSERT_TRUE(is_builtin_type<const NodeType&>);
  ASSERT_TRUE(is_builtin_type<const NodeType*>);

  ASSERT_TRUE(is_builtin_type<NodeType_tmpl<int>*>);
  ASSERT_TRUE(is_builtin_type<NodeType_tmpl<int>&>);
  ASSERT_TRUE(is_builtin_type<NodeType_tmpl<int>*&>);
  ASSERT_TRUE(is_builtin_type<const NodeType_tmpl<int>&>);
  ASSERT_TRUE(is_builtin_type<const NodeType_tmpl<int>*>);

  ASSERT_TRUE(is_builtin_type<NodeType_tmpl<NodeType>*>);
  ASSERT_TRUE(is_builtin_type<NodeType_tmpl<NodeType>&>);
  ASSERT_TRUE(is_builtin_type<NodeType_tmpl<NodeType>*&>);
  ASSERT_TRUE(is_builtin_type<const NodeType_tmpl<NodeType>&>);
  ASSERT_TRUE(is_builtin_type<const NodeType_tmpl<NodeType>*>);
  
}
TEST(Test_is_builtin_type, not_built_in_type) 
{
  ASSERT_FALSE(is_builtin_type<NodeType>);
  ASSERT_FALSE(is_builtin_type<const NodeType>);
  ASSERT_FALSE(is_builtin_type<NodeType_tmpl<int>>);
  ASSERT_FALSE(is_builtin_type<const NodeType_tmpl<int>>);
  ASSERT_FALSE(is_builtin_type<NodeType_tmpl<NodeType>>);
  ASSERT_FALSE(is_builtin_type<const NodeType_tmpl<NodeType>>);
}

// 测试is_ref<>
TEST(Test_is_ref,is_ref)
{
  ASSERT_TRUE(is_ref<int&>);
  ASSERT_TRUE(is_ref<float&>);
  ASSERT_TRUE(is_ref<float*&>);
  ASSERT_TRUE(is_ref<NodeType*&>);
  ASSERT_TRUE(is_ref<NodeType&>);
  ASSERT_TRUE(is_ref<NodeType_tmpl<int>&>);
  ASSERT_TRUE(is_ref<NodeType_tmpl<int*>&>);
  ASSERT_TRUE(is_ref<NodeType_tmpl<NodeType>&>);
  ASSERT_TRUE(is_ref<NodeType_tmpl<NodeType>*&>);
}
TEST(Test_is_ref,is_not_ref)
{
  ASSERT_FALSE(is_ref<int>);
  ASSERT_FALSE(is_ref<float>);
  ASSERT_FALSE(is_ref<float*>);
  ASSERT_FALSE(is_ref<NodeType*>);
  ASSERT_FALSE(is_ref<NodeType>);
  ASSERT_FALSE(is_ref<NodeType_tmpl<int>>);
  ASSERT_FALSE(is_ref<NodeType_tmpl<int*>>);
  ASSERT_FALSE(is_ref<NodeType_tmpl<NodeType>>);
  ASSERT_FALSE(is_ref<NodeType_tmpl<NodeType>*>);
}



    // myAllocator<int> allocate(100,10);
    // int * p10=allocate.apply_alloc(10);
    // int * p100=allocate.apply_alloc(100);
    // int * p20=allocate.apply_alloc(40);
    // allocate.free_alloc(p100,100);
    // allocate.free_alloc(p10,10);
    // int * p8=allocate.apply_alloc(8);
