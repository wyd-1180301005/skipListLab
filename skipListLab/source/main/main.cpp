# include <iostream>
# include <typeinfo>
# include <set>
# include "myAllocator.hpp"
# include "skipList.hpp"
# define DISABLE_DEBUG_INTERFACE

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
    classA* nxt=nullptr;
    classA* lst=nullptr;
    classA_tmpl(int a,float b,int* c,classA d)
    {
        
    }
};

template<typename T>
class classB_tmpl
{
public:
    classA_tmpl<T> *   tmpa;

    template<typename ... ArgClassA>
    classB_tmpl(int m,int* n,ArgClassA ... args)
    {
        tmpa=new classA_tmpl<T>(args...);
    }
};
 
void param_func(int a,classA a1,const char* a2,int* a3)
{
   std::cout<<"param_func"<<std::endl;
}

template<typename ... Args> 
void multi_param_func(Args ... arg) 
{
    param_func(arg ... );
}

int main()
{
    std::cout<<"main start"<<std::endl;

    using rpt=skipListNode<int>;
    using pt=rpt*;
    skipList<int>* a1=new skipList<int>(20,100,20,3);
    // myAllocator<rpt>* alloc1=a1->debug_getallocator();

    // int num,num_layer;
    // for(int i=100;i<200;i+=(i*i+11*i)%7)
    // {
    //   std::cout<<"insert "<<i<<std::endl;  
    //   num_layer=(i*i+11*i)%77;
    //   num=i;
    //   a1->insert(num,num_layer);
    //   pt p_in=alloc1->pt;
    //   a1->remove(num);
    //   pt p_out=alloc1->pt_free;
    //   int num_layer_out=alloc1->last_size_free;
    //   if(p_in!=p_out)
    //     std::cout<<"error p_in!=p_out "<<p_in<<" "<<p_out<<std::endl;
    //   if(p_in!=alloc1->debug_get_memo(num_layer+1))
    //     std::cout<<"error p_in!=mem_out "<<p_in<<" "<<alloc1->debug_get_memo(num_layer+1)<<std::endl;
    //   if(num_layer+1!=num_layer_out)
    //     std::cout<<"error num_layer+1!=num_layer_out "<<num_layer+1<<" "<<num_layer_out<<std::endl;
    //   std::cout<<"end insert remove "<<i<<std::endl;  
    // }
    std::multiset<int> s0;
    for(int i=0;i<100;i+=std::max(1,(i*i+11*i)%7))
    {
      a1->insert(i,(i*i+11*i)%77);
      s0.insert(i);
      std::cout<<"insert "<<i<<std::endl;
    }
    for(int i=0;i<100;i+=std::max(1,(i*i*i+11*i*i+17*i)%13))
    {
      std::cout<<"remove "<<i<<std::endl;
      bool success=a1->remove(i);
      if(success!=(s0.find(i)!=s0.end()))
        std::cout<<"error find rmove"<<i<<std::endl;
      s0.erase(i);

    }
    for(int i=0;i<100;i+=std::max(1,(i*i+11*i)%7))
    {
        if(a1->find(i)!=(s0.find(i)!=s0.end()))
            std::cout<<"error find "<<i<<" "<<a1->find(i)<<" "<<(s0.find(i)!=s0.end())<<std::endl;
    }
    std::cout<<"main end"<<std::endl;
}

