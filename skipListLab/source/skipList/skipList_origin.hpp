// 随机跳表的类
# ifndef SKIPLIST_ORIGIN_HPP
# define SKIPLIST_ORIGIN_HPP

# include "myAllocator.hpp"


template<typename Vtype>
struct skipListNode
{
    pointer_unless_builtin<Vtype> element;
    skipListNode* nxt=nullptr;
};


template<
    typename Vtype,
    class allocator=myAllocator<skipListNode<std::remove_reference_t<Vtype>>>
    >
class skipList
{
    using plainVtype=std::remove_reference_t<Vtype>;
    using NodeType=skipListNode<plainVtype>;
    using ref_type=pointer_unless_builtin<plainVtype>;

    int layer=0;
    int capacity=0;
    NodeType* the_list;

    allocator * the_allocator;
    std::vector<NodeType*> tmp_pos;

private:
    /**
     * 重新申请头部指针:
     * 达到两倍layer的大小
     */ 
    void renew_head(int num_new);

    /**
     * 找到目标元素的前序的方法
     * 并且还要将可能的插入位置提前保存
     * 从而才能使得复杂度为O(logN)
     */
    int find_pre(ref_type element,const int keep_from_layer) noexcept;

    /**
     * 找到目标元素的前序的方法
     * 并且还要将可能的插入位置提前保存
     * 从而才能使得复杂度为O(logN)
     */
    int find_true_pre(ref_type element) noexcept;
    
public:
    // 小于号
    _forceinline bool is_smaller(skipList<Vtype,allocator>::ref_type a,skipList<Vtype,allocator>::ref_type b)
    {
        if constexpr(is_pointer<skipList<Vtype,allocator>::ref_type>)
            return (*a)<(*b);
        else
            return a<b;
    }

    // 等于号
    _forceinline bool equals(skipList<Vtype,allocator>::ref_type a,skipList<Vtype,allocator>::ref_type b)
    {
        if constexpr(is_pointer<skipList<Vtype,allocator>::ref_type>)
            return (*a)==(*b);
        else
            return a==b;
    }

    /**
     * 查找某个元素是否存在的方法
     * 返回bool值代表是否存在
     */ 
    bool find(ref_type element) noexcept;

    /**
     * 从表中删除掉某一个元素的方法
     * 返回值代表是否成功删除(不存在的元素无法删除)
     */
    bool remove(ref_type element) noexcept;

    /**
     * 向表中插入元素的方法
     * 使用左值引用
     */ 
    void insert(ref_type element,int insertLayer);

    template<typename ... AllocArgs>
    skipList(int init_capacity,AllocArgs ... args)
    {
        the_allocator=new allocator(args ...);
        the_list=the_allocator->apply_alloc(init_capacity);
        capacity=init_capacity;
        layer=0;
    }

    # ifndef  DISABLE_DEBUG_INTERFACE 
    void print_list()
    {
        std::cout<<"st-list"<<std::endl;
        NodeType* head_st;
        NodeType* pt;
        for(int i=0;i<=layer;i++)
        {
            head_st=the_list+layer-i;
            pt=head_st->nxt;
            while (pt!=nullptr)
            {
                if constexpr (is_pointer<ref_type>)
                    std::cout<<*(pt->element)<<"\t";
                else
                    std::cout<<(pt->element)<<"\t";
                    pt=pt->nxt;
            }
            std::cout<<std::endl;
        }
        std::cout<<"ed-list"<<std::endl;
    }

    std::vector<NodeType*>& debug_findtrue_pre(int item)
    {
        find_true_pre(item);
        return tmp_pos;
    }


    allocator* debug_getallocator()
    {
        return the_allocator;
    }
    # endif

    ~skipList()
    {
        delete the_allocator;
    }


};


# endif