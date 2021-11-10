#include <iostream>
#include "statements.h"

using namespace std;

namespace Chapter5
{
    //悬垂else (dangling else)
    //当有多个if，多个else时，else与离他最近的if相匹配
    void Demo1()
    {
        string lettergrade = "A";
        int grade = 15;

        //按缩进格式来看好像else是与第一个if相匹配，实际并不是这样
        if (grade % 10 >= 3)
            if (grade % 10 > 7)
                lettergrade += "+";
        else
        {
            lettergrade += "-";
        }
        
        cout << lettergrade << endl; 

        //使用括号括住就可以避免出现dangling else
        lettergrade = "";
        if (grade % 10 >= 3)
        {
            if (grade % 10 > 7)
                lettergrade += "+";
        }
        else
        {
            lettergrade += "-";
        }
        
        cout << lettergrade << endl;
    }

    char getVal() { return 'a'; }

    //switch
    void Demo2()
    {
        //case label 必须是整型、常量表达式
        char val = getVal();
        int ival2 = 42;
        switch (val)
        {
            case 'a': { cout << "it's a " << endl; break; }
            //case 3.14: //compile error, 3.14 is not an integer;
            //case ival2: //compile error, ival2 is not a const
        }
    }
}