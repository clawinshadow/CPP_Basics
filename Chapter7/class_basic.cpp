#include <iostream>
#include "class_basic.h"

using namespace std;

namespace Chapter7
{
    //1. 常量成员函数，比如SalesData类的isbn()函数，即函数参数列表后带一个const的成员函数
    //   它本质上相当于传进来一个const this指针，所以函数体内不允许修改类里面的任何东西
    //   即 isbn(const SalesData* this).
    //   另外，如果在外面定义一个const SalesData的变量，那么该变量只能调用常量的成员函数
    void Demo1()
    {
        const SalesData sd("SD", 100, 5);
        cout << sd.isbn() << endl;  //可以调用常量成员函数
        //sd.set_isbn("sdd");  //compile error;

        SalesData sd2("SD2", 50, 2);
        sd2.set_isbn("sd2");   //it's ok
        cout << sd2.isbn() << endl;
    }

    //构造函数要注意的几点
    //1. 构造函数不能声明为const的
    //2. 编译器只有在发现类不包含任何构造函数的情况下，才会定义一个默认的构造函数
    //   意思是如果我们显示的定义了含参数的构造函数，那么就必须再定义一个默认的构造函数，
    //   否则函数就没有默认的构造函数，这样不太好
    //3. 对于含复合类型或者其余内置类型、类类型成员的类，需要定义构造函数来明确初始化这种复杂类型的初始值
    //4. 如果该类里面含有某个没有默认构造函数的类类型，那么这会导致编译器无法为这个类生成默认的构造函数
    class ConstructorDemo
    {
        private: int a;
        private: string b; 
    public:
        ConstructorDemo(int _a, string _b)
        { 
            a = _a;
            b = _b;
        }
    };

    //在C++中 struct 和 class 的唯一区别就是默认的访问权限不一样
    //在struct里面默认的每个成员都是public的，而在class里面除非声明了是public，否则默认都是private的
    struct StructDemo
    {
        int a = 0;
        string b;
    };

    class ConstructorDemo2
    {
        int a = 0;
        int c;
        string b; 

    public:
        ConstructorDemo2(int _a, string _b)  //构造函数必须是public的
        { 
            a = _a;
            b = _b;
            c = 0;
        }

        //默认构造器并不保证将int之类的基本数据类型都初始化为0，它会赋予一个随机值
        //所以靠谱点的还是自己写构造器，或者对于简单的数据类型，就在定义的时候赋一个初值，就像 int a = 0
        ConstructorDemo2() = default; //C++11, 默认构造器

        std::string ToString()
        {
            string result = std::to_string(a) + " | " + b + " | " + std::to_string(c);
            return result;
        }
    };

    void Demo2()
    {
        //ConstructorDemo cd;  //compile error, no matching constructor..
        ConstructorDemo2 cd;   //it's ok
        cout << cd.ToString() << endl; 

        //struct & class
        StructDemo sd;
        cout << sd.a << " | " << sd.b << endl; //public fields default
        //cout << cd.a; //compile error, private fields default in class
    }

    //除了构造函数之外，类还需要控制拷贝、赋值和销毁对象时所发生的行为
    //对于只包含基本数据类型的类（包括vector和string），编译器可以自己合成这几种行为，并且能正常工作
    //但是对于包含复杂数据类型的类来说，这个就不靠谱了，具体的讨论以后再说

    //友元函数
    //类可以允许其他类或者函数访问它的非共有成员，方法是令其他类或者函数成为它的友元
    //如果类想把一个函数作为它的友元，只需要增加一条以friend关键字开始的函数声明语句即可
    //要注意这个概念的核心还是在函数本身，它主要是声明在类外，实现在类外，但为了访问这个类的非公有成员
    //所以又在类里面加了这一条声明，其余的对类本身来说没有任何变化，参考SalesData类
    //recommendded:
    //  1. 在类的最开始或者最后，集中的声明说有的友元函数
    //  2. 通常把友元的声明与类本身放置在同一个头文件中

    //mutable: 可变数据成员，该关键字标识的变量，可以在常量成语函数中修改它
    class MutableDemo
    {
    private:
        int a = 0;
        mutable int b = 0;
    public:
        MutableDemo(int _a, int _b): a(_a), b(_b) { };
        MutableDemo() = default;
        int GetA() const { b++; return a; };  //const函数中修改了成员 b 的值，it's ok
        int GetB() const { return b; };
    };

