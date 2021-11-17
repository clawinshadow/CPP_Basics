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
包括`float`, `double`,`long double`三种，一般`float`是32位，后面两者都是64位，在大多数平台上`long double`和`double`都是一样的精度。浮点数类型有三个特殊值要注意一下
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

