#ifndef _BITMAP_H_
#define _BITMAP_H_

#include "Common/Allocator.h"
#include "String.h"
#include "Common/UninitializedFunctions.h"

#include <cstdint>
#include <iostream>
#include <stdexcept>

namespace TinySTL
{
    // bitmap会将N上调至8的倍数
    // class of bitmap
    template <size_t N>
    class bitmap
    {
    public:
        typedef allocator<uint8_t> dataAllocator;

    private:
        uint8_t *start_;
        uint8_t *finish_;
        const size_t size_;        // 总的bit数
        const size_t sizeOfUINT8_; // 占用多少个uint8_t
        enum EAlign
        {
            ALIGN = 8
        };

    public:
        bitmap();
        // Return the number of bits that have been set
        size_t count() const;
        size_t size() const { return size_; }
        // Return whether a bit is set;
        bool test(size_t pos) const;
        // Return Whether any of the bits is set
        bool any() const;
        // Return Whether none of the bits is set
        bool none() const;
        // Return Whether all of the bits are set
        bool all() const;

        bitmap &set();
        bitmap &set(size_t pos, bool value = true);
        bitmap &reset();
        bitmap &reset(size_t pos);
        bitmap &flip();
        bitmap &flip(size_t pos);

        string to_string() const;

        template <size_t N1>
        friend std::ostream &operator<<(std::ostream &os, const bitmap<N1> &bm);

    private:
        size_t roundUp8(size_t bytes);
        void setNthInInt8(uint8_t &i, size_t nth, bool newVal);
        // uint8_t getMask(uint8_t i, size_t nth) const { return (i & (i << nth)); }
        uint8_t getMask(uint8_t i, size_t nth) const
        {
            return (i & (1 << nth));
        }

        // 将第n个位置转换为其在第几个uint8_t中？
        size_t getNth(size_t n) const { return (n / 8); }
        // 将第n个位置转化为其在第N个uint8_t的第几个bit上
        size_t getMth(size_t n) const { return (n % EAlign::ALIGN); }
        void allocateAndFillN(size_t n, uint8_t val);
        void THROW(size_t n) const;
    }; // end of bitmap
}

#include "Bitmap.impl.h"

#endif