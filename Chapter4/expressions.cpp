#include <iostream>
#include <bitset>
#include "expressions.h"

using namespace std;

namespace Chapter4
{
    //关于左值和右值，这是针对于表达式这个概念的，这两个概念原本是来自于C语言，用于帮助记忆：
    //左值可以位于赋值语句的左侧，右值则不能
    //但是在C++中，他们的含义发生了一些变化，现在可以先简单的归纳如下：
    //当一个对象被用作右值时，用的是对象的值（内容），而被用作左值时，用的是对象的身份（在内存中的位置）
    //具体的应用以后再说
    //-----------------------------------------
    //关于优先级的简单概括：一元运算符最高，乘法除法次之，然后是加法和减法，括号无视任何优先级
    
    int func1() { return 1; }
    int func2() { return 2; }
    void Demo1()
    {
        //大多数运算符是没有指定求值顺序的
        int a = func1() * func2(); //先算func1 还是 func2 并不确定
        //所以对于这些没有指定求值顺序的运算符来说，如果使用它们的表达式修改了同一个对象
        //将会引发错误并产生未定义的行为
        int i = 0;
        cout << i << "|" << ++i << endl;   //未定义的，不知道是先算i还是先++i

        //赋值运算符满足右结合律
        int val1, val2;
        val1 = val2 = 0;

        string str1, str2;
        str1 = str2 = "ok"; 
    }

    //算术运算符 +，-，*，/，%
    void Demo2()
    {
        //+, - 可以用作一元运算符，也可以用作二元运算符
        int a = 42;
        cout << "a = " << a << ", -a = " << -a << endl;
        int b = -5;
        cout << "b = " << b << ", +b = " << +b << endl;

        int c = a + b;
        cout << "a + b = " << c << endl;

        //整数相除的结果依然是整数，剔除小数部分
        int d = 21 / 6;
        cout << "21 / 6 = " << d << endl;
        double e = 21 / 6;
        cout << "double 21 / 6 = " << e << endl;   //依然是3
        double f = 21.0 / 6;
        cout << "double 21.0 / 6 = " << f << endl; // 3.5

        //取模运算的两边必须都是整数类型
        int mod = 21 % 5;
        cout << "mod 21 % 5 = " << mod << endl;
        //int mod2 = 21 % 3.14; //compile error

        //对于int -> bool来说，所有非0的值都为true，包括负数
    }

    void Demo3()
    {
        //递增递减运算符的两种写法
        //前置版本：++i, i本身加1，然后该表达式返回的结果也是加1之后的i
        //后置版本：i++, i本身加1，但是该表达式返回的结果依然是之前的 i
        int i = 0;
        int j = ++i; 
        cout << "i = " << i << ", j = " << j << endl;
        j = i++;
        cout << "i = " << i << ", j = " << j << endl;
    }

    //位运算符
    void Demo4()
    {
        unsigned char bits = 167;
        std::bitset<8> x(bits);
        cout << "binary of " << (int)bits << ": " << x << endl; //2进制
        cout << hex << "0x" << (int)bits << endl;  //16进制
        cout << oct << "0" << (int)bits << endl;   //8进制
        cout << dec << (int)bits << endl; //十进制

        // ~ 按位求反
        // 得出来的结果可能会非常大，这是因为在使用位运算符时，所有小整形会被先提升到大整型
        // 比如下面的unsigned char, 就被提升为了int，然后高位全部补零后再执行求反操作
        cout << "~ operator: " << (int)~bits << endl;
        std::bitset<32> x2(~bits);
        cout << "binary of ~167: " << x2 << endl;

        // << 左移
        int bits_left_1 = bits << 1; 
        cout << (int)bits << " | " << bits_left_1 << endl;  // = bits * 2

        int a = 3;
        int b = a << 1;
        cout << b << endl;

        //右移 >>
        int bits_right_6 = bits >> 6; //10
        cout << bits_right_6 << endl;

        //&: 位与，|：位或，^: 异或，比较的两个位，有且只有一个为1，最后得出的结果才是1
    }

    //sizeof运算符返回一个表达式或者一个类型名字所占的字节数
    void Demo5()
    {
        char a = 'a';
        cout << sizeof(a) << "|" << sizeof(char) << endl; //可以用于变量，也可以直接使用类型名字

        int b = 4;
        int &rb = b;
        cout << sizeof(rb) << endl;  //引用类型的sizeof返回被引用对象所占空间的大小

        int *pb = &b;
        cout << "sizeof a pointer of int: " << sizeof(pb) << endl; //指针的sizeof返回的就是指针本身所占空间的大小（64位机器上是8个字节）
        cout << sizeof(*pb) << endl; //解引用指针后的sizeof返回所指对象所占空间的大小

        int arr[5] = {1, 2, 3, 4, 5};
        cout << sizeof(arr) << endl; //对数组执行sizeof返回的是整个数组所占空间的大小 4 * 5 = 20
        //计算数组的长度
        constexpr size_t sz = sizeof(arr) / sizeof(*arr);
        cout << sz << endl;
        //但是这个准则不适用于string这种不定长的元素
        string s[3] = {"hello", "world", "!!"};
        cout << sizeof(s) << endl; //输出72，而按理说这个string数组应该只占用了48字节的空间
        int sz2 = s[0].length() + s[1].length() + s[2].length();
        cout << sz2 * sizeof(char) << endl; 

        //对string和vector执行sizeof(), 得出的是其固定部分所占用的空间，不是实际所占的空间
        //比如下面的输出是24，表明这个时候s2其实已经分配了24个字节的空间，虽然现在只占用了20个字节
        string s2("hello");
        cout << sizeof(s2) << endl; 
    }

    //const_cast，主要用于匹配重载函数的上下文
    void Demo6()
    {
        int a = 5;
        const int *cpa = &a;
        //*cpa = 6; //compile error

        int *pa = const_cast<int *>(cpa); //去掉底层const，cast the const away
        *pa = 6;   //此时就可以修改了
        cout << a << endl; 

        //但是如果原来的变量就是常量，那么此时去掉const限制后修改常量，就会变成未定义的行为
        const int b = 42;
        const int *cpb = &b;

        int *pb = const_cast<int *>(cpb);
        *pb = 444;
        cout << b << endl; //不会报错，但一般来说也改不了原来的常量值
    }

    //略过 static_cast, reinterpret_cast, dynamic_cast 有单独的博客详细讲解这几个
}