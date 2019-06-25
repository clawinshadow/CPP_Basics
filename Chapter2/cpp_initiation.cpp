#include <iostream>

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
}