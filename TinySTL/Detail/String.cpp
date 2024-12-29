#include "../String.h"

#include <iostream>

namespace TinySTL
{
    const size_t string::npos;

    string::string(size_t n, char c)
    {
        allocateAndFillN(n, c);
    }
    string::string(const char *s)
    {
        allocateAndCopy(s, s + strlen(s));
    }
    string::string(const char *s, size_t n)
    {
        allocateAndCopy(s, s + n);
    }
    string::string(const string &str)
    {
        allocateAndCopy(str.start_, str.finish_);
    }
    string::string(string &&str)
    {
        moveData(str);
    }
    string::string(const string &str, size_t pos, size_t len)
    {
        len = changeVarWhenEuqalNPOS(len, str.size(), pos);
        allocateAndCopy(str.start_ + pos, str.start_ + pos + len);
    }
    string::~string()
    {
        destroyAndDeallocate();
    }
    string &string::operator=(const string &str)
    {
        if (this != &str)
        {
            destroyAndDeallocate();
            allocateAndCopy(str.start_, str.finish_);
        }
        return *this;
    }
    string &string::operator=(string &&str)
    {
        if (this != &str)
        {
            moveData(str);
        }
        return *this;
    }
    string &string::operator=(const char *s)
    {
        destroyAndDeallocate();
        allocateAndCopy(s, s + strlen(s));
        return *this;
    }
    string &string::operator=(char c)
    {
        destroyAndDeallocate();
        allocateAndFillN(1, c);
        return *this;
    }

    void string::allocateAndFillN(size_t n, char c)
    {
        start_ = dataAllocator::allocate(n);
        finish_ = TinySTL::uninitialized_fill_n(start_, n, c);
        endOfStorage_ = finish_;
    }
    void string::string_aux(size_t n, char c, std::true_type)
    {
        allocateAndFillN(n, c);
    }
    void string::destroyAndDeallocate()
    {
        dataAllocator::destroy(start_, finish_);                   // 调用析构函数
        dataAllocator::deallocate(start_, endOfStorage_ - start_); // 回收内存
    }

}