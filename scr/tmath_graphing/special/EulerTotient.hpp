#ifndef EULERTOTIENT_HPP
#define EULERTOTIENT_HPP
#include "../other/gcd.hpp"
namespace t_math
{
    inline int EulerTotient(int number)
    {
        int temp = 0;
        for(int i = 1; i <= number; i++)
        {
            if(gcd(i,number) == 1) temp++;
        }
        return temp;
    }
}
#endif