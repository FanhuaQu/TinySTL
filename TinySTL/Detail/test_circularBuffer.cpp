#include "TestUtil.h"
#include "CircularBuffer.h"

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>

namespace TinySTL
{
    namespace CircularBufferTest
    {

        template <class T, size_t N>
        using tsCB = TinySTL::circular_buffer<T, N>;

        template <class T, size_t N>
        bool circular_buffer_equal(tsCB<T, N> &cb1, tsCB<T, N> cb2)
        {
            auto it1 = cb1.first(), it2 = cb2.first();
            for (; it1 != cb1.last() && it2 != cb1.last(); ++it1, ++it2)
            {
                if (*it1 != *it2)
                    return false;
            }
            return (it1 == cb1.last() && it2 == cb2.last() && (*(cb1.last()) == *(cb2.last())));
        }

        void testCase1()
        {
            tsCB<int, 10> cb1(10, 1);
            for (auto i = 0; i != 10; ++i)
                assert(cb1[i] == 1);

            int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
            tsCB<int, 10> cb2(std::begin(arr), std::end(arr));
            for (auto i = 0; i != 10; ++i)
                assert(cb2[i] == i);

            auto cb3(cb2);
            assert(circular_buffer_equal(cb2, cb3));

            auto cb4(std::move(cb2)); // cb2 clear
            assert(circular_buffer_equal(cb3, cb4));

            auto cb5 = cb3;
            assert(circular_buffer_equal(cb3, cb5));

            auto cb6 = std::move(cb3); // cb3 clear
            assert(circular_buffer_equal(cb5, cb6));
        }
        void testCase2()
        {
            tsCB<int, 2> cb(1);
            assert(cb.size() == 1);
            cb.pop_front();
            assert(!cb.full());
            assert(cb.size() == 0);
            assert(cb.empty());

            cb.push_back(1), cb.push_back(2);
            assert(cb.full());
            assert(!cb.empty());
            assert(cb.size() == 2);
        }
        void testCase3()
        {
            tsCB<std::string, 3> cb(3);
            cb[0] = "one", cb[1] = "two", cb[2] = "three";

            assert(*(cb.first()) == "one" && *(cb.last()) == "three");

            assert(cb.front() == "one" && cb.back() == "three");
        }
        void testCase4()
        {
            tsCB<std::string, 3> cb(1);
            assert(cb.front() == std::string());

            cb.push_back("zxh");
            cb.push_back("jwl");
            assert(cb.back() == "jwl");
            cb.pop_front();
            assert(cb.front() == "zxh");
        }
        void testCase5()
        {
            tsCB<int, 3> cb1(3), cb2(3);
            assert(cb1 == cb2);
            assert(!(cb1 != cb2));

            cb1[0] = -1;
            assert(!(cb1 == cb2));
            assert(cb1 != cb2);
        }
        void testCase6()
        {
            std::string arr[] = {"1", "2", "3"};
            tsCB<std::string, 3> cb(std::begin(arr), std::end(arr));

            std::ostringstream os;
            os << cb;
            assert(os.str() == "(1, 2, 3)");
        }

        void testAllCases()
        {
            testCase1();
            testCase2();
            testCase3();
            testCase4();
            testCase5();
            testCase6();
        }
    }
}

int main()
{

    TinySTL::CircularBufferTest::testAllCases();
    std::cout << "CircularBufferTest passed!" << std::endl;
}