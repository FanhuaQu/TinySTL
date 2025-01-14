#ifndef _CONSTRUCT_H__
#define _CONSTRUCT_H__

#include <new>

#include "TypeTraits.h"

namespace TinySTL
{
    template <class T1, class T2>
    inline void construct(T1 *ptr1, const T2 &value)
    {
        new (ptr1) T1(value);       // palcement new，在已分配的内存上构造对象
    }

    template <class T>
    inline void destroy(T *ptr)
    {
        ptr->~T();
    }

    // 前向迭代器
    template <class ForwardIterator>
    inline void _destroy(ForwardIterator first, ForwardIterator last, _true_type) {}        // 用于POD类型的析构函数

    template <class ForwardIterator>
    inline void _destroy(ForwardIterator first, ForwardIterator last, _false_type)          // 
    {
        for (; first != last; ++first)
        {
            destroy(&*first);
        }
    }

    template <class ForwardIterator>
    inline void destroy(ForwardIterator first, ForwardIterator last)
    {
        typedef typename _type_traits<ForwardIterator>::is_POD_type is_POD_type;
        _destroy(first, last, is_POD_type());
    }
}

#endif