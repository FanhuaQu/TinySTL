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
    void string::resize(size_t n)
    {
        resize(n, value_type());
    }
    void string::resize(size_t n, char c)
    {
        if (n < size())
        {
            dataAllocator::destroy(start_ + n, finish_); // 析构掉n后面的
            finish_ = start_ + n;
        }
        else if (n > size() && n <= capacity())
        {
            auto lengthOfInsert = n - size();
            finish_ = TinySTL::uninitialized_fill_n(finish_, lengthOfInsert, c);
        }
        else if (n > capacity())
        {
            auto lengthOfInsert = n - size();
            iterator newStart = dataAllocator::allocate(getNewCapacity(lengthOfInsert)); // 分配新的内存
            iterator newFinish = TinySTL::uninitialized_copy(begin(), end(), newStart);
            newFinish = TinySTL::uninitialized_fill_n(newFinish, lengthOfInsert, c);

            destroyAndDeallocate(); // 释放原有的内存
            start_ = newStart;
            finish_ = newFinish;
            endOfStorage_ = start_ + n;
        }
    }

    void string::reserve(size_t n)
    {
        if (n < capacity())
        {
            return;
        }
        iterator newStart = dataAllocator::allocate(n);
        iterator newFinish = TinySTL::uninitialized_copy(begin(), end(), newStart);
        destroyAndDeallocate();
        start_ = newStart;
        finish_ = newFinish;
        endOfStorage_ = start_ + n;
    }
    string &string::insert(size_t pos, const string &str)
    {
        insert(start_ + pos, str.begin(), str.end());
    }
    string &string::insert(size_t pos, const string &str, size_t subpos, size_t sublen)
    {
        sublen = changeVarWhenEuqalNPOS(sublen, str.size(), subpos);
        insert(begin() + pos, str.begin() + subpos, str.begin() + subpos + sublen);
        return *this;
    }
    string &string::insert(size_t pos, const char *s)
    {
        insert(begin() + pos, s, s + strlen(s));
        return *this;
    }
    string &string::insert(size_t pos, const char *s, size_t n)
    {
        insert(begin() + pos, s, s + n);
        return *this;
    }
    string::iterator string::insert_aux_filln(iterator p, size_t n, value_type c)
    { // 指定p位置插入n个字符， 返回插入新字符之后的迭代器
        auto newCapacity = getNewCapacity(n);
        iterator newStart = dataAllocator::allocate(newCapacity);              // 分配新的内存
        iterator newFinish = TinySTL::uninitialized_copy(start_, p, newStart); // 复制start_到p的内容到新的内存空间
        newFinish = TinySTL::uninitialized_fill_n(newFinish, n, c);            // 填充n个字符c
        auto res = newFinish;
        newFinish = TinySTL::uninitialized_copy(p, finish_, newFinish); // 复制p到finish_的内容

        destroyAndDeallocate(); // 销毁旧的内存空间并且释放
        start_ = newStart;
        finish_ = newFinish;
        endOfStorage_ = start_ + newCapacity;
        return res;
    }

    string &string::insert(size_t pos, size_t n, char c)
    {
        insert(begin() + pos, n, c);
        return *this;
    }
    string::iterator string::insert(iterator p, size_t n, char c)
    {
        auto lengthOfLeft = capacity() - size();
        if (n <= lengthOfLeft)
        {
            for (iterator it = finish_ - 1; it >= p; --it)
            {
                *(it + n) = *(it);
            }
            TinySTL::uninitialized_fill_n(p, n, c);
            finish_ += n;
            return (p + n);
        }
        else
        {
            return insert_aux_filln(p, n, c);
        }
    }
    string::iterator string::insert(iterator p, char c)
    {
        return insert(p, 1, c);
    }
    string &string::operator+=(const string &str)
    {
        insert(size(), str);
        return *this;
    }
    string &string::operator+=(const char *s)
    {
        insert(size(), s);
        return *this;
    }
    string &string::operator+=(char c)
    {
        insert(end(), c);
        return *this;
    }
    string &string::append(const string &str)
    {
        (*this) += str;
        return *this;
    }
    string &string::append(const string &str, size_t subpos, size_t sublen)
    {
        sublen = changeVarWhenEuqalNPOS(sublen, str.size(), subpos);
        insert(size(), str, subpos, sublen);
        return *this;
    }
    string &string::append(const char *s)
    {
        (*this) += s;
        return *this;
    }
    string &string::append(const char *s, size_t n)
    {
        insert(size(), s, n);
        return *this;
    }
    string &string::append(size_t n, char c)
    {
        insert(end(), n, c);
        return *this;
    }
    string::iterator string::erase(iterator first, iterator last)
    {
        size_t lengthOfMove = finish_ - last;
        for (auto i = 0; i != lengthOfMove; ++i)
        {
            *(first + i) = *(last + i);
        }
        dataAllocator::destroy(first + lengthOfMove, finish_);
        finish_ = first + lengthOfMove;
        return first;
    }
    string &string::erase(size_t pos, size_t len)
    {
        len = changeVarWhenEuqalNPOS(len, size(), pos);
        erase(begin() + pos, begin() + pos + len);
        return *this;
    }
    string::iterator string::erase(iterator p)
    {
        return erase(p, p + 1);
    }
    string &string::replace(size_t pos, size_t len, const string &str)
    {
        return replace(begin() + pos, begin() + pos + len, str.begin(), str.end());
    }
    string &string::replace(iterator i1, iterator i2, const string &str)
    {
        return replace(i1, i2, str.begin(), str.end());
    }
    string &string::replace(size_t pos, size_t len, const string &str, size_t subpos, size_t sublen)
    {
        sublen = changeVarWhenEuqalNPOS(sublen, str.size(), subpos);
        return replace(begin() + pos, begin() + pos + len, str.begin() + subpos, str.begin() + subpos + sublen);
    }
    string &string::replace(size_t pos, size_t len, const char *s)
    {
        return replace(begin() + pos, begin() + pos + len, s, s + strlen(s));
    }
    string &string::replace(iterator i1, iterator i2, const char *s)
    {
        return replace(i1, i2, s, s + strlen(s));
    }
    string &string::replace(iterator i1, iterator i2, size_t n, char c)
    {
        auto ptr = erase(i1, i2);
        insert(ptr, n, c);
        return *this;
    }
    string &string::replace(size_t pos, size_t len, const char *s, size_t n)
    {
        return replace(begin() + pos, begin() + pos + len, s, s + n);
    }
    string &string::replace(iterator i1, iterator i2, const char *s, size_t n)
    {
        return replace(i1, i2, s, s + n);
    }
    string &string::replace(size_t pos, size_t len, size_t n, char c)
    {
        return replace(begin() + pos, begin() + pos + len, n, c);
    }
    size_t string::find_aux(const_iterator cit, size_t pos, size_t lengthOfS, size_t cond) const
    {
        size_t i, j;
        for (i = pos; i != cond; ++i)
        {
            for (j = 0; j != lengthOfS; ++j)
            {
                if (*(begin() + i + j) != cit[j])
                {
                    break;
                }
            }
            if (j == lengthOfS)
            {
                return i;
            }
        }
        return npos;
    }
    size_t string::find(const char *s, size_t pos, size_t n) const
    { // 在区间pos~pos+n中查找子串s
        size_t lengthOfS = strlen(s);
        return find_aux(s, pos, lengthOfS, pos + n);
    }
    size_t string::find(const string &str, size_t pos) const
    {
        size_t lengthOfS = str.size();
        if (size() - pos < lengthOfS)
        {
            return npos;
        }
        return find_aux(str.cbegin(), pos, lengthOfS, size());
    }
    size_t string::find(const char *s, size_t pos) const
    {
        return find(s, pos, strlen(s));
    }
    size_t string::find(char c, size_t pos) const
    {
        for (auto cit = cbegin() + pos; cit != cend(); ++cit)
        {
            if (*cit == c)
                return cit - cbegin();
        }
        return npos;
    }
    size_t string::rfind(char c, size_t pos) const
    {
        pos = changeVarWhenEuqalNPOS(pos, size(), 1);
        for (auto cit = cbegin() + pos; cit >= cbegin(); --cit)
        {
            if (*cit == c)
            {
                return cit - cbegin();
            }
        }
        return npos;
    }
    size_t string::rfind_aux(const_iterator cit, size_t pos, size_t lengthOfS, int cond) const{
        int i, j;
        for (i = pos + lengthOfS; i>= cond; --i){
            for (j = 0; j != lengthOfS; ++j){
                if(*(begin() + j+i) != cit[i]){
                    break;
                }

            }
            if(j == lengthOfS){
                return i;
            }
        }
        return npos;
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