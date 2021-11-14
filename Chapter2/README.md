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
    - `void`: 一般用来修饰函数返回值或者指针，表示函数没有返回值以及不明类型的指针等
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
## 基础类型(Fundamental Types)
Also called primitive built-in types
### 整型 (Integral Types)
C++语言中定义了各个整型的含义，以及绝大多数整型的最小尺寸，但并未严格限定每种整型的固定大小，整型的具体所占字节数视平台和实现而定，可使用sizeof(_type name_)来查看某个类型在本地实现的具体大小
1. 布尔类型：`bool`, 取值范围 [`true`, `false`]，最小尺寸未定义，`sizeof(bool)`在绝大多数机器上应该都是 1
2. 字符型: `char`, `wchar_t`, `char16_t`, `char32_t` - `char`的最小尺寸为8位，早期的计算机中`char`足以应付所有的字符，后期根据字符集的不断发展和扩大，字符类型的大小也做了相应的扩展
   - 在随后的设计中，`wchar_t`就被期望能满足所有的字符，它在绝大多数系统中都是32位的长度，只有Windows系统中是个例外，占16位，表示一个UTF-16的code unit
   - C++11之后，对于字符类型的设计做了更进一步的细分，`char16_t`专门用来适配UTF-16编码，最小尺寸16位，`char32_t`用来适配UTF-32编码，最小尺寸32位
   - C++20补充了新的字符类型`char8_t`，用于适配UTF-8编码，补全了对整个Unicode字符集的支持 \
   我们在C++中各种`string`的实现里面可以看到这些对应的字符类型
   ![](./string_definitions.png)