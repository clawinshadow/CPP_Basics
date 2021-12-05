#include <iostream>

static int val = 2;       //internal linkage
static int get_size() { return 2; } //internal linkage
const int cval = 2;       //internal linkage
constexpr int ce_val = 2; //internal linkage
typedef struct { char a; char b; } TS, *PTS; //internal linkage 

//int i = 2;          //linking error: duplicate symbol '_i'
extern int i;         //use extern to declare i, but not define it
// extern int j = 2;   //linking error
//const int ci = 2; //linking error
extern const int ci;
// enum EA {
//     EA_1,
//     EA_2
// };                  
// EA ea = EA::EA_2;      //linking error

void LinkageDemo_File2()
{
    std::cout << "val in file2 = " << val << std::endl;
    std::cout << "get_size() in file2 returns " << get_size() << std::endl;
    std::cout << "cval in file2 = " << cval << std::endl;
    std::cout << "ce_val in file2 = " << ce_val << std::endl;

    TS ts = {'a', 'b'};
    std::cout << "ts.a in file2 = " << ts.a << std::endl;

    std::cout << "extern int i = " << i << std::endl;
    std::cout << "extern const int ci = " << ci << std::endl;
}