# ifndef MYALLOCATOR_ORIGIN_CPP
# define MYALLOCATOR_ORIGIN_CPP

# include "myAllocator.hpp"

    /**
     * 将一小块内存放置在mem_memo中
     */
    template<typename NodeType> 
    void myAllocator<NodeType>::add_memo(const NodeType* st,const int size) noexcept
    {
        int pos=size/10;
        int size_now=mem_memo.size();
        for(int i=size_now-1;i<=pos;i++)
            mem_memo.emplace_back();
        mem_memo[pos].emplace_front(st,size);
    } 


    /**
     * 从mem_memo处申请一块内存
     * 返回nullptr说明没有这样的空闲内存快
     */
    template<typename NodeType> 
    NodeType* myAllocator<NodeType>::recycle(const int size)
    {
        int pos=size/10;
        int size_now=mem_memo.size();
        // 不存在这样的空闲空间
        if(size_now<=pos)
            return nullptr;

        memo_list::iterator it1;
        for(int i=pos;i<size_now;i++)
        {
            memo_list& list_now=mem_memo[i];
            for(it1=list_now.begin();it1!=list_now.end();++it1)
            {
                int size_free=(*it1).t2;
                if(size_free>=size)
                {
                    NodeType* pt=(*it1).t1;
                    list_now.erase(it1);
                    if(size_free>size)
                        add_memo(pt+size,size_free-size);
                    // std::cerr<<"recycle new block "<<std::endl;
                    return pt;
                }
            }
        }
        return nullptr;
    }

    /**
     * 从内存池中直接分配一小块内存,类型为NodeType*
     */
    template<typename NodeType> 
    NodeType* myAllocator<NodeType>::alloc(const int size)
    {
        // 如果分配的内存大于每个池子最大的大小,则修改内存池的大小
        if(size>mem_pool_size)
        {
            // 将当前的不足以分配的大小直接放入memo中
            add_memo(mem_pool[mem_pool_inuse]+pos_using,mem_pool_size-pos_using);
            // std::cerr<<"alloc and resize new block"<<std::endl;
            mem_pool_size+=size;
            pos_using=0;
            mem_pool_inuse+=1;
            mem_pool.emplace_back(new NodeType[mem_pool_size]);
        }
        // 没有空闲空间,则进行再分配
        if(pos_using+size>mem_pool_size)
        {
            // std::cerr<<"alloc new block"<<std::endl;
            // 将当前的不足以分配的大小直接放入memo中
            add_memo(mem_pool[mem_pool_inuse]+pos_using,mem_pool_size-pos_using);
            pos_using=0;
            mem_pool_inuse+=1;
            mem_pool.emplace_back(new NodeType[mem_pool_size]);
        }
        NodeType* res=mem_pool[mem_pool_inuse]+pos_using;
        pos_using+=size;
        return res;
    }

    /**
     * 构造函数,pool_size为每块内存池的初始大小
     */
    template<typename NodeType> 
    myAllocator<NodeType>::  myAllocator(const int pool_size,const int criteria)
    {
        mem_pool_size=pool_size;
        this->criteria=criteria;
        mem_pool_inuse=0;
        pos_using=0;
        mem_pool.emplace_back(new NodeType[pool_size]);
    }

    /**
     * 申请一小块内存
     * 首先使用memo,其次再使用内存池
     */
    template<typename NodeType>
    NodeType* myAllocator<NodeType>::apply_alloc(const int size)
    {
        NodeType* res=recycle(size);
        if(res==nullptr)
            res=alloc(size);
        return res;
    }

    /**
     * 将一小块内存标记为可分配
     */
    template<typename NodeType> 
    inline void myAllocator<NodeType>::free_alloc(const NodeType* st,const int size) noexcept
    {
        add_memo(st,size);
    }
    
    template<typename NodeType>
    myAllocator<NodeType>::~myAllocator() noexcept
    {
        // std::cerr<<"~myAllocator()"<<std::endl;
        for(int i=0;i<mem_pool.size();i++)
            delete[] mem_pool[i];
    }

# endif