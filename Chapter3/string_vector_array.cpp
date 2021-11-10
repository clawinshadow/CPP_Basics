#include <iostream>
//C++ STL 兼容了所有C语言的标准库，比如下面这个实际上是C语言中的ctype.h
//放在C++语言中引用该头文件的时候，就是<cctype>, 在前面加个c，去掉.h
#include <cctype>
#include <vector>
#include <cstring>
#include "string_vector_array.h"

//头文件中一般不使用using声明，因为头文件的内容会被拷贝到所有引用它的代码文件中
//那么如果头文件中使用了某个using声明，那这个名字里面的所有内容也都随着该头文件
//一起被拷贝到别的文件中去了，可能会造成某些始料未及的名字冲突
using namespace std;

namespace Chapter3 
{
    void Demo1()
    {
        //string 的几种初始化方式
        //使用等号 (=) 的方式叫拷贝初始化 (copy initialization), 编译器将等号右边的值拷贝到变量中去
        //相反，如果不使用等号，则执行的是直接初始化 (directly initialization)
        string s1;
        string s2(s1);       //directly initialization
        string s3 = s1;      //copy initialization
        string s4 = "value"; //copy initialization
        string s5("value");  //directly initialization
        string s6(10, 'c');  //directly initialization
        cout << s4 << "|" << s5 << "|" << s6 << endl;

        //string 的几种常用操作
        cout << "s1 is empty: " << s1.empty() << endl;
        cout << "s4 is empty: " << s4.empty() << endl;
        cout << "character count of s4: " << s4.size() << endl;  //不是占字节数，是字符的个数
        cout << "length of s4: " << s4.length() << endl;         //占字节数，基本上与size()是一样的
        cout << "3rd char in s4: " << s4[2] << endl;

        //size_type 一般来说是个无符号的整型，但它是机器无关的，所以一般不要用 int xx = s4.size() 
        string::size_type sz = s4.size();  
    }

    void Demo2()
    {
        //字符串相加时，必须确保加号两侧至少有一个是string，不能是两个字符串字面值直接相加
        //这个说法看起来很奇怪，难道字符串字面值的类型不是string吗？还真不是...
        //因为某些历史原因，也为了与C兼容，C++语言中的字符串字面值并不是标准库类型的string
        string s1 = "first";
        string s2 = s1 + ", second";      //it's ok
        //string s3 = "first" + ", second"; //compile error
        string s4 = s1 + ", " + "second"; //it's ok, equals to (s1 + ", ") + "second"
        //string s5 = "first" + ", " + s1;  //compile error
    }

    //对字符的一些常用操作
    void Demo3()
    {
        string s("Hello, World!!!");
        int puncCount;
        for (auto c: s)
        {
            if (ispunct(c))
                puncCount++;
        }
        cout << puncCount << " punctuations in " << "\"" << s << "\"" << endl;

        //修改字符，在for循环中使用引用
        for (auto &c: s)
        {
            c = toupper(c);
        }

        cout << s << endl;
    }

    //vector initialization
    void Demo4()
    {
        //1. copy initialization
        vector<int> v1;
        vector<int> v2 = v1;
        vector<int> v6 = {1, 2, 3};

        //2. direct initialization
        vector<int> v3(10, 1); // v3 = {1, 1, 1, ...., 1}, 10个
        
        //3. list initialization, 列表初始化
        vector<int> v4 {1, 2, 3, 4};

        //4. 值初始化
        vector<int> v5(10);     //10个int类型的默认值0， v5 = {0, 0, 0, ..., 0}, 10个

        //5. 用数组初始化
        int arr[] = {1, 2, 3, 5};
        vector<int> v7(begin(arr), end(arr));

        std::cout << v2.empty() << std::endl;
        std::cout << v4.size() << std::endl;
        v4.push_back(5);
        std::cout << v4.size() << std::endl;
    }

