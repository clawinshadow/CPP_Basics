# C++数据类型 (Type System)
一门编程语言的数据类型系统决定了它是如何在内存中管理数据的，内存中的二进制字节序列因不同的数据类型从而具备了不同的语义信息。对C++来说，对象(Objects)、引用(References)、函数(functions)以及表达式(expressions)都有对应的的数据类型，总体来说C++的数据类型系统可以做如下分类：
- __基础类型__(Fundamental Types): 其中绝大部分也被称为基本内置类型(primitive built-in types)
  - 算术类型(Arithmetic Types): 能直接进行加减乘除等各种算术运算的数据类型
    - 整型(Integral Types)
      - 布尔型: `bool`
      - 字符型(character types): 窄字符型包括 `char, signed char, unsigned char` 等，宽字符型包括 `wchar_t, char16_t, char32_t` 等主要用于Unicode字符集
      - 整数类型(integer types): `short, int, long, long long` 等整数类型，这些都支持无符号版本(`unsigned`)
    - 浮点型(Floating-point Types): `float, double, long double`
  - 特殊数据类型
    - `void`: 一般用来修饰函数返回值类型或者指针，表示函数没有返回值以及不明类型的指针等
    - `nullptr_t`: Since C++11, type of `nullptr`. 
- __复合类型__ (Compound Types)
  - 引用类型(reference types): 左值引用，右值引用等
  - 指针类型(pointer types): 对象指针，函数指针，指向类成员的指针，空指针，void *等
  - 数组类型(array types)
  - 枚举类型(enumeration types)
  - 类类型(class types): union or non-union types
  - 函数类型(function types) 

