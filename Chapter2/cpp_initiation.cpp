#include <iostream>
#include <cstdlib>

namespace Chapter2
{
    void Demo1()
    {
        std::cout << "Come up and C++ me some time \n";
        std::cout << "You won't regret it!\n";
    }

    void Demo2()
    {
        int v1 = 0, v2 = 0;
        std::cin >> v1 >> v2;

        int min = v1 < v2 ? v1 : v2;
        int max = v1 >= v2 ? v1 : v2;

        for (int i = min; i <= max; i++)
            std::cout << i << std::endl;
    }

    //basic data type
    void Demo3()
    {
        char a = 3;
        short b = 512;
        int c = 12345678;
        long d = 1111111;
        long long e = 1111111111111111;
        std::cout << "size of char: " << sizeof(a) << std::endl;
        std::cout << "size of short: " << sizeof(b) << std::endl;
        std::cout << "size of int: " << sizeof(c) << std::endl;
        std::cout << "size of long: " << sizeof(d) << std::endl;
        std::cout << "size of long long: " << sizeof(e) << std::endl;

        char16_t f = 'f'; //16 bit Unicode char
        char32_t f2 = 'f'; //32 bit Unicode char
        std::string str = "string";
        std::cout << "size of char16_t: " << sizeof(f) << std::endl;
        std::cout << "size of char32_t: " << sizeof(f2) << std::endl; 
        
        //https://stackoverflow.com/questions/3770781/why-is-sizeofstring-32
        // Small (or Short) String Optimisation (SSO)
        //即便修改了str里面的内容，sizeof(str)依然是24，这是由编译器所决定的
        //sizeof的具体值在编译时已经确定，即便传进去的是一个instance值，它不是运行时决定的
        std::cout << "size of sample string \"string\": " << sizeof(str) << std::endl;
        std::cout << "length of sample string \"string\": " << str.length() << std::endl;
        std::cout << str.size() << std::endl;

        int *p = nullptr;
        std::cout << "size of a pointer on 64bit OS: " << sizeof(p) << std::endl;
    }

    void Demo3_Overflow()
    {
        unsigned char a = -257;
        std::cout << "a = " << (int)a << std::endl;
    }

    //prefix and suffix on literal values (字面值)
    /*
            char and string literal values
    Prefix          Implications             data type
      u            Unicode 16 char           char16_t
      U            Unicode 32 char           char32_t
      L            Wide char                 wchar
      u8           UTF-8 (only for string)   char

            Integer literal values
    Suffix          data type
    u or U          unsigned            
    l or L          long
    ll or LL        long long 

            Float literal values
    Suffix          data type
    f or F          float
    l or L          long double
    ------------------------------------------------------
    0..  -> 八进制
    0x.. -> 十六进制
     */
    void Demo4()
    {
        auto a = 32u;
        std::cout << sizeof(a) << std::endl; 
        auto b = u'a';
        std::cout << sizeof(b) << std::endl;
        auto c = U'a';
        std::cout << sizeof(c) << std::endl;
        auto d = 1223.00L;
        std::cout << sizeof(d) << std::endl;
        auto e = 1223.0;
        std::cout << sizeof(e) << std::endl;
        int i1 = 20;
        int i2 = 024;
        int i3 = 0x14;
        std::cout << i1 << i2 << i3 << std::endl;
    }

    //list initialization (C++11), 形如{}的初始化方式，叫做列表初始化
    void Demo5()
    {
        int i1 = 10;
        int i2 = {10};
        int i3{10};
        int i4(10);
        std::cout << i1 << i2 << i3 << i4 << std::endl;

        //当用于内置类型的变量时，列表初始化有一个重要特点：如果我们使用列表初始化
        //且初始值存在丢失信息的风险，则编译器将报错
        int a = 1234.5678;   //ok, just a warning
        //int a{1234.5678};  //compile error
    }

    //关于默认初始化，如果是内置类型的变量未被显示初始化的，它的值由定义的位置决定
    //如果定义在函数体外，那么默认一般都是0，如果在函数体内，那么是undefined.
    int g1;
    void Demo6()
    {
        int g2;
        std::cout << "global uninitialized g1 = " << g1 << std::endl;
        // g2 will be an undefined value
        std::cout << "unintialized variable inside function is undefined: " << g2 << std::endl;
        int g3 = g2 + 2;
        std::cout << g3 << std::endl;
    }

