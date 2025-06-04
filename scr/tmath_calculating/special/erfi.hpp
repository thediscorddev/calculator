#ifndef ERFI_HPP
#define ERFI_HPP
#include "../general/pow.hpp"
#include "../general/factorial.hpp"
#include "../general/abs.hpp"
#include "../general/exp.hpp"
#include "../t_math_constant.hpp"
namespace t_math
{
    inline double erfi(double arg)
    {
        double temp = 0;
        int i = 0;
        bool is_termimated = false;
        double term = 0;
        if (arg < 0)
            return -1 * erfi(-1 * arg);
            while (is_termimated == false)
            {
                term = (pow_int(arg, 2 * i + 1)) / (d_fac(i) * (2 * i + 1));
                temp += term;
                i++;
                if (abs(term) < t_math_precise)
                    is_termimated = true;
            }
        return temp*1.12837916709551257390;
    };
};
#endif // ERFI_HPP
