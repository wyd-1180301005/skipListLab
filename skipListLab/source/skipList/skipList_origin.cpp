# ifndef SKIPLIST_ORIGIN_CPP
# define SKIPLIST_ORIGIN_CPP
# define skipList_template(type)                    \
    template<                                       \
    typename Vtype,                                 \
    class allocator>                                \
    type skipList<Vtype,allocator>::

# include "skipList_origin.hpp"


    /**
     * 重新申请头部指针:
     * 达到两倍layer的大小
     */ 
    skipList_template(void)
    renew_head(int num_new)
    {
        int num_new_alloc=std::max(2*layer,num_new+1);
        NodeType* new_list=the_allocator->apply_alloc(num_new_alloc);

        // 进行拷贝
        for(int i=0;i<=layer;i++)
            (new_list+i)->nxt=(the_list+i)->nxt;
        // 其余进行初始化
        for(int i=layer+1;i<num_new_alloc;i++)
            (new_list+i)->nxt=nullptr;
        // 将原本的head节点free
        the_allocator->free_alloc(the_list,capacity);
        // 更新capacity
        capacity=num_new_alloc;
        // 更新list
        the_list=new_list;
    }

    /**
     * 找到目标元素的前序的方法(后面可能并无目标元素)
     * 并且还要将可能的插入位置提前保存
     * 从而才能使得复杂度为O(logN)
     */
    skipList_template(int)
    find_pre(ref_type element,const int keep_last_layers) noexcept
    {
        int count_layer=0;
        int const keep_from_layer=layer-keep_last_layers;
        if(tmp_pos.size()<keep_last_layers)
            tmp_pos.resize(keep_last_layers);
        // now指针初始为skip_list的最顶层
        NodeType* now=the_list+layer;
        NodeType* next;

        // 0 1 2 3 4 5
        while(count_layer<=keep_from_layer)
        {
            // 查找一行
            next=now->nxt;
            // 当停止时,下一个位置要么是空,要么就大于等于element
            while(next!=nullptr && is_smaller(next->element,element))
            {                
                now=next;
                next=next->nxt;
            }
            count_layer++;
            // 指针减一,实际上是将指针移动到下一层
            now=now-1;
        }

        int count=0;
        while(count_layer<=layer)
        {
            // 查找一行
            next=now->nxt;
            // 当停止时,下一个位置要么是空,要么就大于等于element
            while(next!=nullptr && is_smaller(next->element,element))
            {                
                now=next;
                next=next->nxt;
            }
            tmp_pos[count++]=now;
            count_layer++;
            // 否则直接找下一层
            now=now-1;
        }
        return count;
    }

    /**
     * 找到目标元素的前序的方法
     * 并且还要将可能的插入位置提前保存
     * 从而才能使得复杂度为O(logN)
     */
    skipList_template(int)
    find_true_pre(ref_type element) noexcept
    {
        int count=0;
        int count_layer=0;
        if(layer+1>tmp_pos.size())
            tmp_pos.resize(layer+1);
        NodeType* now=the_list+layer;
        NodeType* next;

        while(count_layer<=layer)
        {
            // 查找一行
            next=now->nxt;
            // 当停止时,下一个位置要么是空,要么就大于等于element
            while(next!=nullptr && is_smaller(next->element,element))
            {                
                now=next;
                next=next->nxt;
            }
            if(next!=nullptr && equals(next->element,element))
                tmp_pos[count++]=now;
            count_layer++;
            // 转到下一层
            now=now-1;
        }
        return count;
    }

    /**
     * 查找某个元素是否存在的方法
     * 返回bool值代表是否存在
     */
    skipList_template(bool)
    find(ref_type element) noexcept
    {
        int count_layer=0;
        NodeType* now=the_list+layer;
        NodeType* next;

        while(count_layer<=layer)
        {
            // 查找一行
            next=now->nxt;
            // 当停止时,下一个位置要么是空,要么就大于等于element
            while(next!=nullptr && is_smaller(next->element,element))
            {                
                now=next;
                next=next->nxt;
            }
            count_layer++;
            // 找到,则直接返回true
            if(next!=nullptr && equals(next->element,element))
                return true;
            // 否则直接找下一层
            now=now-1;
        }
        return false;
    }

    /**
     * 从表中删除掉某一个元素的方法
     * 返回值代表是否成功删除(不存在的元素无法删除)
     */
    skipList_template(bool)
    remove(ref_type element) noexcept
    {
        int num=find_true_pre(element);
        // 不存在该元素,返回false
        if(num==0)
            return false;

        NodeType* st=tmp_pos[num-1]->nxt;
        for(int i=0;i<num;i++)
        {
            tmp_pos[i]->nxt=tmp_pos[i]->nxt->nxt;
        }        

        the_allocator->free_alloc(st,num);
        return true;
    }

    /**
     * 向表中插入元素的方法
     * 使用左值引用
     */
    skipList_template(void)
    insert(ref_type element,int insertLayer)
    {
        // 如果要insert的层数大于当前层数:
        if(insertLayer>layer)
        {
            if(insertLayer>capacity)
            {
                renew_head(insertLayer);
            }
            layer=insertLayer;
        }

        int const layer_to_insert=find_pre(element,insertLayer+1);
        NodeType* st=the_allocator->apply_alloc(layer_to_insert)+layer_to_insert-1;
        NodeType* tmp;
        for(int i=0;i<layer_to_insert;i++)
        {
            tmp=tmp_pos[i]->nxt;
            tmp_pos[i]->nxt=(st-i);
            (st-i)->nxt=tmp;
            (st-i)->element=element;
        }
    }
# endif