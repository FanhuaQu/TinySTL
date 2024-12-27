#ifndef _ALLOC_H__
#define _ALLOC_H__

#include <cstdlib>

namespace TinySTL
{
    /*
     * 自定义的空间配置器，以字节为单位分配
     */

    class alloc
    {
    private:
        enum EAlign
        {
            ALIGN = 8 // 小型区块的上调边界
        };
        enum EMaxBytes
        {
            MAXBYTES = 128 // 小型区块的上限，超过的由malloc分配
        };
        enum ENFreeList
        {
            NFREELIST = (EMaxBytes::MAXBYTES / EAlign::ALIGN) // freelists的个数
        };
        enum ENObjs
        {
            NOBJS = 20 // 每次增加的节点数量
        };

    private:
        // free-list的节点构造
        union obj
        {
            union obj *next;
            char client[1];
        };

        static obj *free_list[ENFreeList::NFREELIST];

    private:
        static char *start_free; // 内存池起始位置
        static char *end_free;   // 内存池结束位置
        static size_t heap_size;

    private:
        // 将bytes上调到8的倍数
        static size_t ROUND_UP(size_t bytes)
        {
            return ((bytes + EAlign::ALIGN - 1) & ~(EAlign::ALIGN - 1));
        }

        // 根据区块大小，决定去free-list的第n号节点中拿
        static size_t FREELIST_INDEX(size_t bytes)
        {
            return ((bytes + EAlign::ALIGN - 1) / EAlign::ALIGN - 1);
        }
        // 返回一个大小为n的对象，并可能加入大小为n的其他区块到free-list中?
        static void *refill(size_t n);
        // 配置一大块空间，可容纳nobjs个大小为size的区块
        static void *chunk_alloc(size_t size, size_t &nobjs);

    public:
        static void *allocate(size_t bytes);
        static void deallocate(void *ptr, size_t bytes);
        static void *reallocate(void *ptr, size_t old_sz, size_t new_sz);
    };
}

#endif