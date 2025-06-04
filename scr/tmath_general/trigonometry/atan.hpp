#ifndef ATAN_HPP
#define ATAN_HPP
#include "../general/pow.hpp"
#include "../general/abs.hpp"
#include "../t_math_constant.hpp"
namespace t_math
{
  inline long double atan(double args)
  {
    if (args < -1)
      return atan(1 / (-1 * args)) - pi / 2;
    if (args > 1)
      return pi / 2 - atan(1 / args);
    long double temp = 0;
    int i = 0;
    while (abs(pow(-1, i) * pow(args, 2 * i + 1) / (2 * i + 1)) >= t_math_precise)
    {
      temp += pow(-1, i) * pow(args, 2 * i + 1) / (2 * i + 1);
      i++;
    }

    return temp;
  };
}
#endif // ATAN_HPP
