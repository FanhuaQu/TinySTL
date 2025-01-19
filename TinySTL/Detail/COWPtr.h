#ifndef _COWPTR_H_
#define _COWPTR_H_

#include "Memory.h"
// Copy On Write Pointer
namespace TinySTL
{
    template <class T>
    class cow_ptr;

    namespace Detail
    {
        template <class T>
        class proxy     // cow_ptr的代理类，处理对指向对象的访问和修改
        {
        public:
            explicit proxy(cow_ptr<T> *const cp) : cp_(cp) {}
            proxy(const proxy<T> &) = default;
            proxy &operator=(const proxy<T> &) = default;

            const T &operator*() const;
            T &operator*();
            const T *operator->() const;
            T *operator->();
            cow_ptr<T> &operator=(const T &val);
            operator T() const;

        private:
            cow_ptr<T> *cp_;
        };
    }

    // 未能完全模拟原生指针操作，只供参考，详情见单元测试
    template <class T>
    class cow_ptr
    {
    public:
        typedef T element_type;

    private:
        template <class U>  // 修改模板参数名称以避免冲突
        using proxy = Detail::proxy<U>;

    public:
        explicit cow_ptr(T *p = nullptr);
        template <class D>
        cow_ptr(T *p, D d);

        cow_ptr(const cow_ptr &cp);
        cow_ptr &operator=(const cow_ptr &cp);

        const proxy<element_type> operator*() const;
        proxy<element_type> operator*();
        const proxy<element_type> operator->() const;
        proxy<element_type> operator->();

        element_type *get();
        const element_type *get() const;

        operator bool() const;

    private:
        shared_ptr<element_type> ptr_;

    public:
        template <class T1, class T2>
        friend bool operator==(const cow_ptr<T1> &cp1, const cow_ptr<T2> &cp2);
        template <class U>
        friend bool operator==(const cow_ptr<U> &cp, nullptr_t p);
        template <class U>
        friend bool operator==(nullptr_t p, const cow_ptr<U> &cp);
        template <class T1, class T2>
        friend bool operator!=(const cow_ptr<T1> &cp1, const cow_ptr<T2> &cp2);
        template <class U>
        friend bool operator!=(const cow_ptr<U> &cp, nullptr_t p);
        template <class U>
        friend bool operator!=(nullptr_t p, const cow_ptr<U> &cp);

        template <class U>  // 修改模板参数名称以避免冲突
        friend class Detail::proxy;
    };

    template <class T, class... Args>
    cow_ptr<T> make_cow(Args... args)
    {
        return cow_ptr<T>(new T(std::forward<Args>(args)...));  // 完美转发
    }
}

#include "COWPtr.impl.h"

#endif