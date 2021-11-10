#include <iostream>
#include "functions.h"

using namespace std;

namespace Chapter6
{
    /*
        Notes:
        1. 函数的形参如果为空有两种写法 void func(), void func(void), 后一种是为了和C语言兼容
        2. 函数的返回类型不能是数组或者函数类型，但可以是指向数组或者函数的指针
        3. 函数声明的三要素（返回类型，函数名和形参类型），甚至不需要形参的名字。
           这三要素描述了函数的接口，也称为函数原型(function prototype)
        4. 参数传递一样有引用传递和值传递的概念，区别就在于实参和形参是否是两个独立的对象
     */

    //函数里面的局部静态对象
    size_t count_calls()
    {
        static size_t count = 0;
        return ++count;
    }

    void Demo1()
    {
        for (size_t i = 0; i < 10; ++i)
            cout << count_calls() << endl;
    }

    //值传递
    void func1(int val)
    {
        val -= 1;
    }

    //C语言中经常传递指针类型的形参来访问函数外部的对象，但是C++中建议使用引用类型的形参替代指针
    void reset(int *ip)
    {
        *ip = 0;   //改变指针ip所指对象的值
        ip = 0;    //改变ip本身的地址，即改变了局部拷贝，实参地址未被改变
    }

    void Demo2()
    {
        int i = 42;
        cout << "i = " << i << endl;
        func1(i);
        cout << "i = " << i << endl; //i并未被改变

        printf("Address of i: 0x%p \n", &i);
        reset(&i); 
        cout << "i = " << i << endl;     //i = 0, 但是 &i 并未改变
        printf("Address of i: 0x%p \n", &i);
    }

    //引用传递, 好处如下
    //  1. 引用类型的形参避免传入参数时，对大对象的拷贝，影响性能
    //  2. 引用类型的形参还可以作为除了函数返回值之外的另一种类型的返回值
    void reset(int &ri)
    {
        ri = 0;
    }

    void Demo3()
    {
        int i = 42;
        reset(i);
        cout << i << endl;
    }

    void fcn(const int i) {}
    //void fcn(int i) {} //compile error, 仅仅只有const关键字的不同不能形成两个不同的函数签名

    //当形参的类型关键字比较多时，比如又是const又是引用的，一眼看上去可能比较复杂
    //但是形参的初始化方式其实和变量的初始化方式是一样的
    //在不需要改变形参值的情况下，要尽量使用常量引用
    // 1. 常量引用可以接受常量或者非常量的实参以及字面值，而非常量引用只能接受实例化了的非常量变量
    // 2. 常量引用避免函数体内错误的修改参数值
    void fakeFunc(const int &i) { }
    void Demo4()
    {
        int i = 42;
        fakeFunc(i);  //it's ok, 因为 const int &ri = i 是合法的
        fakeFunc(5);  //it's ok, 因为 const int &ri = 5 是合法的
        const int j = 66;
        fakeFunc(j);  //it's ok, 因为 const int &ri = j 是合法的
    }

    //数组形参
    //因为数组具有如下两个性质：1. 数组不允许拷贝，2. 使用数组时通常会将其转换成指针
    //所以当数组作为一个形参来传递时，通常也是传递一个指向数组首元素的指针
    //如下3种定义方式
    void func_with_array_param_1(const int* p) { }
    void func_with_array_param_2(const int p[]) { }
    void func_with_array_param_3(const int p[10]) { } //10表示我们期望的数组长度，但实际传进来的并不一定，没关系

    void Demo5()
    {
        int i = 5;
        func_with_array_param_1(&i);    //it's ok
        func_with_array_param_2(&i);    //it's ok
        func_with_array_param_3(&i);    //it's ok

        int arr[10] = {0};
        func_with_array_param_1(arr);    //it's ok
        func_with_array_param_2(arr);    //it's ok
        func_with_array_param_3(arr);    //it's ok
    }

    //数组作为形参时，因为函数并不知道数组的确切尺寸，所以一般需要额外提供一些信息，主要有以下三种方法
    //1. 使用标记指定数组长度, 传递的是一个C风格字符串，默认最后一个字符为空字符串，可以作为控制条件返回false
    void print(const char *cp)
    {
        if (!cp)
            return;
        while (*cp)
        {
            cout << *cp << endl;
            cp++;
        }
    }

    //2. 传递指向数组首元素和尾后元素的指针
    void print(const int *beg, const int *end)
    {
        while (beg != end)
        {
            cout << *beg << endl;
            beg++;
        }
    }

    //3. 显示传递一个数组大小的形参
    void print(const int ia[], size_t size)
    {
        for(int i = 0; i < size; i++)
        {
            cout << ia[i] << endl;
        }
    }

    void Demo6()
    {
        print("C++");

        int arr[5] = {1, 2, 3, 4, 5};
        print(begin(arr), end(arr));
        print(arr, end(arr) - begin(arr));
    }

    //int main(int argc, char *argv[])
    //第一个代表参数个数，第二个代表参数数组，每一个参数都是一个C风格字符串
    //也可以写成 int main(int argc, char **argv)

    //含有可变形参的函数
    //1. 如果所有的实参类型都相同，可以传递一个名为 initializer_list 的标准库类型，相当于 List<T> in C#
    void error_msg(initializer_list<string> list)
    {
        for (auto beg = list.begin(); beg != list.end(); beg++)
            cout << *beg << endl;
    }

    void Demo7()
    {
        error_msg({"Function X", "expected ", "actual"}); //直接用花括号括起来传递一个序列
    }

