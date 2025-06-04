#ifndef SIN_HPP
#define SIN_HPP
#include "../general/factorial.hpp"
#include "../general/pow.hpp"
#include "../t_math_constant.hpp"
#include "../general/round_high.hpp"
#include "../general/abs.hpp"
namespace t_math
{
    inline double sin(double args)
    {
        if (args > 2 * pi)
            return sin(args - 2 * pi);
        if (args < 0)
            return -1 * sin(-1 * args);
        if (args == pi / 2)
            return 1;
        double temp = 0;
        int i = 0;
        while (abs(pow_int(-1, i) * pow_int(args, 2 * i + 1) / d_fac(2 * i + 1)) > t_math_precise)
        {
            temp += pow_int(-1, i) * pow_int(args, 2 * i + 1) / d_fac(2 * i + 1);
            i++;
        };
        return round_high(temp, 7);
    };
};
#endif // SIN_HPP
