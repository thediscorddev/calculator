#ifndef LI_HPP
#define LI_HPP

#include <stdexcept>

#include "../t_math_constant.hpp"

#include "../general/abs.hpp"

#include "../general/factorial.hpp"

#include "../general/pow.hpp"

#include "../general/ln.hpp"

namespace t_math 
{
  inline double li(double arg) 
  {
    if(arg == 0)
        return 0;
    if (arg < 0 || arg == 1)
      throw std::out_of_range("Invaild number: Li(x) is not defined at 1 and negative number.");
    double temp = Euler_Mascheroni_constant + ln(abs(ln(arg)));
    double is_termiated = false;
    double term = 0; // temp term
    int i = 1;
    while (is_termiated == false) 
    {
      term = pow_int(ln(arg), i) / (i * d_fac(i));
      if (abs(term) < t_math_precise) 
        is_termiated = true;
      temp += term;
      i++;
    };
    return temp;
  };
};
#endif // LI_HPP