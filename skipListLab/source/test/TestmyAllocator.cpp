# include <iostream>
# include <typeinfo> // 调试元编程时使用

# include "myAllocator.hpp"

class NodeType
{
public:
    int v;
    NodeType* nxt=nullptr;
    NodeType* lst=nullptr;
};

int main()
{
    std::cout<<"TestmyAllocator"<<std::endl;

    // 测试is_builtin_type-全部正确
    // 1 
    if (is_builtin_type<int>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;
    // 2
    if (is_builtin_type<bool>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;
    // 3
    if (is_builtin_type<int*>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;
    // 4 
    if (is_builtin_type<int**>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;
    // 5
    if (is_builtin_type<int***>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;
    // 6
    if (is_builtin_type<float***>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;  
    // 7
    if (is_builtin_type<float***>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;
    // 8
    if (is_builtin_type<float&>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;
    // 9
    if (is_builtin_type<float*&>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;
    // 10
    if (is_builtin_type<float*&>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;
    // 11 no
    if (is_builtin_type<NodeType>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;
    // 12
    if (is_builtin_type<NodeType&>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;
    // 13
    if (is_builtin_type<NodeType*&>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;
    // 14
    if (is_builtin_type<const NodeType*&>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;
    // 15 no
    if (is_builtin_type<const NodeType>)std::cout<<"yes"<<std::endl;else std::cout<<"no"<<std::endl;

    // myAllocator<int> allocate(100,10);
    // int * p10=allocate.apply_alloc(10);
    // int * p100=allocate.apply_alloc(100);
    // int * p20=allocate.apply_alloc(40);
    // allocate.free_alloc(p100,100);
    // allocate.free_alloc(p10,10);
    // int * p8=allocate.apply_alloc(8);

}