    void Demo3()
    {
        MutableDemo md(3, 3);
        cout << md.GetA() << " | " << md.GetB() << endl;
    }

    //返回*this的成员函数
    class CalculatorDemo
    {
    private:
        double number = 1;
    public:
        CalculatorDemo& Add(double val) 
        { 
            number += val; 
            return *this; 
        }

        CalculatorDemo& Multiply(double val)
        {
            number *= val;
            return *this;
        }

        double GetResult() const { return number; }
    };

    void Demo4()
    {
        CalculatorDemo cd;
        //返回*this的作用主要就是可以使用这种写法，注意返回类型里面还有个引用，否则每次调用更改的都是临时副本就没用了
        cout << "Result = " << cd.Add(5).Multiply(6).Multiply(2).GetResult() << endl;
    }

    //友元再探：前面讲了类里面可以声明一个外部函数为友元，实际上还有以下几种情况
    //  1. 类A里面可以声明另一个类B为友元，然后类B的所有成员函数就可以访问类A包括非公有成员在内的所有成员
    //  2. 类A里面可以仅声明另一个类B的某个函数为友元，只有这个函数才有访问类A所有成员的权限
    
    //demo of 1
    class A
    {
        friend class B;
        int a = 5;
    };

    class B
    {
        int b = 6;
    public:
        void GetAMember() 
        {
            A _a;
            cout << "private member a of A: " << _a.a << endl;
        }
    };

    void Demo5()
    {
        B _b;
        _b.GetAMember();
    }

    //demo of 2
    //对于第二种情况，对于两个类，以及友元函数的定义和声明有严格的顺序
    //比如类C中声明类D的某个函数func()为友元，则顺序如下：
    //  step 1: 先声明类D，以及它的函数func()，但不定义func()
    //  step 2: 声明类C
    //  step 3: 定义类D的函数 func()
    //总结：关于友元的本质其实就是关于对本类访问权限的一个声明，它本身并不是一个普通意义上的声明

    class D
    {
        int d = 5;
        public: void GetCMember();
    };

    class C
    {
        int c = 9;
        friend void D::GetCMember();
    };

    void D::GetCMember()
    {
        C _c;
        cout << "private member of C: " << _c.c << endl;
    }

    void Demo6()
    {
        D _d;
        _d.GetCMember();
    }

    //构造函数深入研究
    //构造函数初始值列表的必要性： 1. 性能方面的考量 2. 有时候不得不用这种方式

    //1. 性能方面的考量
    //   在如下的ConstRef(int _val)构造函数执行之前，类成员int a实际上已经执行过一次默认初始化为0
    //   然后才是在构造函数中再被赋值一次，等价于我们先声明一个变量，再为他赋值：
    //   int a;
    //   a = 5;
    //   那么在构造函数初始值列表这种方法中，则只执行了一次操作，直接赋值，形如下面的第二个构造函数

    // 2. 必须使用的情况: 当类成员包含const，引用，或者某种没有默认构造函数的类类型时，
    //                  必须通过构造函数初始值列表来完成初始化
    //    比如下面的 const int ci, int &ri, 都不能在第一个构造函数中初始化，会编译报错
    class ConstRef
    {
    private:
        int a;
        const int ci;
        int &ri;
    public:
        // ConstRef(int _val)
        // {
        //     a = _val;
        //     ci = a;  //compile error
        //     ri = a;  //compile error
        // }

        ConstRef(int _val): a(_val), ci(_val), ri(a) { }; 
    };

    //构造函数初始值列表中，成员初始化的顺序
    //这个顺序不是以写列表的顺序来的，而是按照成员在类的声明中的顺序来的
    //比如下面的例子中，我们以为是先用val初始化了j，然后用j初始化i
    //实际上刚好相反，因为在类成员的声明中，i排在前头，所以先初始化i，而此时j尚未定义
    class X
    {
        int i;
        int j;
    public:
        //使用未定义的值j来初始化i
        X(int val): j(val), i(j) { };
        std::string ToString()
        {
            return std::to_string(i) + " | " + std::to_string(j);
        }
    };

    void Demo7()
    {
        X x(5); 
        std::cout << x.ToString() << std::endl;  //i为随机值
    }
}