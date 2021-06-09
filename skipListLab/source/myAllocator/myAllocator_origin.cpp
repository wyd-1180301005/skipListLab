# ifndef MYALLOCATOR_ORIGIN_CPP
# define MYALLOCATOR_ORIGIN_CPP

# include "myAllocator.hpp"

    /**
     * 将一小块内存放置在mem_memo中
     */
    template<typename NodeType> 
    void myAllocator<NodeType>::add_memo(NodeType* st,const int size) noexcept
    {
        int pos=size/criteria;
        const size_t size_now=mem_memo.size();
        if(pos+1>size_now)
            for(int i=0;i<pos-size_now+1;i++)
                mem_memo.emplace_back();
        mem_memo[pos].emplace_front(st,size);
        # ifndef  DISABLE_DEBUG_INTERFACE
        # ifdef VERBOSE_DEBUG
        std::cout<<"add_memo "<<size<<" "<<st<<std::endl;
        # endif
        # endif
    } 


    /**
     * 从mem_memo处申请一块内存
     * 返回nullptr说明没有这样的空闲内存快
     */
    template<typename NodeType> 
    NodeType* myAllocator<NodeType>::recycle(const int size)
    {
        int pos=size/criteria;
        const size_t size_now=mem_memo.size();
        // 不存在这样的空闲空间
        if(size_now<=pos)
            return nullptr;

        memo_list::iterator it1;
        for(int i=pos;i<size_now && i-pos<=max_traverse;i++)
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
                    # ifndef  DISABLE_DEBUG_INTERFACE
                    # ifdef VERBOSE_DEBUG
                        std::cout<<"recycle block "<<size<<" "<<pt<<std::endl;
                    # endif
                    # endif
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
    myAllocator<NodeType>::  myAllocator(const int pool_size,const int criteria,const int max_tra)
    {
        mem_pool_size=pool_size;
        this->criteria=criteria;
        this->max_traverse=max_tra;
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
        # ifndef  DISABLE_DEBUG_INTERFACE
        last_size=size;
        pt=res;
        # ifdef VERBOSE_DEBUG
        std::cout<<"alloc "<<size<<" "<<res<<std::endl;
        # endif
        # endif
        return res;
    }

    /**
     * 将一小块内存标记为可分配
     */
    template<typename NodeType> 
    inline void myAllocator<NodeType>::free_alloc(NodeType* st,const int size) noexcept
    {
        # ifndef  DISABLE_DEBUG_INTERFACE
        last_size_free=size;
        pt_free=st;
        # endif
        add_memo(st,size);
    }
    
    template<typename NodeType>
    myAllocator<NodeType>::~myAllocator() noexcept
    {
        // std::cerr<<"~myAllocator()"<<std::endl;
        for(int i=0;i<mem_pool.size();i++)
            delete[] mem_pool[i];
    }

# ifndef  DISABLE_DEBUG_INTERFACE

    /**
     * 获得memo中大小为blk_size的块的指针的方法
     */
    template<typename NodeType>
    NodeType* myAllocator<NodeType>::debug_get_memo(const int blk_size)
    {
        const int pos=blk_size/criteria;
        if(mem_memo.size()<=pos)
        {
            return nullptr;
        }
        memo_list & list_now=mem_memo[pos];
        memo_list::iterator it1;
        for(it1=list_now.begin();it1!=list_now.end();it1++)
        {
            int size_of_mem=(*it1).t2;
            if(size_of_mem==blk_size)
                return (*it1).t1;
        }
        return nullptr;
    }

    /**
     * 获得已经申请的内存池的个数的方法
     */
    template<typename NodeType>
    int  myAllocator<NodeType>::debug_count_pool()
    {
        return mem_pool_inuse+1;
    }

    /**
     * 获得当前mem_pool的指针的方法
     */
    template<typename NodeType>
    NodeType*  myAllocator<NodeType>::debug_get_current_pool()
    {
        return mem_pool[mem_pool_inuse];
    }

    /**
     * 获得当前正在分配的块的指针的方法
     */
    template<typename NodeType>
    NodeType*  myAllocator<NodeType>::debug_get_pos()
    {
        return mem_pool[mem_pool_inuse]+pos_using;
    }
    
#endif

# endif