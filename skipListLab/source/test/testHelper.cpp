# include <iostream>
# include <random>
# include <cstdlib>
# include <vector>
# include <set>
#include <list>

# include "skipList.hpp"
# include "myAllocator.hpp"


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



int main()
{

    // std::cout<<"start"<<std::endl;
    // myAllocator<test> allocate(100,10);
    // allocate.apply_alloc(10);

    // static const test  a=test();
    // static const test  b=test();
    // skipList<test,a,b> s;
    // s.insert(test());

    // std::default_random_engine generator(time(NULL));  
    // std::uniform_int_distribution<int> dis(0,100);  
    // for(int i=0;i<5;i++)  
    // {  
    //     std::cout<<dis(generator)<<std::endl;  
    // }  


    std::cout<<"end"<<std::endl;
    return 0;
}