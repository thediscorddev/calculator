#ifndef GAMMA_HPP
#define GAMMA_HPP
#include "../general/factorial.hpp"
#include "../t_math_constant.hpp"
#include "../general/pow.hpp"
#include "../general/abs.hpp"
#include "../general/exp.hpp"
#include "../general/floor.hpp"
#include "../general/sqrt.hpp"
#include "../general/ln.hpp"
#include "../other/is_int.hpp"
#include <stdexcept>
#include <iostream>
namespace t_math
{
    inline double gamma(double args)
    {
        if (args <= 0 && is_int(args))
            throw std::out_of_range("Gamma function is not defined at x = 0 and negative integer.");
        // if the last code is false
        if (args > 0 && is_int(args))
            return fac(args - 1);
        if (args <= 10)
            return gamma(args + 1) / args;
        double temp = 1;
        if (args > 10 && !is_int(args))
        {
            temp *= 2.50662827463100 * sqrt(args - 1);
            temp *= exp((args - 1) * (ln(args - 1) - 1));
            temp *= exp((pow_int(args - 1, 2) + 53 / 210) * ln(1 + 1 / (12 * pow_int(args - 1, 3) + 24 / 7 * (args - 1) - 1 / 2)));
        };
        return temp;
    };
};
#endif // GAMMA_HPP