Refer to [[C++ Type System](https://en.cppreference.com/w/cpp/language/type)](https://en.cppreference.com/w/cpp/language/type)

------
## 1. 基础类型(Fundamental Types)
Also called primitive built-in types
### 1.1 整型 (Integral Types)
C++语言中定义了各个整型的含义，以及绝大多数整型的最小尺寸，但并未严格限定每种整型的固定大小，整型的具体所占字节数视平台和实现而定，可使用`sizeof(_type name_)`来查看某个类型在本地实现的具体大小
#### 1.1.1 布尔类型
`bool`, 取值范围 [`true`, `false`]，最小尺寸未定义，`sizeof(bool)`在绝大多数机器上应该都是 1
#### 1.1.2 字符型
`char`, `wchar_t`, `char16_t`, `char32_t` - `char`的最小尺寸为8位，早期的计算机中`char`足以应付所有的字符，后期根据字符集的不断发展和扩大，字符类型的大小也做了相应的扩展
   - 在随后的设计中，`wchar_t`就被期望能满足所有的字符需求，它在绝大多数系统中都是32位的长度，只有Windows系统中是个例外，占16位，表示一个UTF-16的code unit
   - C++11之后，对于字符类型的设计做了更进一步的细分，`char16_t`专门用来适配UTF-16编码，最小尺寸16位，`char32_t`用来适配UTF-32编码，最小尺寸32位
   - C++20补充了新的字符类型`char8_t`，用于适配UTF-8编码，补全了对整个Unicode字符集的支持

我们在C++中各种`string`的实现里面可以看到这些对应的字符类型, Specializations of the basic_string<> template.

   ![](./string_definitions.png)

需要注意的是虽然`std::string`是由8位的char组成的，但并不代表它不能容纳Unicode字符串，在Linux系统中，`std::string`采用的是UTF-8编码来操作字符串，Windows系统中，`std::string`的编码应该是跟当前系统的本地化配置(locale)有关系[[Details: Windows Strings]](https://docs.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp?view=msvc-170)。

参考`StringEncodingDemo()`:
```C++
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
    ....
}
```
[[UTF-8 Encoder]](https://www.browserling.com/tools/utf8-encode)
#### 1.1.3 整数类型
C++中整数类型的核心是`int`，它的最小尺寸保证是16位，然后通过如下两类修饰符(modifiers)来衍生出各种不同的整数类型
- 符号(Signedness): `unsigned`、`signed`, 通常`signed`是默认的，在类型声明中可以省略
- 大小(Size): `short`、`long`、`long long`(Since C++11)

两种修饰符可以组合成任意的整数类型，一般`signed`, `int`在类型声明中都可以省略。比如 `signed long long int` = `long long`

各整数类型的具体大小，即所占字节数，根据各个操作系统和平台结构的不同而不同，C++这些基础类型的实现统称为data models，常见的四种数据模型如下：\
![](./data_models.png)\
对于我们常见的Unix 64位的操作系统来说，适配LP64模型，`short`是16位，`int`32位，`long`和`long long`都是64位。因为数据模型的原因，C++的代码在跨平台移植、交互的时候需要注意兼容性\
所有整数类型如下图:\
![](./size.png)

如果对数据类型的固定长度有很高的要求，可以考虑使用`定长整数类型`(Fixed width integer types), 它能保证在各平台下都有一致的大小。目前ZROS平台里面应该普遍都在用这种数据类型

![](./fixed_width.png)

[[Details: Fixed width integer types]](https://en.cppreference.com/w/cpp/types/integer)

在本机上查看数据类型的大小一般使用sizeof()方法，查看具体类型的最大值最小值，C++11之后可以使用`numeric_limits`类，之前可以使用`limits.h`里面定义的各种宏:
```C++
void SizeofDataTypesDemo()
{
    std::cout << "sizeof(short): " << sizeof(short) << std::endl;
    //Range [-32768, 32767]
    std::cout << "Maximum value of short: " << SHRT_MAX << std::endl; //Macro defined in limits.h
    std::cout << "Maximum value from numeric limits: " << std::numeric_limits<short>::max() << std::endl; //Since C++11

    std::cout << "sizeof(unsigned short): " << sizeof(unsigned short) << std::endl;
    std::cout << "Maximum value of unsigned short: " << USHRT_MAX << std::endl; //Macro defined in stdint.h
    std::cout << "Maximum value from numeric limits: " << std::numeric_limits<unsigned short>::max() << std::endl;
}
```
### 1.2 浮点数类型
包括`float`, `double`,`long double`三种，一般`float`是32位，`double`是64位，`long double`是128位，但是在大多数平台上`long double`只使用了80位有效位数来描述一个浮点数，少数平台支持全部的128位超高精度浮点数。

浮点数类型有三个特殊值要注意一下
1. _带负号的零_ (Negative zero) - 算术上它与零相等，主要用于生成`-INFINITY`
2. _INFINITY_ - 无穷大，分别有正无穷和负无穷
   - `INFINITY` 与所有数值的加减乘除均为INFINITY
   - `INFINITY` 与同样符号的`INFINITY`相等
   - C++11之后可以用`std::isinf()`来检查数值是否是`INFINITY`
3. _NAN_ (Not a Number) - 代表非法的数值
   - NAN与所有数值的加减乘除均为NAN
   - NAN不等于任何数值，也不等于同样的NAN
   - C++11之后可以用`std::isnan()`方法来检查某个浮点数是否是NAN
  
参考下面的FloatPointSpecialValuesDemo():
```C++
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
              << "isnan(NaN): " << std::isnan(NAN) << '\n'
              << "isnan(0.0): " << std::isnan(0.0) << '\n'
              << "isnan(Inf): " << std::isnan(INFINITY) << '\n'
              << "isnan(Inf + 1): " << std::isnan(INFINITY + 1) << '\n'
              << "isnan(Inf + Inf): " << std::isnan(INFINITY + INFINITY) << '\n'
              << "isnan(Inf - Inf): " << std::isnan(INFINITY - INFINITY) << '\n';
    char* end;
    std::cout << std::boolalpha
              << "isnan(strtod(\"NaN\")): " << std::isnan(std::strtod("NaN", &end)) << std::endl;
}
```
-------------
### 1.3 给算术类型赋值
C++算是一种类型不安全的语言(type unsafety)，在给算术类型赋值的时候，存在一些隐式类型转换，并且潜在的溢出情况也需要注意
1. 可以给`bool`类型赋一个整数值，只要非零的值都是`true`
2. 反过来`bool`值赋给整数类型时，true = 1， false = 0
3. 浮点数的值赋给整数类型时，会丢失精度，保留整数位
4. 给无符号整型赋一个越界的值 `val` ，所得的结果为`val`对这个类型所占的位数的二次幂取模之后的余数，虽然这种赋值明显是错误的，但C++中它造成的后果是一种 well-defined behavior，不会引起任何运行时异常
   > 以16位`unsigned short int`为例，它的取值范围为[0, 65535], 如果给它赋值65540，实际所得的值应该是 4 \
    因为 65540 = 1 * (2^16) + 4, 余数为 4
5. 给有符号整型赋一个越界的值，造成的结果是undefined behavior, 无法预计，大多数情况下会得到一个取模之后的值，与无符号整型是一样的处理，但也有可能会得到一个非法值，或者程序崩溃。应尽量避免这种错误。
6. 在无符号整型与有符号整型一起做算术运算的时候，有符号的会被先转化成无符号整型做运算，所以尤其要注意当有符号整数转化成无符号时越界的这种情况。另外，所有算术运算中，低于32位的数值都会被promoted成signed int再做计算

以上这种越界的潜在赋值错误，都可以在编译时通过`-Woverflow`选项来让编译器报警
  
  参考AssignValuesDemo()
  ```C++
  void AssignValuesDemo()
  {
      bool b = false;
      b = 42; //should be true, any integer value assigned to a bool type should be true except 0
      std::cout << std::boolalpha << "b is " << b << std::endl;

      //bool values assigned to a integer type, true -> 1, false -> 0
      int i = b;
      std::cout << "i = " << i << std::endl;

      //float-point values assigned to a integer type, will lose precision
      i = 3.14159;
      std::cout << "i = " << i << std::endl;

      //Assign a value outside the range of an unsigned integer type
      //result is the remainder of (value mod 2**(bits of type))
      unsigned short us = 65560; // 65560 mod 2**16 -> 65560 = 1 * 65536 + 24
      std::cout << "us = " << us << std::endl;
      us = -2;                   // -2 mod 65536 -> -2 = -1 * 65536 +65534
      std::cout << "us = " << us << std::endl;

      //Assign a value outside the range of a signed integer type
      //result is undefined behavior, the most critical error we should be avoid.
      short s = 70000;
      std::cout << "s = " << s << std::endl;

      unsigned int u = 10;
      int i2 = -42;
      std::cout << "u + i2 = " << u + i2 << std::endl; // -42 would be converted to unsigned int

      unsigned short u2 = 10;
      short s2 = -42;
      // u & s2 were promoted to signed int in arithmetic operations
      // the same as: (int)u2 + (int)s2
      std::cout << "u2 + s2 = " << u2 + s2 << std::endl;

      unsigned char uc = 10;
      signed char c = -42;
      //promoted too
      std::cout << "uc + c = " << uc + c << std::endl;
  }
  ```
### 1.4 字面值 (Literals)
字面值就是一个很直观的值(self-explaning)，常用于赋值表达式的右边，每一个字面值都有对应的数据类型，编译器根据它的值以及前后缀等形式来推断它的数据类型
#### 1.4.1 整数字面值 (Integer literals)
表示一个整数，对于整数字面值来说，编译器推断出来的数据类型至少都是`int`，不存在`short`这种字面值整数类型。所以下面的代码应该显示是4字节
```C++
auto i = 10;       //decimal-literal
std::cout << "sizeof(i) = " << sizeof(i) << std::endl;
```
能在数值后面加上各种后缀来告知编译器这是一个`long int`，或者是`long long int`，或者是无符号类型等等
```C++
auto i_l = 10l;    // suffix l/L means signed long int
std::cout << "sizeof(i_l) = " << sizeof(i_l) << std::endl;
auto i_ll = 10LL;  // suffix LL/ll means signed long long int
std::cout << "sizeof(i_LL) = " << sizeof(i_ll) << std::endl;
auto i_u = -10u;   // suffix u means unsigned, -10 definitely overflow
std::cout << "i_u = " << i_u << std::endl;
```
一个整数字面值支持四种进制的表示方法，二进制、八进制、十进制和十六进制
```C++
auto i_b = 0b1010; //binary-literal
auto i_o = 012;    //octal-literal
auto i_h = 0xA;    //hexademical-literal
std::cout << "i i_b i_o i_h: " << i   << " " << i_b << " " 
                               << i_o << " " << i_h << " " << std::endl;
```
#### 1.4.2 浮点数字面值 (Floating-point literals)
一个浮点数字面值的类型由下面几种后缀来决定：
- (no suffix) defines a `double`
- f/F defines a `float`
- l/L defines a `long double`
```C++
auto f = 3.14159f;  // suffix f/F represents a float type
std::cout << "sizeof(f) = " << sizeof(f) << std::endl;
auto d = 3.14159;   // no suffix represents a default double type
std::cout << "sizeof(d) = " << sizeof(d) << std::endl;
auto ld = 3.14159L; // suffix l/L represents a long double type
std::cout << "sizeof(ld) = " << sizeof(ld) << std::endl;
```
浮点数的科学计数法表示
```C++
auto f_e = 3.14159e5; //科学计数法来表示一个浮点数, e/E 作为指数标记
std::cout << "f_e = " << f_e << std::endl;
```
#### 1.4.3 字符型、字符串字面值 (Character/String literals)
字符型和字符串字面值采用相同的前缀来决定具体的数据类型
- No prefix -> default `char` type, 1 byte
- 'L' prefix -> defines a `wchar_t` type, 4 bytes
- 'u' prefix -> defines a `char16_t` type, 2 bytes
- 'U' prefix -> defines a `char32_t` type, 4 bytes 
```C++
auto c = 'a';       //default char type with no prefix
std::cout << "sizeof(c) = " << sizeof(c) << std::endl;
auto wide_c = L'a'; // L prefix represents a wide character, wchar_t
std::cout << "sizeof(wide_c) = " << sizeof(wide_c) << std::endl;
auto u16_c = u'a';  // u prefix represents a char16_t, utf-16 character
std::cout << "sizeof(u16_c) = " << sizeof(u16_c) << std::endl;
auto u32_c = U'a';  // U prefix represents a char32_t, utf-32 character
std::cout << "sizeof(u32_c) = " << sizeof(u32_c) << std::endl;
```
字符串字面值的前缀一样，具体参考前面的StringsEncodingDemo

### 1.5 变量的声明 (Variables declaration)
变量的声明主要由两个部分组成: 
- 修饰符序列(specifier sequence): 主要就是指明变量的数据类型、是否常量等等
- 声明符序列(declarator list): 一个声明符由 变量名称(identifiers) 以及 引用符号`&`, 指针符号`*`...等组合而成

>_decl-specifier-seq init-declarator-list_

#### 1.5.1 修饰符(Specifier)
主要就是指明变量的数据类型、是否常量等等
1. 指明变量的数据类型 (type specifiers) - 前面提及的各类基本数据类型都是修饰符，包括`class`, `enum`, `struct`, `union`...等复杂数据类型
2. `typedef`, `inline`, `friend`, `constexpr`等各类访问修饰符、常量表达式修饰符、其它各种特殊用途的修饰符等等
   
详情参考[[Specifiers]](https://en.cppreference.com/w/cpp/language/declarations)

#### 1.5.2 标识符(Identifier)
主要用于指定一个变量的名称，它由数字、拉丁字母、下划线组成，可任意排列但要注意以下几点
1. 不能以数字开头，会导致编译失败 `(e.g. int 3i; //compile error)`
2. 不能与任何C++关键字(keywords)重名，会导致编译失败
3. 大小写敏感
4. 以下几种命名方式编译能通过，但通常这类命名方式被标准库所保留(reserved)，容易重名
    - 名称中不要出现连续两个下划线(`__`)，尤其是名称开头和结尾部分
    - 名称不要以 下划线+大写字母 开头(`e.g. _A`)
    - 全局变量的名称中不要以下划线开头

#### 1.5.3 声明符(Declarator)
一个声明符由变量标识符以及引用符号`&`/`&&`, 指针符号`*`...等组成，引用和指针与简单数据类型组合成复合类型(compound types)
```C++
int a = 1, *p = nullptr, f(), (*pf)(double);
// decl-specifier-seq is int
// declarator a = 1 defines and initializes a variable of type int
// declarator *p = nullptr defines and initializes a variable of type int*
// declarator (f)() declares (but doesn't define)
//                  a function taking no arguments and returning int
// declarator (*pf)(double) defines a pointer to function
//                  taking double and returning int
```
详情参考[[Declarations]](https://en.cppreference.com/w/cpp/language/declarations)

----------
## 2. 复合类型 (Compound types)
本章主要介绍引用、指针以及数组等复合类型
### 2.1 引用 (reference)
引用就是给已存在的对象起的一个别名，它在内存中没有属于自己的实体数据，声明符形式: `&`_`var`_
> A reference is not an object. Instead, a reference is just another name for an already existing object.

引用类型的声明：
```C++
int i = 42;
int &ref_i = i; //ref_i is a reference of i
std::cout << "ref_i = " << ref_i << std::endl;
```
对引用的所有修改操作直接影响其绑定的对象
```C++
ref_i = 0;
std::cout << "i = " << i << std::endl;
```
需要注意的几点：
1. 引用在声明的时候必须被初始化，不存在默认值
   ```C++
   int &ref_i2;    //compile error: reference must be initialized
   ```
2. 引用在初始化之后，无法再绑定到其他的对象，没有这样的语法
3. 引用只能绑定实体对象，不能绑定另一个引用，即：不存在引用的引用 
4. 不能用字面值来初始化一个引用
   ```C++
   int &ref_i3 = 1024; //compiler error: reference cannot bind to a literal value
   ```
5. 声明引用的数据类型必须与其绑定的对象数据类型一致
   ```C++
   double d = 3.1415
   int &ref_d = d; //compiler error: type of reference must be the same as the binding object
   ```
参考`ReferencesDemo()`;
### 2.2 指针(Pointer)
__指针__ 是“指向”另外一种类型的复合类型，它的声明符形式`*var`，其中`var`是该指针变量的名称。
- 它使用 __取地址符&__ 来获取目标对象的内存地址
- 对指针使用 __解引用符* (dereference)__ 来获取目标对象的实体数据
   ```C++
   int val = 42;
   int *p_val = &val; //get the memory address of val
   std::cout << "The value of p_val point to: " << *p_val << std::endl; //dereference p_val
   ```

与引用类似，指针也实现了对其他对象的间接访问。但是它与引用还有很多不同之处：

1. 引用本身在内存里没有对应的实体，它只是另外一个对象的别名。指针不同，它本身存储了指向另外一个对象的内存地址，在32位机器上是32位地址，64位机器上是64位地址。所以指针本身是有实体数据的。
   ```C++
   int i = 5;
   int *pi = &i; //pointer declaration
   std::cout << std::hex << "The value of pi (the address of i) = " << pi << std::endl;
   ```
   上面代码中的指针`pi`在64位机器上打印出来一般都是48位的值，是因为目前绝大多数CPU都只用了48位的地址空间(能应付2^18次方GB的内存)，高16位保留了。

   Linux 系统可使用 `cat /proc/cpuinfo` 来查看CPU详细信息

2. 指针无需在声明的时候赋初始值，未初始化的指针拥有一个不确定的值(Undefined behavior)，使用它时程序一般都会crash，但也有可能会继续错误的运行下去，需要尽量避免这种不可预计的后果
   ```C++
   int *p; //don't need to be initialized
   std::cout << std::hex << "The value of uninitialized p: " << p << std::endl; //a random memory address
   std::cout << "The value p point to: " << (int)*p << std::endl; //probably crashed here
   ```
   > __ATTENTION__: 初始化所有的指针，如果暂时不知道给指针赋什么值，可以用NULL或者0来初始化一个空指针，C++11之后可以用`nullptr`来初始化空指针

   我们可以直接将指针作为if语句的判断条件，如果该指针为`nullptr`或者`0/NULL`这样的空指针，if 语句返回false，否则为true
   ```C++
   int *p_null = 0;
   p_null = NULL;
   p_null = nullptr; // all the same to initialize a null pointer
   if (!p_null)
      std::cout << "p_null is a null pointer" << std::endl;
   ```
   所以当我们使用一个来路不明的指针时，比如在一个函数体内使用作为参数传进来的指针，最好是先判断它是否为空指针，以免对它解引用时报错导致程序crash
3. 引用在其初始化后就一直与初始对象绑定，但是指针在其生命周期内可以再指向不同的对象
   ```C++
   int i2 = 6;
   pi = &i2;
   std::cout << "now p2 point to i2: " << *pi << std::endl;
   ```
#### 指针之间的比较
对于两个类型相同的合法指针，可以使用相等操作符`==`和不等操作符`!=`来比较它们。如果它们存放的地址值是相等的，则比较结果为true。地址值相等主要有以下三种情况：
1. 两个指针都为空
2. 两个指针指向同一个对象
   ```C++
   //references comparation
   int *p1 = nullptr;
   int *p2 = nullptr;
   std::cout << std::boolalpha << "p1 == p2: " << (p1 == p2) << std::endl;

   int a = 5;
   p1 = &a;
   p2 = &a;
   std::cout << std::boolalpha << "p1 == p2: " << (p1 == p2) << std::endl;
   ```

#### const引用 (reference to a const)
引用本身不是一个对象，所以这里的const不是用来修饰引用的，实际上它是一个针对const常量的引用