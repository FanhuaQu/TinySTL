#include "StringTest.h"

#include <fstream>

namespace TinySTL
{
    namespace StringTest
    {
        void testCase1()
        {
            const char *ptr = "hello world";
            stdStr s1(ptr);
            tsStr s2(ptr);
            assert(TinySTL::Test::container_equal(s1, s2));

            stdStr s5(10, 'z');
            tsStr s6(10, 'z');
            assert(TinySTL::Test::container_equal(s5, s6));

            char arr[] = "zouxiaohang love cpp";
            stdStr s7(std::begin(arr), std::end(arr));
            tsStr s8(std::begin(arr), std::end(arr));
            assert(TinySTL::Test::container_equal(s7, s8));
        }

        void testAllCases()
        {
            testCase1();
        }

    } // namespace

} // namespace
