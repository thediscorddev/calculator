#ifndef ERF_HPP
#define ERF_HPP
#include "../general/pow.hpp"
#include "../general/factorial.hpp"
#include "../general/abs.hpp"
#include "../general/exp.hpp"
#include "../t_math_constant.hpp"
namespace t_math
{
    inline double erf(double arg)
    {
        double temp = 0;
        int i = 0;
        bool is_termimated = false;
        double term = 0;
        if (arg < 0)
            return -1 * erf(-1 * arg);
        if (abs(arg) < 3)
        {
            while (is_termimated == false)
            {
                term = (pow_int(-1, i) * pow_int(arg, 2 * i + 1)) / (d_fac(i) * (2 * i + 1));
                temp += term;
                i++;
                if (abs(term) < t_math_precise)
                    is_termimated = true;
            }
            temp *= 1.12837916709551257390;
        }
        else
        {
            temp = 1 - (exp(-1 * pow_int(arg, 2))) / arg * 0.56418958354775628695 * (1 - 1 / (2 * pow_int(arg, 2)) + 3 / (4 * pow_int(arg, 4)) - 15 / (8 * pow_int(arg, 6)));
        };
        return temp;
    };
};
#endif // ERF_HPP