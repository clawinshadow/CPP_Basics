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

    auto f = 3.14159f;  // suffix f/F represents a float type
    std::cout << "sizeof(f) = " << sizeof(f) << std::endl;
    auto d = 3.14159;   // no suffix represents a default double type
    std::cout << "sizeof(d) = " << sizeof(d) << std::endl;
    auto ld = 3.14159L; // suffix l/L represents a long double type
    std::cout << "sizeof(ld) = " << sizeof(ld) << std::endl;

    auto f_e = 3.14159e5; //科学计数法来表示一个浮点数, e/E 作为指数标记
    std::cout << "f_e = " << f_e << std::endl;

    auto c = 'a';       //default char type with no prefix
    std::cout << "sizeof(c) = " << sizeof(c) << std::endl;
    auto wide_c = L'a'; // L prefix represents a wide character, wchar_t
    std::cout << "sizeof(wide_c) = " << sizeof(wide_c) << std::endl;
    auto u16_c = u'a';  // u prefix represents a char16_t, utf-16 character
    std::cout << "sizeof(u16_c) = " << sizeof(u16_c) << std::endl;
    auto u32_c = U'a';  // U prefix represents a char32_t, utf-32 character
    std::cout << "sizeof(u32_c) = " << sizeof(u32_c) << std::endl;
}

void ReferencesDemo()
{
    int i = 42;
    int &ref_i = i; //ref_i is a reference of i
    std::cout << "ref_i = " << ref_i << std::endl;
    
    ref_i = 0;
    std::cout << "i = " << i << std::endl;

    // int &ref_i2;    //compile error: reference must be initialized

    // int &ref_i3 = 1024; //compiler error: reference cannot bind to a literal value

    // double d = 3.1415
    // int &ref_d = d; //compiler error: type of reference must be the same as the binding object

    int &ref_i4 = ref_i; //reference can be copied;
    std::cout << "ref_i4 = " << ref_i4 << std::endl;

    //int &&ref_ref_i = ref_i; //compile error: cannot define a reference refer to another reference
}

void PointersDemo()
{
    int val = 42;
    int *p_val = &val; //get the memory address of val
    std::cout << "The value of p_val point to: " << *p_val << std::endl; //dereference p_val

    int i = 5;
    int *pi = &i; //pointer declaration
    std::cout << std::hex << "The value of pi (the address of i) = " << pi << std::endl;

    int *p; //don't need to be initialized
    std::cout << std::hex << "The value of uninitialized p: " << p << std::endl; //a random memory address
    std::cout << "The value p point to: " << (int)*p << std::endl; //probably crashed here

    int *p_null = 0;
    p_null = NULL;
    p_null = nullptr; // all the same to initialize a null pointer
    if (!p_null)
        std::cout << "p_null is a null pointer" << std::endl;

    int i2 = 6;
    pi = &i2;
    std::cout << "now p2 point to i2: " << *pi << std::endl;

    //pointers comparation
    int *p1 = nullptr;
    int *p2 = nullptr;
    std::cout << std::boolalpha << "p1 == p2: " << (p1 == p2) << std::endl;

    int a = 5;
    p1 = &a;
    p2 = &a;
    std::cout << std::boolalpha << "p1 == p2: " << (p1 == p2) << std::endl;

    //reference to a pointer
    int b = 1;
    int *p3 = &b;
    int *&rp3 = p3; //read from right to left
    std::cout << "*rp3 = " << *rp3 << std::endl;
}

void VoidPointersDemo()
{
    //void pointers
    double d = 3.14159;
    double *pd = &d;
    void *vp = pd;
    std::cout << "*vp = " << *(double *)vp << std::endl;
}

int GetBufSize() { return 42; }

void ConstDemo()
{
    const int BUF_SIZE = 42;
    //BUF_SIZE = 42; //error: const object cannot be modified
    std::cout << BUF_SIZE << std::endl;

    const int BUF_SIZE2 = GetBufSize();
    //const int BUF_SIZE3; //error: uninitialized const

    int i = BUF_SIZE;
    i = 0; //i can be modified after copy from the const BUF_SIZE
    std::cout << "i = " << i << std::endl;
    std::cout << "BUF_SIZE = " << BUF_SIZE << std::endl;

    const int i2 = i;
    //i2 = 42;//error: i2 cannot be modified
}

void ConstReferenceDemo()
{
    const int ci = 42;
    const int &r1 = ci; //reference to const variable ci
    //r1 = 0;       //error: cannot modify the value of a const reference
    //int &r2 = ci; //error: non const reference to a const variable

    int i = 42;
    const int &r3 = i; //it's ok, const reference can be bind to a nonconst variable
    //r3 = 0; //error: cannot modify i by its const reference
}

void ConstPointersDemo()
{
    //a plain pointer point to const object
    const int i = 42;
    //int *pi = &i; //error: nonconst pointer point to a const object
    
    const int *cpi = &i;
    std::cout << "*cpi = " << *cpi << std::endl;
    //*cpi = 0; //error: pi point to a const object
    int j = 10;
    cpi = &j; // it's ok, pointer itself can be changed
    std::cout << "*cpi = " << *cpi << std::endl;

    // a const pointer
    int val = 42;
    int *const pval = &val;
    std::cout << "*pval = " << *pval << std::endl;
    *pval = 1;
    std::cout << "val = " << val << std::endl;
    //pval = nullptr; //error: pointer itself cannot be changed

    //int *const p; //error: must be initialized

    //a const pointer point to a const object
    const int k = 42;
    const int *const ptr = &k;
    //*ptr = 0;      // error
    //ptr = nullptr; // error
}

int get_size() { return 1; }

void ConstExpressionsDemo()
{
    const int max_files = 20;        // max_files is a constant expression 
    const int limit = max_files + 1; // limit is a constant expression 
    int staff_size = 27;             // staff_size is not a constant expression 
    const int sz = get_size();       // sz is not a constant expression
}

constexpr int GetSize() {return 1; }

int i = 0;
void ConstexprDemo()
{
    constexpr int mf = 20;         // 20 is a constant expression 
    constexpr int limit = mf + 1;  // mf + 1 is a constant expression 
    constexpr int sz2 = GetSize(); // ok only if size is a constexpr function

    constexpr int &ri = i;  //it's ok, i is a global variable
    int j = 0;
    //constexpr int &rj = j;  //error: j is a local variable

    constexpr int *pi = &i; // it's ok, the address of i is fixed at compile time.
    //pi = nullptr; //error: pi is a const pointer cannot be changed anymore
}

void BlockScopesDemo()
{
    {
        int i = 0; // scope of outer i begins
        ++i;       // outer i is in scope
        {
            int i = 1; // scope of inner i begins,
                       // scope of outer i pauses
            i = 42;    // inner i is in scope
            std::cout << "inner i = " << i << std::endl;
        } // block ends, scope of inner i ends,
          // scope of outer i resumes
        std::cout << "outer i = " << i << std::endl;
    } // block ends, scope of outer i ends 

    //Function scope
    goto label;
    std::cout << "This line will be passed" << std::endl;

label:
    std::cout << "jump to label" << std::endl;
}

}