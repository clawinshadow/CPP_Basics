#include <iostream>
#include <string>

#include "data_types.h"

namespace Chapter2
{

void DT_Demo1()
{
    std::string s = "你好";
    std::cout << s.length() << std::endl;
    for (auto c: s)
    {
        std::cout << sizeof(c) << " | " << (int)c << std::endl;
    }

    std::u16string s_utf16 = u"你好";
    std::cout << s_utf16.length() << std::endl;
    for (auto c: s_utf16)
    {
        std::cout << sizeof(c) << " | " << c << std::endl;
    }

    std::u32string s_utf32 = U"你好";
    std::cout << s_utf32.length() << std::endl;
    for (auto c: s_utf32)
    {
        std::cout << sizeof(c) << " | " << c << std::endl;
    }
}

}