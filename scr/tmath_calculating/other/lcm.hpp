#ifndef LCM_HPP
#define LCM_HPP
#include "gcd.hpp"
#include "../general/abs.hpp"
namespace t_math
{
    inline int lcm(int first, int second)
    {
        return abs(first * second)/gcd(first,second);
    }
}
#endif