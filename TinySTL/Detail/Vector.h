#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "Common/Allocator.h"
#include "Common/Algorithm.h"
#include "Common/Iterator.h"
#include "Common/ReverseIterator.h"
#include "Common/UninitializedFunctions.h"

#include <algorithm>
#include <type_traits>

namespace TinySTL
{
    /******vector****** */
    template <class T, class Alloc = allocator<T>>
    class vector
    {
    private:
        T *start_;
        T *finish_;
        T *endOfStorage_;

        typedef Alloc dataAllocator;

    public:
        typedef T value_type;
        typedef T *iterator;
        typedef const T *const_iterator;
        typedef reverse_iterator_t<T *> reverse_iterator;
        typedef reverse_iterator_t<const T *> const_reverse_iterator;
        typedef iterator pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

    public:
        vector() : start_(0), finish_(0), endOfStorage_(0) {}
        explicit vector(const size_type n);
        vector(const size_type n, const value_type &value);
        template <class InputIterator>
        vector(InputIterator first, InputIterator last);
        vector(const vector &v);
        vector(vector &&v);
        vector &operator=(const vector &v);
        vector &operator=(vector &&v);
        ~vector();

        // compare
        bool operator==(const vector &v) const;
        bool operator!=(const vector &v) const;

        // iterator
        iterator begin() { return start_; }
        const_iterator begin() const { return start_; }
        const_iterator cbegin() const { return start_; }
        iterator end() { return (finish_); }
        const_iterator end() const { return (finish_); }
        const_iterator cend() const { return (finish_); }
        reverse_iterator rbegin() { return reverse_iterator(finish_); }
        const_reverse_iterator crbegin() const { return const_reverse_iterator(finish_); }
        reverse_iterator rend() { return reverse_iterator(start_); }
        const_reverse_iterator crend() const { return const_reverse_iterator(start_); }

        // container
        difference_type size() const { return finish_ - start_; }
        difference_type capacity() const { return endOfStorage_ - start_; }
        bool empty() const { return start_ == finish_; }
        void resize(size_type n, value_type val = value_type());
        void reserve(size_type n);
        void shrink_to_fit();

        // 访问元素相关
        reference operator[](const difference_type i) { return *(begin() + i); }
        const_reference operator[](const difference_type i) const { return *(cbegin() + i); }
        reference front() { return *(begin()); }
        reference back() { return *(end() - 1); }
        pointer data() { return start_; }

        // 修改容器
        void clear();
        void swap(vector &v);
        void push_back(const value_type &value);
        void pop_back();
        iterator insert(iterator pos, const value_type &val);
        void insert(iterator pos, const size_type &n, const value_type &val);
        template <class InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last);
        iterator erase(iterator pos);
        iterator erase(iterator first, iterator last);

        // 空间配置器相关
        // Alloc get_allocator() { return dataAllocator; }

    private:
        void destroyAndDeallocateAll();
        void allocateAndFillN(const size_type n, const value_type &value);
        template <class InputIterator>
        void allocateAndCopy(InputIterator first, InputIterator last);

        template <class InputIterator>
        void vector_aux(InputIterator first, InputIterator last, std::false_type);
        template <class Integer>
        void vector_aux(Integer n, const value_type &value, std::true_type);
        template <class InputIterator>
        void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
        template <class Integer>
        void insert_aux(iterator position, Integer n, const value_type &value, std::true_type);
        template <class InputIterator>
        void reallocateAndCopy(iterator position, InputIterator first, InputIterator last);
        void reallocateAndFillN(iterator position, const size_type &n, const value_type &val);
        size_type getNewCapacity(size_type len) const;

    public:
        template <class T1, class Alloc1>
        friend bool operator==(const vector<T1, Alloc1> &v1, const vector<T1, Alloc1> &v2);
        template <class T1, class Alloc1>
        friend bool operator!=(const vector<T1, Alloc1> &v1, const vector<T1, Alloc1> &v2);
    }; // class of vector

    // 包含实现文件

}
#include "Vector.impl.h"

#endif