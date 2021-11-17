#include <iostream>
#include <string>

#include <climits>
#include <limits>
#include <cmath>
#include <cstdlib>

#include "data_types.h"

namespace Chapter2
{

void StringEncodingDemo()
{
    //default string: utf-8 encoding 
    std::string s = "你好";
    std::cout << "chars count of using std::string: " << s.length() << std::endl;
    std::cout << "sizeof char: " << sizeof(s[0]) << std::endl;

    std::cout << "chars (ordinals #hex): ";
    for (auto c: s)
    {
        unsigned char uc = static_cast<unsigned char>(c);
        std::cout << " " << std::hex << static_cast<unsigned int>(uc);
    }
    std::cout << "\n--------------------\n";

    //wide string: probably utf-32 encoding 
    std::wstring s_wide = L"你好";
    std::cout << "chars count of using std::wstring: " << s_wide.length() << std::endl;
    std::cout << "sizeof(wchar_t): " << sizeof(s_wide[0]) << std::endl;
    std::cout << "chars (ordinals #hex): ";
    for (auto c: s_wide)
    {
        std::cout << " " << static_cast<unsigned int>(c);
    }
    std::cout << "\n--------------------\n";

    //u16string: UTF-16 encoding
    std::u16string s_utf16 = u"你好";
    std::cout << "chars count of using std::u16string: " << s_utf16.length() << std::endl;
    std::cout << "sizeof(char16_t): " << sizeof(s_utf16[0]) << std::endl;
    std::cout << "chars (ordinals #hex): ";
    for (auto c: s_utf16)
    {
        std::cout << " " << static_cast<unsigned short>(c);
    }
    std::cout << "\n--------------------\n";

    //u32string: UTF-32 encoding
    std::u32string s_utf32 = U"你好";
    std::cout << "chars count of using std::u32string: " << s_utf32.length() << std::endl;
    std::cout << "sizeof(char32_t): " << sizeof(s_utf32[0]) << std::endl;
    std::cout << "chars (ordinals #hex): ";
    for (auto c: s_utf32)
    {
        std::cout << " " << static_cast<unsigned int>(c);
    }
    std::cout << "\n--------------------\n" << std::dec; //restore to decimal format
}

void SizeofDataTypesDemo()
{
    std::cout << "sizeof(short): " << sizeof(short) << std::endl;
    //Range [-32768, 32767]
    std::cout << "Maximum value of short: " << SHRT_MAX << std::endl; //Macro defined in limits.h
    std::cout << "Maximum value from numeric limits: " << std::numeric_limits<short>::max() << std::endl; //Since C++11

    std::cout << "sizeof(unsigned short): " << sizeof(unsigned short) << std::endl;
    std::cout << "Maximum value of unsigned short: " << USHRT_MAX << std::endl; //Macro defined in stdint.h
    std::cout << "Maximum value from numeric limits: " << std::numeric_limits<unsigned short>::max() << std::endl;

    float pos_inf = 1.0/0.0;
    double neg_inf = 1.0/-0.0;
    std::cout << "pos_inf: " << pos_inf << std::endl;
    std::cout << "neg_inf: " << neg_inf << std::endl;
}

void FloatPointSpecialValuesDemo()
{
    double zero = 0.0;
    double neg_zero = -0.0;      //Negative zero
    //Infinity values
    std::cout << "positive infinity: " <<  1.0 / zero << std::endl;
    std::cout << "negative infinity: " <<  1.0 / neg_zero << std::endl;
    //use std::isinf() to check infinity values since C++11, include <cmath>
    std::cout << std::boolalpha << "isinf(INFINITY): " << std::isinf(INFINITY) << std::endl
              << "isinf(-INFINITY): " << std::isinf(-INFINITY) << std::endl
              << "isinf(INFINITY - 1): " << std::isinf(INFINITY - 1) << std::endl
              << "isinf(INFINITY + 1): " << std::isinf(INFINITY + 1) << std::endl
              << "isinf(INFINITY * 2): " << std::isinf(INFINITY * 2) << std::endl
              << "INFINITY == INFINITY: " << (INFINITY == INFINITY) << std::endl;
    //NaN values
    std::cout << std::boolalpha
              << "NAN == NAN: " << (NAN == NAN) << '\n'
              << "isnan(NaN): " << std::isnan(NAN) << '\n'
              << "isnan(NaN + 1): " << std::isnan(NAN + 1) << '\n'
              << "isnan(Inf): " << std::isnan(INFINITY) << '\n'
              << "isnan(Inf + 1): " << std::isnan(INFINITY + 1) << '\n'
              << "isnan(Inf + Inf): " << std::isnan(INFINITY + INFINITY) << '\n'
              << "isnan(Inf - Inf): " << std::isnan(INFINITY - INFINITY) << '\n';
    char* end;
    std::cout << std::boolalpha
              << "isnan(strtod(\"NaN\")): " << std::isnan(std::strtod("NaN", &end)) << std::endl;
}

void LiteralsDemo()
{
    auto i = 10;       //decimal-literal
    std::cout << "sizeof(i) = " << sizeof(i) << std::endl;

    auto i_l = 10l;    // suffix l/L means signed long int
    std::cout << "sizeof(i_l) = " << sizeof(i_l) << std::endl;
    auto i_ll = 10LL;  // suffix LL/ll means signed long long int
    std::cout << "sizeof(i_LL) = " << sizeof(i_ll) << std::endl;
    auto i_u = -10u;   // suffix u means unsigned, -10 definitely overflow
    std::cout << "i_u = " << i_u << std::endl;

    auto i_b = 0b1010; //binary-literal
    auto i_o = 012;    //octal-literal
    auto i_h = 0xA;    //hexademical-literal
    std::cout << "i i_b i_o i_h: " << i << " " 
                                   << i_b << " " 
                                   << i_o << " " 
                                   << i_h << " " << std::endl;
}

}