#ifndef CI_HPP
#define CI_HPP
#include "../general/pow.hpp"
#include "../general/factorial.hpp"
#include "../t_math_constant.hpp"
#include "../trigonometry/sin.hpp"
#include "../trigonometry/cos.hpp"
#include "../general/ln.hpp"
#include "../general/abs.hpp"
#include <stdexcept>
namespace t_math
{
    inline double ci(double args)
    {
        double temp = 0;
        int i = 1;
        if (args <= 0)
            throw std::out_of_range("Ci(x) isn't defined at these range.");
        if (args <= 26)
        {
            bool is_termimated = false;
            double term = 0;
            while (is_termimated == false)
            {
                term = (pow_int(-1, i) * pow_int(args, 2 * i)) / (d_fac(2 * i) * (2 * i));
                if (abs(term) < t_math_precise)
                    is_termimated = true;
                temp += term;
                i++;
            };
            return ln(args) + Euler_Mascheroni_constant + temp;
        }
        else
        {
            double si = 1;
            double cn = 1 / args;
            while (i <= 30)
            {
                si += pow_int(-1, i) * d_fac(2 * i) / pow_int(args, 2 * i);
                cn += pow_int(-1, i) * d_fac(2 * i + 1) / pow_int(args, 2 * i + 1);
                i++;
            };
            temp += (sin(args) / args) * si - (cos(args) / args) * (cn);

        };
        return temp; 
    };
};
#endif // CI_HPP