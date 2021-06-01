// 随机跳表的类
# ifndef SKIPLIST_HPP
# define SKIPLIST_HPP



template<typename Vtype>
struct skipListNode
{
    Vtype element;
    skipListNode* nxt=nullptr;
    skipListNode* down=nullptr;
};




template<
    typename Vtype,
    const std::remove_reference_t<Vtype>& min_obj,
    const std::remove_reference_t<Vtype>& max_obj,
    class allocator=myAllocator<std::remove_reference_t<Vtype>>,
    int pool_size=100,
    int criteria=10
    >
class skipList
{
    using plainVtype=std::remove_reference_t<Vtype>;
    using NodeType=skipListNode<plainVtype>;

    int layer=0;
    std::vector<NodeType*> list;
    allocator& the_allocator=*(new allocator(pool_size,criteria));
    std::vector<NodeType*> tmp_pos;
    
    /**
     * 找到目标元素的前序的方法
     * 并且还要将可能的插入位置提前保存
     * 从而才能使得复杂度为O(logN)
     */ 
    int find_pre(const plainVtype& element,const int keep_from_layer) noexcept
    {
        int count_layer=0;
        tmp_pos.reserve(keep_last_layers);
        NodeType* now=list.back();
        NodeType* last;

        while(now!=nullptr && count_layer<keep_from_layer)
        {
            // 查找一行
            while(now->element<element)
            {                
                last=now;
                now=now->nxt;
            }
            count_layer++;
            // 否则直接找下一层
            now=now->down;
        }

        int count=0;
        while(now!=nullptr)
        {
            // 查找一行
            while(now->element<element)
            {                
                last=now;
                now=now->nxt;
            }
            tmp_pos[count++]=last;
            // 否则直接找下一层
            now=now->down;
        }
        return count;
    }

    /**
     * 找到目标元素的前序的方法
     * 并且还要将可能的插入位置提前保存
     * 从而才能使得复杂度为O(logN)
     */ 
    int find_true_pre(const plainVtype& element) noexcept
    {
        int count=0;
        tmp_pos.reserve(keep_last_layers);
        NodeType* now=list.back();
        NodeType* last;

        while(now!=nullptr)
        {
            // 查找一行
            while(now->element<element)
            {                
                last=now;
                now=now->nxt;
            }
            if(now->element==element)
                tmp_pos[count++]=last;
            // 否则直接找下一层
            now=now->down;
        }
        return count;
    }


public:
    /**
     * 查找某个元素是否存在的方法
     * 返回bool值代表是否存在
     */ 
    bool find(const plainVtype& element) noexcept
    {
        NodeType* now=list.back();
        while(now!=nullptr)
        {
            // 查找一行
            while(now->element<element)
            {                
                now=now->nxt;
            }
            // 找到,则直接返回true
            if(now->element==element)
                return true;
            // 否则直接找下一层
            now=now->down;
        }
        return false;
    }

    /**
     * 从表中删除掉某一个元素的方法
     * 返回值代表是否成功删除(不存在的元素无法删除)
     */
    bool remove(const plainVtype& element) noexcept
    {
        int num=find_true_pre(element);
        for(int i=0;i<num;i++)
        {
            tmp_pos[i]->nxt=tmp_pos[i]->nxt->nxt;
        }
        allocator.free_alloc(tmp_pos[num-1],num);
        return num!=0;
    }

    /**
     * 向表中插入元素的方法
     * 使用左值引用
     */ 
    bool insert(plainVtype& element,int insertLayer)
    {
        int layer_to_insert=find_pre(element,std::max(0,layer-insertLayer+1));
        // 如果要insert的层数大于当前层数:
        if(in_layer>layer)
        {

        }

    }

    /**
     * 向表中插入元素
     * 使用右值引用
     */
    bool insert(plainVtype&& element,int insertLayer)
    {

    }

    /**
     * 向表中插入元素的方法
     * 使用左值引用
     */ 
    bool insert(plainVtype& element)
    {

    }

    /**
     * 向表中插入元素
     * 使用右值引用
     */
    bool insert(plainVtype&& element)
    {

    }

    skipList()
    {
        NodeType* first=the_allocator.alloc();
        NodeType* next=the_allocator.alloc();
        first->nxt=next;
        first->element=min;
        next->element=max;
        list.push_back(first);
    }
    


    ~skipList()
    {
        delete &the_allocator;
    }

    

};


# endif