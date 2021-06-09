# include <iostream>
# include <random>
# include <typeinfo>
# include <set>
# include <windows.h>
# include <stdio.h>
# include "myAllocator.hpp"
# include "skipList.hpp"

class myClock
{
    LARGE_INTEGER freq;
    LARGE_INTEGER start_t, stop_t;
    double exe_time;

public:
    myClock()
    {
        QueryPerformanceFrequency(&freq);
    }

    void setClock()
    {
        QueryPerformanceCounter(&start_t);
    }

    double getTime()
    {
        QueryPerformanceCounter(&stop_t);
        return 1e3*(stop_t.QuadPart-start_t.QuadPart)/freq.QuadPart;
    }
};

template<typename T>
class mySetWrapper
{
    std::set<T> s0;
public:
    bool find(ref_unless_builtin<T> item)
    {
        return s0.find(item)!=s0.end();
    }

    void insert(ref_unless_builtin<T> item)
    {
        s0.insert(item);
    }

    void erase(ref_unless_builtin<T> item)
    {
        s0.erase(item);
    }


};
template<class set_class>
class set_operation
{
    std::default_random_engine* rnd;
    std::uniform_int_distribution<int>* dist;
    set_class * set0;

    int const base=100;
    int insert_ops;
    int erase_ops;
    int sum_ops;
public:

    template<typename ... Args>
    set_operation(int insert_ops,int erase_ops,int find_ops, Args ... args)
    {
        rnd=new std::default_random_engine(time(NULL));
        dist=new std::uniform_int_distribution<int> (0,base);
        sum_ops=(insert_ops+erase_ops+find_ops);
        this->insert_ops=(insert_ops*base)/sum_ops;
        this->erase_ops=this->insert_ops+(erase_ops*base)/sum_ops;
        set0=new set_class(args...);
    }
    
    void start_op()
    {
        for(int i=0;i<sum_ops;i++)
        {
            int item=(((17*i)%(sum_ops-7))*29)%(sum_ops);
            int indic=(*dist)(*rnd);
            if(indic>=insert_ops)
            {
                if(indic<=erase_ops)
                {
                    set0->erase(item);
                }
                else
                {
                    set0->find(item);
                }
            }
            else
            {
                if(set0->find(item)==false)
                    set0->insert(item);
            }
        }
    }
};

int main()
{
    std::cout<<"main start"<<std::endl;

    int num_trial;

    for(num_trial=30000;num_trial<=400000;num_trial+=30000)
    {
        std::cout<<"try "<<num_trial<<std::endl;
        int num_remove=num_trial*0.3;
        int find=num_trial*0.8;

    
        set_operation<skipList<int>> op1(num_trial,num_remove,find,1000,0.9,100,10,2);
        set_operation<mySetWrapper<int>> op2(num_trial,num_remove,find);

        myClock clock0;


        clock0.setClock();
        std::set<int> s1;
        op2.start_op();
        std::cout<<"\t"<<clock0.getTime()<<std::endl;

        clock0.setClock();
        op1.start_op();
        std::cout<<"\t"<<clock0.getTime()<<std::endl;

    }


    std::cout<<"main end"<<std::endl;
}

