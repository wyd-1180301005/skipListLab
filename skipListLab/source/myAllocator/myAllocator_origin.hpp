# ifndef MYALLOCATOR_ORIGIN_HPP
# define MYALLOCATOR_ORIGIN_HPP

# include<vector>
# include<list>


// 判断一个类型是否是reference的方法:
template<typename T>
struct is_ref_tr{static const bool is_ref_v=false;};

template<typename T>
struct is_ref_tr<T&>{static const bool is_ref_v=true;};

template <typename T>
constexpr bool is_ref=is_ref_tr<T>::is_ref_v;

// 判断一个类型是否是指针的方法:
template<typename T>
struct is_pointer_tr{static const bool is_pointer_v=false;};

template<typename T>
struct is_pointer_tr<T*>{static const bool is_pointer_v=true;};

template <typename T>
constexpr bool is_pointer=is_pointer_tr<T>::is_pointer_v;

// 判断一个类型是否是BuiltInType的方法:(任何类型的指针/引用,都视为BuiltInType)
template <typename T>
constexpr bool is_builtin_type=is_pointer<T>||is_ref<T>||std::is_arithmetic_v<T>;

// 给类类型添加reference的方法:
template<typename T,bool isBuiltIn>
struct ref_unless_builtin_tr {using type=T&;};

template<typename T>
struct ref_unless_builtin_tr<T,true> {using type=T;};

template<typename T>
using ref_unless_builtin=typename ref_unless_builtin_tr<T,is_builtin_type<T>>::type;

template<typename T1,typename T2>
struct pair
{
    T1 t1;
    T2 t2;
    pair(const ref_unless_builtin<T1> t1,const ref_unless_builtin<T1> t2)
    {
        this->t1=t1;
        this->t2=t2;
    }
    pair(T1&& t1,T2&& t2)
    {
        this->t1=t1;
        this->t2=t2;
    }

};


template<typename NodeType>
class myAllocator
{
    using memo=pair<NodeType*,int>;
    using memo_list=std::list<pair<NodeType*,int>>;
    
    int mem_pool_size;
    int mem_pool_inuse;
    int pos_using;
    std::vector<NodeType*> mem_pool;

    int criteria=10;
    std::vector<memo_list> mem_memo;

    /**
     * 将一小块内存放置在mem_memo中
     */
    void add_memo(const NodeType* st,const int size) noexcept;

    /**
     * 从mem_memo处申请一块内存
     * 返回nullptr说明没有这样的空闲内存快
     */
    NodeType* recycle(const int size);

    /**
     * 从内存池中直接分配一小块内存,类型为NodeType*
     */ 
    NodeType* alloc(const int size);


public:

    /**
     * 构造函数,pool_size为每块内存池的大小
     */ 
    myAllocator(const int pool_size,const int criteria);

    /**
     * 申请一小块内存
     * 首先使用memo,其次再使用内存池
     */
    NodeType* apply_alloc(const int size);

    /**
     * 将一小块内存标记为可分配
     */
    inline void free_alloc(const NodeType* st,const int size) noexcept;
    
    ~myAllocator() noexcept;
};

# endif