#ifndef _LIST_H_
#define _LIST_H_

#include "Common/Algorithm.h"
#include "Common/Iterator.h"
#include "Common/ReverseIterator.h"
#include "Common/UninitializedFunctions.h"

#include <type_traits>

namespace TinySTL
{
    template <class T>
    class list;
    namespace Detail
    {
        // the class of node
        template <class T>
        struct node
        {
            T data;
            node *prev;
            node *next;
            list<T> *container;
            node(const T &d, node *p, node *n, list<T> *c) : data(d), prev(p), next(n), container(c) {}
            bool operator==(const node &n)
            {
                return data == n.data && prev == n.prev && next == n.next && container == n.container;
            }
        };
        // the class of list iterator
        template <class T>
        struct listIterator : public iterator<bidirectional_iterator_tag, T>
        {
            template <class U>
            friend class list;

        public:
            typedef node<T> *nodePtr;
            nodePtr p;

        public:
            explicit listIterator(nodePtr ptr = nullptr) : p(ptr) {}

            listIterator &operator++();
            listIterator operator++(int);
            listIterator &operator--();
            listIterator operator--(int);
            T &operator*() { return p->data; }
            T *operator->() { return &(operator*()); }

            template <class U>
            friend bool operator==(const listIterator<U> &lhs, const listIterator<U> &rhs);
            template <class U>
            friend bool operator!=(const listIterator<U> &lhs, const listIterator<U> &rhs);
        };
    } // end of namespace

    // the class of list
    template <class T>
    class list
    {
        template <class U>
        friend struct listIterator;

    private:
        typedef allocator<Detail::node<T>> nodeAllocator;
        typedef Detail::node<T> *nodePtr;

    public:
        typedef T value_type;
        typedef Detail::listIterator<T> iterator;
        typedef Detail::listIterator<const T> const_iterator;
        typedef reverse_iterator_t<iterator> reverse_iterator;
        typedef T &reference;
        typedef size_t size_type;

    private:
        iterator head;
        iterator tail;

    public:
        list();
         list(size_type n, const value_type &val = value_type()); // explicit
        template <class InputIterator>
        list(InputIterator first, InputIterator last);
        list(const list &l);
        list &operator=(const list &l);
        ~list();

        bool empty() const { return head == tail; }
        size_type size() const;
        reference front() { return (head.p->data); }
        reference back() { return (tail.p->prev->data); }

        void push_front(const value_type &val);
        void pop_front();
        void push_back(const value_type &val);
        void pop_back();

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        reverse_iterator rbegin();
        reverse_iterator rend();

        iterator insert(iterator position, const value_type &val);
        template <class InputIterator>
        void insert(iterator position, size_type n, const value_type &val);
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last);
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
        void swap(list &x);
        void clear();
        void splice(iterator position, list &x);
        void splice(iterator position, list &x, iterator i);
        void splice(iterator position, list &x, iterator first, iterator last);
        void remove(const value_type &val);
        template <class Predicate>
        void remove_if(Predicate pred);
        void unique();
        template <class BinaryPredicate>
        void unique(BinaryPredicate binary_pred);
        void merge(list &x);
        template <class Compare>
        void merge(list &x, Compare comp);
        void sort();
        template <class Compare>
        void sort(Compare comp);
        void reverse();

    private:
        void ctorAux(size_type n, const value_type &val, std::true_type);
        template <class InputIterator>
        void ctorAux(InputIterator first, InputIterator last, std::false_type);
        nodePtr newNode(const T &val = T());
        void deleteNode(nodePtr p);
        void insert_aux(iterator position, size_type n, const T &val, std::true_type);
        template <class InputIterator>
        void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
        const_iterator changeIteratorToConstIterator(iterator &it) const;

    public:
        template <class U>
        friend void swap(list<U> &x, list<U> &y);
        template <class U>
        friend bool operator==(const list<U> &lhs, const list<U> &rhs);
        template <class U>
        friend bool operator!=(const list<U> &lhs, const list<U> &rhs);
    }; // end of List
}

#include "List.impl.h"

#endif