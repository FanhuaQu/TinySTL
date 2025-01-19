#ifndef _REF_H_
#define _REF_H_

#include <atomic>
#include <functional>
#include <memory>

namespace TinySTL
{
    namespace Detail
    {
        // 仿函数，在释放资源时调用delete
        template <class T>
        struct _default_delete
        {
            void operator()(T *ptr)
            {
                if (ptr)
                    delete ptr;
            }
        };
        // 引用计数器
        template <class T>
        struct ref_t
        {
            using deleter_type = std::function<void(T *)>; // 删除器类型

            std::atomic<size_t> ncount_; // 线程安全的引用计数
            T *data_;                    // 指向实际数据的指针
            deleter_type deleter_;       // 删除器，默认是_default_delete

            explicit ref_t(T *p = nullptr, deleter_type pfunc = deleter_type(_default_delete<T>()))
                : ncount_(0), data_(p), deleter_(pfunc)
            {
                if (data_)
                    ncount_ = 1;
            }
            ref_t(const ref_t &) = delete; // 禁用拷贝构造函数和赋值运算符
            ref_t &operator=(const ref_t &) = delete;

            ~ref_t()
            { // 析构函数，每调用一次引用计数减小1
                --ncount_;
                if (ncount_ == 0)
                    deleter_(data_);
            }

            size_t count() const { return ncount_.load(); } // 获取当前引用计数
            T *get_data() const { return data_; }           // 获取指向数据的指针

            ref_t &operator++()
            {
                ++ncount_;
                return *this;
            }
            ref_t operator++(int)
            {
                auto t = *this;
                ++*this;
                return t;
            }
            ref_t &operator--()
            {
                --ncount_;
                return *this;
            }
            ref_t operator--(int)
            {
                auto t = *this;
                --*this;
                return t;
            }
        };
        template <class T>
        bool operator==(const ref_t<T> &lhs, const ref_t<T> &rhs)
        { // 比较两个ref_t是否指向相同数据
            return lhs.get_data() == rhs.get_data();
        }
        template <class T>
        bool operator!=(const ref_t<T> &lhs, const ref_t<T> &rhs)
        {
            return !(lhs == rhs);
        }
    }
}

#endif