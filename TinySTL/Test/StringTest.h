#ifndef _STRING_TEST_H__
#define _STRING_TEST_H__

#include "TestUtil.h"
#include "Detail/String.h"
#include <string>

#include <cassert>
#include <iterator>

namespace TinySTL
{
    namespace StringTest
    {
        using stdStr = std::string;
        using tsStr = TinySTL::string;
        void testCase1();

        void testAllCases();
    }
}

#endif