#ifndef ROUND_LOW_HPP
#define ROUND_LOW_HPP
#include "pow.hpp"
#include "floor.hpp"
namespace t_math
{
    inline long double round_low(double x, int precision)
    {
        double n = floor(x * pow_int(10, precision));
        return n / pow_int(10, precision);
    };
};
#endif // ROUND_LOW_HPP
