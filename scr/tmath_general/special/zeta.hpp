#ifndef ZETA_HPP
#define ZETA_HPP
#include "../t_math_constant.hpp"
#include "../general/d_pow.hpp"
#include "../general/abs.hpp"
#include "../other/is_int.hpp"
#include <stdexcept>
namespace t_math
{
    inline double zeta(double arg, double alpha = 1)
    {
        if (is_int(arg) && arg <= 0)
            throw std::out_of_range("Hurwitz zeta function isn't defined at that range!");
        if(arg <= 1) {
            if(alpha == 1) throw std::out_of_range("Riemann zeta function isn't defined at that range!");
            if(alpha != 1) throw std::out_of_range("Hurwits zeta function isn't defined at that range!");
        }
        double temp = 0;
        int i = 0;
        bool is_termimated = false;
        double term = 0;
        while (is_termimated == false)
        {
            term = 1 / pow(i + alpha, arg);
            if (abs(term) < t_math_precise)
                is_termimated = true;
            i++;
            temp+=term;
        }
        return temp;
    };
}
#endif // ZETA_HPP