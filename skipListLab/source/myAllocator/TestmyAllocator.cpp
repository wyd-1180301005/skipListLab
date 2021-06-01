# include <iostream>
# include "myAllocator.hpp"


int main()
{
    std::cout<<"TestmyAllocator"<<std::endl;
    myAllocator<int> allocate(100,10);
    
}