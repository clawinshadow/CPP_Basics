#include <iostream>

int cnt = 1;

static int val = 1;       //internal linkage
static int get_size() { return 1; } //internal linkage
const int cval = 1;       //internal linkage
constexpr int ce_val = 1; //internal linkage
typedef struct {int a; int b;} TS, *PTS; //internal linkage

int i = 1;          //external linkage
extern int j = 1;   //external linkage, equals to int j = 1
extern const int ci = 1; //external linkage
enum EA {
    EA_1,
    EA_2
};                  
EA ea = EA::EA_1;   //external linkage

void GlobalScopeDemo()
{
    int cnt = 2;
    std::cout << "local cnt = " << cnt << std::endl;
    std::cout << "global cnt = " << ::cnt << std::endl;
}

void LinkageDemo_File1()
{
    std::cout << "val in file1 = " << val << std::endl;
    std::cout << "get_size() in file1 returns " << get_size() << std::endl;
    std::cout << "cval in file1 = " << cval << std::endl;
    std::cout << "ce_val in file1 = " << ce_val << std::endl;

    TS ts = {1, 2};
    std::cout << "ts.a in file1 = " << ts.a << std::endl;

    std::cout << "int i = " << i << std::endl;
    std::cout << "--------------Seperator-------------------" << std::endl;
}