    //为了支持多文件的分离式编译，C++将变量的声明和定义区分开来 (declaration & definition)
    //比如下面的 val 变量定义在另一个文件 cpp_initiation_2.cpp 中，但是在这里为了使用它，需要重新声明
    //前面加上关键字 extern 即可，但是不能够写 extern int val = xxx, 只要赋值了就变成定义了
    extern int val;
    // extern int val2 = 8;
    void Demo7()
    {
        std::cout << "extern variable val = " << val << std::endl;
        //running error, duplicate symbol of val2
        // std::cout << "extern variable with definition val2 = " << val2 << std::endl;
    }

    //关于变量的作用域问题，同名的局部变量会覆盖全局变量，但不代表全局变量失效，可以用域操作符::随时获取全局变量
    //所以定义变量要尽可能的在使用前定义，不要定义在很遥远的地方，另外，函数内部不宜定义与全局变量同名的局部变量
    int reused = 42;
    void Demo8()
    {
        int unique = 0;
        std::cout << reused << " " << unique << std::endl;
        int reused = 0; // override global variable: reused
        std::cout << reused << std::endl;
        //因为我这里是在namespace Chapter2 里面定义的reused, 所以使用 Chapter2::reused来获取
        //如果在该namespace外定义 reused, 那么可以直接使用 ::reused 来获取真正的全局变量 reused
        std::cout << Chapter2::reused << std::endl;
    }

    //复合类型(compound type)是指基于其它类型定义的类型，这里先介绍两种：引用和指针
    //理论上来说，一条声明语句是由一个基本数据类型(base type)和紧随其后的一个声明符(declarator)列表组成的
    //只不过前面的简单例子中，声明符只是变量名
    //C++11中新增了一种引用，所谓的“右值引用”(rvalue reference)，后面会详细介绍这个
    //平时我们用的最多的还是左值引用 (lvalue reference)
    void Demo9()
    {
        int ival = 1024;
        int &refVal = ival;    //refVal point to ival (just another name of ival)
        //int &refval2;          //compile error: 引用必须被初始化
        //int &refval3 = refval; //引用本身不是一个对象，所以不能定义引用的引用
        //int &refval4 = 1024;   //引用只能绑定在对象上，不能绑定在一个字面值上或者某个表达式的值上面
        std::cout << "ival = " << ival << ", refVal = " << refVal << std::endl;
        refVal = 2;
        std::cout << "ival = " << ival << ", refVal = " << refVal << std::endl;
    }

    //指针 (pointer)
    //与引用的相似点：都实现了对其他对象的间接访问
    //与引用的不同之处：
    //  1. 指针本身就是一个对象，允许对指针赋值和拷贝，并且一个指针在其生命周期内可以指向不同的对象
    //  2. 指针无须在定义时赋初值
    //指针的值应该属于下面4种状态之一：
    //  1. 指向一个对象
    //  2. 指向紧邻对象所占空间的下一个位置，常见于数组
    //  3. 空指针，意味着指针没有指向任何值
    //  4. 无效指针，上述情况之外的其他值 (e.g., 在块作用域内定义而不赋值)
    void Demo10()
    {
        int ival = 42;
        int *p = &ival;
        std::cout << *p << std::endl;
        *p = 0;
        std::cout << *p << std::endl;
        //null pointer 空指针的三种写法，不是无效指针
        int *p1 = nullptr; // C++11 标准写法
        int *p2 = 0;
        int *p3 = NULL;
        //void * 指针，可用于存放任何对象的地址，但我们对该地址中是个什么类型的对象并不了解
        //标准转换应该要用到 static_cast<T *>
        double obj = 3.141;
        void *pv = &obj;
        std::cout << *((double *)pv) << std::endl;
        //虽然不能定义指向引用的指针，但可以定义指向指针的引用..
        int i = 42;
        int *pi;
        //当声明符像下面这样有多个时，按从右往左的方式读，越靠近变量的越重要
        //比如下面，最靠近变量名r的是&符号，那么表明它本质上是一个引用，其次才是一个 int * 的指针
        int *&r = pi; // r is a reference to pointer pi

        r = &i;       // then pi point to i, too
        std::cout << "i = " << i << std::endl;
        *pi = 0;
        std::cout << "i = " << i << std::endl;
    }