    //迭代器(iterator), 所有标准库的容器都可以使用迭代器，包括不是容器的string也行
    //有效的迭代器或者指向某一个元素，或者指向尾元素的下一个位置，其它情况都属于无效
    //一般来说，我们不太清楚迭代器具体是什么类型，所以一般都需要使用auto关键字
    //迭代器一般没有定义<, >操作，常用迭代器的操作：
    //1. *iter            返回迭代器iter所指向的元素的引用
    //2. iter->member     解引用iter并获取该元素的member成员
    //3. ++iter           令iter指向容器中的下一个元素
    //4. --iter           令iter指向容器中的上一个元素
    //5. iter1 == iter2   两个迭代器是否相等，即是否指向同一个元素，或者都指向尾后位置
    //6. begin(), end()   返回的是可以修改的迭代器
    //7. cbegin(), cend() 返回的是常量迭代器，不能修改它指向的元素
    //8. iter + n         往前移动n个位置
    //9. iter2 - iter1    计算中间隔了几个元素
    //push_back()等修改容器内容的操作会使迭代器失效
    void Demo5()
    {
        string s("hello, world");
        std::cout << "s is: " << s << std::endl;
        for (auto it = s.begin(); it != s.end(); ++it)
        {
            *it = toupper(*it);
        }
        cout << "s toupper is: " << s << endl;

        for (auto it = s.cbegin(); it != s.cend(); ++it)
        {
            cout << *it << endl;
            //*it = tolower(*it); //compile error
        }
    }

    //array
    void Demo6()
    {
        //initialization
        const unsigned int sz = 3;
        int a1[sz] = {0, 1, 2};
        int a2[] = {0, 1, 2};
        int a3[5] = {0, 1, 2}; // = {0, 1, 2, 0, 0}

        //对字符数组来说，有几点比较特殊
        //1. 它可以直接使用字符串字面值来初始化
        //2. 注意字符串字面值的最后还有一个空字符
        char c1[] = {'a', 'b', 'c'};
        char c2[] = "abc";  //it's ok
        //char c3[3] = "abc"; //compile error, 空间不够
        char c4[4] = "abc"; //it's ok 

        //Do not allow copy and assignment
        int a4[] = {1, 2};
        //int a5[] = a4;    //compile error

        //complex array declaration
        int *ptrs[10];   //包含十个整型指针的数组
        //int &refs[10];   //不存在元素是引用的数组
        int arr[10];
        int (*arrayPtr)[10] = &arr; //arrayPtr 是个指针，指向一个包含十个整型的数组
        int (&arrayRef)[10] = arr;  //arrayRef 是个引用，指向一个包含十个整型的数组

        //遍历数组还是for循环最好用
        for (auto i : a3)
            cout << i << endl;
    }

    //指针和数组，这两者在C++中有非常紧密的联系
    void Demo7()
    {
        //在很多用到数组名字的地方，编译器会自动将其转化为一个指向数组首元素的指针
        int arr[5] = {0, 1, 2, 3, 4};
        int* p1 = &arr[0];
        int* p2 = arr;    //这两者等价
        cout << *p1 << " | " << *p2 << endl;

        //指针也是迭代器
        ++p2;
        cout << *p2 << endl;  //指向了数组第二个元素
        int* p3 = p1 + 3;     //p3指向数组第四个元素
        cout << *p3 << endl;

        //标准库函数 begin & end
        for (int* pbegin = begin(arr); pbegin != end(arr); ++pbegin)
        {
            cout << *pbegin << endl;
        }

        //数组内置的下标运算实际上就是指针的前后移动
        int* p4 = &arr[3];  //p4已经指向第4个元素
        int n5 = p4[1];     //获取p4向后移动一位指向的第五个元素
        int n1 = p4[-3];    //此时p4向前移动3位，指向第一个元素
        cout << *p4 << "|" << n1 << "|" << n5 << endl;
    }

    //C风格字符串，尽量避免使用，很容易出错
    //就是一个char数组，以空字符'\0'结尾
    void Demo8()
    {
        //1. strlen(c1)
        char ca[] = {'C', '+', '+'};
        cout << strlen(ca) << endl; //严重错误：ca没有以空字符结尾，strlen()将再内存中一直往后寻找到空字符为止

        char ca2[] = {'C', '+', '+', '\0'};
        cout << strlen(ca2) << endl; //it's ok

        //2. strcmp(p1, p2): 
        //if p1 == p2, return 0, if p1 < p2, return negative, if p1 > p2, return positive 
        string s1 = "A string example";
        string s2 = "A different string";
        cout << (s1 > s2) << endl;   //对于string来说直接比较就可以

        char c1[] = "A string example";
        char c2[] = "A different string";
        //cout << (c1 < c2) << endl;   //毫无意义，因为比较的是两个地址
        cout << strcmp(c1, c2) << endl;

        //3. strcpy(s1, s2)
        //4. strcat(s1, s2)
        string largeStr = s1 + " " + s2;
        cout << largeStr << endl;   //对于string直接相加就可以
        
        int size = strlen(c1) + strlen(c2) + 1;
        char largeCStr[size];
        strcpy(largeCStr, c1);
        strcat(largeCStr, " ");
        strcat(largeCStr, c2);
        cout << largeCStr << endl;
    }
}