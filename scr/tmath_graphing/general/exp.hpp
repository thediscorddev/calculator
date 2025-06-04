#ifndef EXP_HPP
#define EXP_HPP
#include "factorial.hpp"
#include "d_pow.hpp"
#include "floor.hpp"
#include "log.hpp"
#include "pow.hpp"
#include "../t_math_constant.hpp"
namespace t_math
{
    inline long double exp(double x)
    {
        return pow(t_math::e,x);
    }
    inline long double expOld(double x)
    {
        long double temp = 0;
        if (x < 0)
            return 1 / exp(-1 * x);
        if (x == 0)
            return 1;
        const double a = pow_int(e, (int)floor(x));
        int i = 0;
        while (abs((a * pow_int(x - a, i)) / d_fac(i)) > t_math_precise * 0.0000001)
        {
            temp += (a * pow_int(x - floor(x), i)) / d_fac(i);
            i++;
        };
        return temp;
    };
}
#endif // EXP_HPP
