#ifndef CHI_HPP
#define CHI_HPP
#include "../general/pow.hpp"
#include "../general/abs.hpp"
#include "../general/factorial.hpp"
#include "../t_math_constant.hpp"
#include "../general/round_high.hpp"
#include "../hyperbolic/sinh.hpp"
#include "../hyperbolic/cosh.hpp"
namespace t_math
{
    inline double chi(double args)
    {
        if (args < 0)
            return -1 * chi(-1 * args);
        double temp = 0;
        if (args == 0)
            return 0;
        int i = 0;
        if (args < 13)
        {
            while (abs(( pow_int(args, 2 * i + 1)) / ((d_fac(2 * i + 1) * (2 * i + 1)))) > t_math_precise)
            {
                temp += (pow_int(args, 2 * i + 1)) / ((d_fac(2 * i + 1) * (2 * i + 1)));
                i++;
            }
        }
        else if (args >= 13)
        {
            double ci = 1;
            double sn = 1 / args;
            while (i <= 30)
            {
                ci += d_fac(2 * i) / pow_int(args, 2 * i);
                sn += d_fac(2 * i + 1) / pow_int(args, 2 * i + 1);
                i++;
            };
            temp += pi / 2 - (cosh(args) / args) * ci - (sinh(args) / args) * (sn);
        };
        return temp;
    };
};
#endif // CHI_HPP