    //2. 可以使用一个可变参数模板，具体Chapter 16讲
    //3. 还有一种特殊的形参类型(省略符), 这个一般只用于和C函数交互的接口程序，不是万不得已不要这么写
    //   省略符形参应该仅仅用于C和C++通用的类型，大多数类类型的对象在传递给省略符形参时都无法正确拷贝
    //   e.g. void foo(...)

    //函数的返回值，这个机制与初始化一个变量或者形参是完全一样的
    //1. 返回值拷贝, 如下函数所示，返回的要么是word的拷贝，要么是临时变量 (word + ending) 的拷贝
    string make_plural(size_t ctr, const string &word, const string &ending)
    {
        return (ctr > 1) ? word + ending : word;
    }

    //2. 返回引用，但是注意千万不要返回局部对象的引用或指针
    const string &shorterString(const string &s1, const string &s2)
    {
        return s1.size() < s2.size() ? s1 : s2;
    }

    void Demo8()
    {
        string s1 = "Hello";
        string s2 = "Mike";
        const string &s3 = shorterString(s1, s2);

        cout << s3 << endl;
    }

    //调用一个返回引用的函数得到左值，特别是，我们能为返回类型是非常量饮用的函数的结果赋值
    char &get_val(string &str, string::size_type index)
    {
        return str[index];
    }

    void Demo9()
    {
        string s("some value");
        cout << s << endl;
        get_val(s, 0) = 'S'; //函数调用作为左值使用
        cout << s << endl; 

        //shorterString("hi", "bye") = "x"; //compile error, 不可对常量引用赋值
    }

    //递归调用
    int factorial(int val)
    {
        if (val > 1)
            return factorial(val - 1) * val;
        return 1;  // 0! = 1
    }

    void Demo10()
    {
        cout << "5! = " << factorial(5) << endl;
    }

    //返回数组指针的函数
    //因为数组不能被拷贝，所以函数不能返回数组，不过函数可以返回数组的指针或者引用
    //有以下几种方式来声明这种函数

    //1. 使用类型别名
    typedef int arrT[10];
    //或者
    using arrT2 = int[10]; 

    int egArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    arrT* func_return_array_pointer_1(const int& incremental) 
    {
        for (auto &i: egArray)
            i += incremental;
        return &egArray;
    }

    //2. 最原始的方法，直接声明
    int (*func_return_array_pointer_2(const int& incremental))[10]
    {
        for (auto &i: egArray)
            i += incremental;
        return &egArray;
    }

    //3. C++11, 使用尾置返回类型 (trailing return type)，对于返回类型很复杂的函数很有效
    auto func_return_array_pointer_3(const int& incremental) -> int (*)[10]
    {
        for (auto &i: egArray)
            i += incremental;
        return &egArray;
    }

    //4. 使用decltype
    decltype(egArray) *func_return_array_pointer_4(const int& incremental)
    {
        for (auto &i: egArray)
            i += incremental;
        return &egArray;
    }

    void Demo11()
    {
        arrT* arr = func_return_array_pointer_1(3);
        for (int &i: *arr)
            cout << i << ",";
        cout << endl;

        int (*arr2)[10] = func_return_array_pointer_2(3);
        for (int &i: *arr2)
            cout << i << ",";
        cout << endl;

        int (*arr3)[10] = func_return_array_pointer_3(3);
        for (int &i: *arr3)
            cout << i << ",";
        cout << endl;

        decltype(egArray) *arr4 = func_return_array_pointer_4(3);
        for (int &i: *arr4)
            cout << i << ",";
        cout << endl; 
    }

    //关于函数重载
    //1. 仅仅只有返回类型不同时，无法构成重载
    void func_overload(int i);
    //int func_overload(int i); //compile error

    //constexpr函数：函数的返回值类型及所有的形参类型都必须是字面值类型
    //内联函数和constexpr函数通常都定义在头文件中
    //constexpr函数并不总是返回常量表达式

    //如何禁用所有的assert语句？只要定义NDEBUG就好了(#define NDEBUG)

    //函数指针
    //1. 函数指针指向的是函数而非对象
    //2. 函数的类型由它的返回类型和形参类型共同决定，与函数名和形参名无关
    
    //函数本身
    bool lengthCompare(const string &s1, const string &s2)
    {
        return s1.length() < s2.length();
    }

    //那么函数类型为 bool(const string &, const string &);
    //如何声明一个指向该函数的指针：bool (*pf)(const string &, const string &)
    void Demo12()
    {
        bool (*pf)(const string &, const string &);  //声明函数指针，还未初始化
        pf = lengthCompare;  //直接将函数名字赋给pf即可
        pf = &lengthCompare; //与上面的是一个意思

        bool b1 = pf("hello", "func");   //使用的时候不必解引用
        bool b2 = (*pf)("hello", "func");//实在要先解引用也行，都一样
    }

    //函数指针作为形参
    void UseBigger(const string& s1, const string& s2, bool (*pf)(const string &, const string &)) {}
    //或者省略掉括号和星号
    void UseBigger2(const string& s1, const string& s2, bool pf(const string &, const string &)) {}

    //上面的类型太复杂，使用typedef和decltype简化名称
    typedef bool (*FuncP)(const string &, const string &);
    typedef decltype(lengthCompare) *FuncP2;
    //那么用在形参里面
    void UseBigger3(const string& s1, const string& s2, FuncP) {}
    void UseBigger4(const string& s1, const string& s2, FuncP2) {}
}