    //const, 对于常量的定义一般只在本代码文件内有效，所以多个不同的文件中可以有各自同名的常量
    //那么如果想要共享同一个名字的常量，则需要用 extern const .. 来同时声明和定义，见 cpp_initiation_2.cpp 
    extern const int bufSize;
    void Demo11()
    {
        std::cout << "bufSize from another file: " << Chapter2::bufSize << std::endl;

        //reference to const
        //1. initialization
        const int ci = 88;
        const int &rci = ci;   //most straight-forward initialization 
        //rci = 0;             //compile error, can't modify a const through its reference
        int i = 42;
        const int &ri = i;      //a const reference to a non-const value, it's ok
        const int &rl = 42;     //a const reference to a literal value, it's ok
        const int &re = ri * 2; //a const reference to an expression, it's ok
        std::cout << ri << ", " << rl << ", " << re << std::endl;

        //pointer to const，又称为底层const (low-level const)
        //1. initialization
        const double cd = 3.14;
        const double *pcd = &cd;  //most straight-forward 
        double d = 5.0;
        const double *pd = &d;   //a const pointer point to a non-const value, it's ok
        //虽然我们无法通过这种pointer来修改原对象的值，但指针本身并不是const，我们可以修改指针本身的值
        // *pcd = 0;   //error
        // *pd = 0;    //error
        std::cout << "*pcd = " << *pcd << std::endl;
        pcd = pd;      //it's ok
        std::cout << "*pcd = " << *pcd << std::endl;

        //------------------------------------------------------------------------------
        //summary: so 可以这样去想，所谓指向常量的指针或引用，const reference or const pointer, 
        //         它们都不过是"自以为是"罢了，它们觉得自己指向了常量，所以自觉的不去改变所指对象的值
        //------------------------------------------------------------------------------

        //const pointer, 即指针本身是一个常量指针(它所存储的地址不能改变)，又称为顶层const (top-level const)
        double ival = 1.0;
        double *const pi = &ival;   //const pointer 必须在定义时就被初始化

        //此时虽然我们不能修改pointer本身的值，但是其所指对象的值可以修改
        double ival2 = 2.0;
        double *const pi2 = &ival2; 
        //pi = pi2;   //compile error
        std::cout << "*pi = " << *pi << std::endl;
        *pi = 2.0;    // it's ok
        std::cout << "*pi = " << *pi << std::endl;

        //a const pointer to const value
        const double PI = 3.14159;
        const double *const cpi = &PI; //不管是指针本身，还是指针所指向的值都不能被修改了
    }

    constexpr int size()
    {
        return 30;
    }

    //常量表达式 (const expression) 是指值不会改变，并且在编译时就能得到计算结果的表达式，字面值是常量表达式
    //很多const..都是常量表达式，但有些const的初始化要在运行时才能确定，那这个const就不是一个常量表达式
    //所以C++11引入一个新的关键字 constexpr, 用于让编译器知道在编译时就要验证这个变量的值是否是一个常量表达式
    int fix_address = 3;
    void Demo12()
    {
        const int max_files = 20;  //it is a const expression
        constexpr int mf = 20;     //这两者基本等价
        constexpr int limit = mf + 10; 
        constexpr int sz = size(); //只有当size()是一个const expr 函数时才是一条正确的声明语句
        std::cout << "sz = " << sz << std::endl;

        //除了基本的算术类型之外，引用和指针也能被定义成constexpr，但它们的初始值收到严格限制
        //一个constexpr pointer的初始值必须是nullptr或者0，或者是存储于某个固定地址的对象
        //如何区分存储于固定地址的对象比较复杂，比较常见的一类就是定义在任何块作用域之外的变量

        //下面这两种写法相似，但是p和q的类型区别很大
        //对于p来说，它是一个底层const，指向一个常量的指针，但指针本身还是可以改变的
        //但是对于q来说，constexpr将它变为了一个底层const, 指针本身不能再被改变，它一直都会是一个nullptr
        const int *p = nullptr;
        constexpr int *q = nullptr;

        int ival = 55;
        p = &ival;   //it's ok
        std::cout << "*p = " << *p << std::endl;
        //q = &ival;   //compile error

        constexpr int *q2 = &fix_address;  //it's ok, fix_address是全局变量，存在固定地址里面
        std::cout << "*q2 = " << *q2 << std::endl;
    }
}